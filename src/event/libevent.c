#include <minilang/ml_library.h>
#include <minilang/ml_macros.h>
#include <minilang/ml_file.h>
#include <minilang/ml_object.h>
#include <minilang/ml_stream.h>
#include <minilang/ml_logging.h>
#include <gc/gc.h>
#include <event2/event.h>
#include <event2/thread.h>
#include <event2/http.h>
#include <event2/buffer.h>
#include <event2/keyvalq_struct.h>
#include <event2/bufferevent_ssl.h>
#include <openssl/ssl.h>
#include <math.h>
#include <fcntl.h>
#include <sys/stat.h>

typedef struct {
	ml_scheduler_t Base;
	ml_scheduler_queue_t *Queue;
	struct event_base *Events;
	struct event *QueueEvent;
} event_scheduler_t;

static event_scheduler_t Scheduler[1];

typedef struct event_t {
	const ml_type_t *Type;
	struct event *Handle;
} ml_event_t;

ML_TYPE(EventT, (), "event");

ML_FUNCTIONX(EventSleep) {
	ML_RETURN(MLNil);
}

typedef struct {
	const ml_type_t *Type;
	struct evhttp *Handle;
} evhttp_t;

ML_TYPE(EventHttpT, (), "event-http");

ML_METHOD(EventHttpT) {
	evhttp_t *Http = new(evhttp_t);
	Http->Type = EventHttpT;
	Http->Handle = evhttp_new(Scheduler->Events);
	return (ml_value_t *)Http;
}

typedef struct {
	ml_context_t *Context;
	ml_value_t *Fn;
} callback_t;

typedef struct {
	ml_state_t Base;
	ml_value_t *Value;
	ml_value_t *Args[];
} call_state_t;

static void call_state_done(call_state_t *State, ml_value_t *Value) {
	if (ml_is_error(Value)) ML_LOG_ERROR(Value, "Callback returned an error");
}

static void call_state_run(call_state_t *State, ml_value_t *Value) {
	State->Base.run = (ml_state_fn)call_state_done;
	return ml_call(State, State->Value, ml_integer_value(Value), State->Args);
}

typedef enum {
	REQUEST_STATE_NORMAL,
	REQUEST_STATE_STREAMING,
	REQUEST_STATE_CLOSED
} evhttp_request_state_t;

typedef struct {
	ml_type_t *Type;
	struct evhttp_request *Handle;
	struct evbuffer *Buffer;
	ml_state_t *Caller;
	size_t Count;
	evhttp_request_state_t State;
} evhttp_request_t;

ML_TYPE(HttpRequestT, (MLStreamT), "http-request");

static void request_finalize(evhttp_request_t *Request, void *Data) {
	ML_LOG_INFO(NULL, "Finalizing request");
	if (Request->State != REQUEST_STATE_CLOSED) {
		evhttp_send_error(Request->Handle, 500, "Internal Server Error");
	}
	evhttp_request_free(Request->Handle);
	Request->Handle = NULL;
}

static evhttp_request_t *event_request(struct evhttp_request *Handle) {
	evhttp_request_t *Request = new(evhttp_request_t);
	Request->Type = HttpRequestT;
	Request->Handle = Handle;
	Request->State = REQUEST_STATE_NORMAL;
	GC_register_finalizer(Request, (void *)request_finalize, NULL, NULL, NULL);
	return Request;
}

ML_ENUM2(HttpMethodT, "http-method",
	"GET", EVHTTP_REQ_GET,
	"POST", EVHTTP_REQ_POST,
	"HEAD", EVHTTP_REQ_HEAD,
	"PUT", EVHTTP_REQ_PUT,
	"DELETE", EVHTTP_REQ_DELETE,
	"OPTIONS", EVHTTP_REQ_OPTIONS,
	"TRACE", EVHTTP_REQ_TRACE,
	"CONNECT", EVHTTP_REQ_CONNECT,
	"PATCH", EVHTTP_REQ_PATCH
);

ML_METHOD("method", HttpRequestT) {
	evhttp_request_t *Request = (evhttp_request_t *)Args[0];
	return ml_enum_value(HttpMethodT, evhttp_request_get_command(Request->Handle));
}

ML_METHOD("uri", HttpRequestT) {
	evhttp_request_t *Request = (evhttp_request_t *)Args[0];
	return ml_string(evhttp_request_get_uri(Request->Handle), -1);
}

ML_METHOD("add_header", HttpRequestT, MLStringT, MLStringT) {
	evhttp_request_t *Request = (evhttp_request_t *)Args[0];
	if (Request->State != REQUEST_STATE_NORMAL) return ml_error("StateError", "Invalid request state");
	evhttp_add_header(evhttp_request_get_output_headers(Request->Handle), ml_string_value(Args[1]), ml_string_value(Args[2]));
	return (ml_value_t *)Request;
}

ML_METHOD("body", HttpRequestT) {
	evhttp_request_t *Request = (evhttp_request_t *)Args[0];
	struct evbuffer *Input = evhttp_request_get_input_buffer(Request->Handle);
	size_t Length = evbuffer_get_length(Input);
	char *Bytes = snew(Length + 1);
	evbuffer_copyout(Input, Bytes, Length);
	evbuffer_drain(Input, Length);
	return ml_string(Bytes, Length);
}

ML_METHOD("send_reply", HttpRequestT, MLIntegerT, MLStringT, MLAddressT) {
	evhttp_request_t *Request = (evhttp_request_t *)Args[0];
	if (Request->State != REQUEST_STATE_NORMAL) return ml_error("StateError", "Invalid request state");
	struct evbuffer *Buffer = evbuffer_new();
	evbuffer_add(Buffer, ml_address_value(Args[3]), ml_address_length(Args[3]));
	evhttp_send_reply(Request->Handle, ml_integer_value(Args[1]), ml_string_value(Args[2]), Buffer);
	Request->State = REQUEST_STATE_CLOSED;
	evhttp_request_free(Request->Handle);
	Request->Handle = NULL;
	return (ml_value_t *)Request;
}

ML_METHOD("send_error", HttpRequestT, MLIntegerT, MLStringT) {
	evhttp_request_t *Request = (evhttp_request_t *)Args[0];
	if (Request->State != REQUEST_STATE_NORMAL) return ml_error("StateError", "Invalid request state");
	evhttp_send_error(Request->Handle, ml_integer_value(Args[1]), ml_string_value(Args[2]));
	Request->State = REQUEST_STATE_CLOSED;
	evhttp_request_free(Request->Handle);
	Request->Handle = NULL;
	return (ml_value_t *)Request;
}

ML_METHOD("send_file", HttpRequestT, MLIntegerT, MLStringT, MLStringT) {
	evhttp_request_t *Request = (evhttp_request_t *)Args[0];
	if (Request->State != REQUEST_STATE_NORMAL) return ml_error("StateError", "Invalid request state");
	int Fd = open(ml_string_value(Args[3]), O_RDONLY);
	if (Fd == -1) {
		if (errno == ENOENT) {
			evhttp_send_error(Request->Handle, HTTP_NOTFOUND, NULL);
		} else {
			evhttp_send_error(Request->Handle, HTTP_INTERNAL, NULL);
		}
	} else {
		struct stat Stat;
		if (fstat(Fd, &Stat) == -1) {
			close(Fd);
			evhttp_send_error(Request->Handle, HTTP_INTERNAL, NULL);
		} else {
			char SizeString[32];
			sprintf(SizeString, "%ld", Stat.st_size);
			evhttp_add_header(evhttp_request_get_output_headers(Request->Handle), "Content-Size", SizeString);
			struct evbuffer *Buffer = evbuffer_new();
			evbuffer_add_file(Buffer, Fd, 0, Stat.st_size);
			evhttp_send_reply(Request->Handle, ml_integer_value(Args[1]), ml_string_value(Args[2]), Buffer);
		}
	}
	Request->State = REQUEST_STATE_CLOSED;
	evhttp_request_free(Request->Handle);
	Request->Handle = NULL;
	return (ml_value_t *)Request;
}

ML_METHOD("send_stream", HttpRequestT, MLIntegerT, MLStringT) {
	evhttp_request_t *Request = (evhttp_request_t *)Args[0];
	if (Request->State != REQUEST_STATE_NORMAL) return ml_error("StateError", "Invalid request state");
	evhttp_send_reply_start(Request->Handle, ml_integer_value(Args[1]), ml_string_value(Args[2]));
	Request->State = REQUEST_STATE_STREAMING;
	Request->Buffer = evbuffer_new();
	return (ml_value_t *)Request;
}

static void reply_chunk_callback(struct evhttp_connection *Conn, evhttp_request_t *Request) {
	ml_state_t *Caller = Request->Caller;
	Request->Caller = NULL;
	ml_state_schedule(Caller, ml_integer(Request->Count));
}

static void ML_TYPED_FN(ml_stream_write, HttpRequestT, ml_state_t *Caller, evhttp_request_t *Request, void *Buffer, int Count) {
	if (Request->State != REQUEST_STATE_STREAMING) ML_ERROR("StateError", "Invalid request state");
	if (Request->Caller) ML_ERROR("StateError", "Invalid request state");
	evbuffer_add(Request->Buffer, Buffer, Count);
	Request->Caller = Caller;
	Request->Count = Count;
	evhttp_send_reply_chunk_with_cb(Request->Handle, Request->Buffer, (void *)reply_chunk_callback, Request);
}

static void ML_TYPED_FN(ml_stream_close, HttpRequestT, ml_state_t *Caller, evhttp_request_t *Request) {
	if (Request->State != REQUEST_STATE_STREAMING) ML_ERROR("StateError", "Invalid request state");
	if (Request->Caller) ML_ERROR("StateError", "Invalid request state");
	evhttp_send_reply_end(Request->Handle);
	Request->State = REQUEST_STATE_CLOSED;
	evhttp_request_free(Request->Handle);
	Request->Handle = NULL;
	ML_RETURN(MLNil);
}

typedef struct {
	ml_type_t *Type;
	struct evkeyvalq *Handle;
} evkeyvalq_t;

ML_TYPE(HttpHeadersT, (MLSequenceT), "http-headers");

ML_METHOD("headers", HttpRequestT) {
	evhttp_request_t *Request = (evhttp_request_t *)Args[0];
	evkeyvalq_t *Headers = new(evkeyvalq_t);
	Headers->Type = HttpHeadersT;
	Headers->Handle = evhttp_request_get_input_headers(Request->Handle);
	return (ml_value_t *)Headers;
}

ML_METHOD("[]", HttpHeadersT, MLStringT) {
	evkeyvalq_t *Headers = (evkeyvalq_t *)Args[0];
	const char *Value = evhttp_find_header(Headers->Handle, ml_string_value(Args[1]));
	return Value ? ml_string(Value, -1) : MLNil;
}

typedef struct {
	ml_type_t *Type;
	struct evkeyval *Handle;
} evkeyval_t;

ML_TYPE(HttpHeaderT, (), "http-header");

static void ML_TYPED_FN(ml_iterate, HttpHeadersT, ml_state_t *Caller, evkeyvalq_t *Headers) {
	if (!Headers->Handle->tqh_first) ML_RETURN(MLNil);
	evkeyval_t *Next = new(evkeyval_t);
	Next->Type = HttpHeaderT;
	Next->Handle = Headers->Handle->tqh_first;
	ML_RETURN(Next);
}

static void ML_TYPED_FN(ml_iter_next, HttpHeaderT, ml_state_t *Caller, evkeyval_t *Header) {
	if (!Header->Handle->next.tqe_next) ML_RETURN(MLNil);
	evkeyval_t *Next = new(evkeyval_t);
	Next->Type = HttpHeaderT;
	Next->Handle = Header->Handle->next.tqe_next;
	ML_RETURN(Next);
}

static void ML_TYPED_FN(ml_iter_key, HttpHeaderT, ml_state_t *Caller, evkeyval_t *Header) {
	ML_RETURN(ml_string(Header->Handle->key, -1));
}

static void ML_TYPED_FN(ml_iter_value, HttpHeaderT, ml_state_t *Caller, evkeyval_t *Header) {
	ML_RETURN(ml_string(Header->Handle->value, -1));
}

typedef struct {
	ml_state_t Base;
	ml_value_t *Value;
	evhttp_request_t *Request;
} request_state_t;

static void request_state_done(request_state_t *State, ml_value_t *Value) {
	if (ml_is_error(Value)) {
		ML_LOG_ERROR(Value, "Callback returned an error");
		if (State->Request->State != REQUEST_STATE_CLOSED) {
			State->Request->State = REQUEST_STATE_CLOSED;
			evhttp_send_error(State->Request->Handle, HTTP_INTERNAL, NULL);
			evhttp_request_free(State->Request->Handle);
		}
	}
}

static void request_state_run(request_state_t *State, ml_value_t *Value) {
	State->Base.run = (ml_state_fn)request_state_done;
	return ml_call(State, State->Value, 1, (ml_value_t **)&State->Request);
}

static void gen_callback(struct evhttp_request *Request, callback_t *Callback) {
	request_state_t *CallState = new(request_state_t);
	CallState->Base.Context = Callback->Context;
	CallState->Base.run = (ml_state_fn)request_state_run;
	CallState->Value = Callback->Fn;
	CallState->Request = event_request(Request);
	ml_state_schedule((ml_state_t *)CallState, MLNil);
}

/*static void request_input_buffer_callback(struct evbuffer *Input, const struct evbuffer_cb_info *Info, void *Arg) {

}

static int newreq_callback(struct evhttp_request *Request, evhttp_t *Http) {
	struct evbuffer *Input = evhttp_request_get_input_buffer(Request);
	evbuffer_add_cb(Input, request_input_buffer_callback, Http);
	return 0;
}*/

ML_METHODX(EventHttpT, MLFunctionT) {
	evhttp_t *Http = new(evhttp_t);
	Http->Type = EventHttpT;
	Http->Handle = evhttp_new(Scheduler->Events);
	callback_t *Callback = new(callback_t);
	Callback->Context = Caller->Context;
	Callback->Fn = Args[0];
	evhttp_set_gencb(Http->Handle, (void *)gen_callback, Callback);
	//evhttp_set_newreqcb(Http->Handle, (void *)newreq_callback, Http);
	ML_RETURN(Http);
}

static struct bufferevent *ssl_callback(struct event_base *Base, SSL_CTX *Ctx) {
	SSL *Ssl = SSL_new(Ctx);
	return bufferevent_openssl_socket_new(Base, -1, Ssl, BUFFEREVENT_SSL_ACCEPTING, BEV_OPT_CLOSE_ON_FREE);
}

ML_METHOD("enable_ssl", EventHttpT, MLStringT, MLStringT) {
	SSL_CTX *Ctx = SSL_CTX_new(TLS_server_method());
	SSL_CTX_use_certificate_chain_file(Ctx, ml_string_value(Args[1]));
	SSL_CTX_use_PrivateKey_file(Ctx, ml_string_value(Args[2]), SSL_FILETYPE_PEM);
	evhttp_t *Http = (evhttp_t *)Args[0];
	evhttp_set_bevcb(Http->Handle, (void *)ssl_callback, Ctx);
	return (ml_value_t *)Http;
}

ML_METHOD("bind", EventHttpT, MLStringT, MLIntegerT) {
	evhttp_t *Http = (evhttp_t *)Args[0];
	if (evhttp_bind_socket(Http->Handle, ml_string_value(Args[1]), ml_integer_value(Args[2]))) {
		return ml_error("BindError", "Error binding socket");
	} else {
		return (ml_value_t *)Http;
	}
}

int ml_event_queue_add(event_scheduler_t *Scheduler, ml_state_t *State, ml_value_t *Value) {
	int Fill = ml_scheduler_queue_add(Scheduler->Queue, State, Value);
	event_active(Scheduler->QueueEvent, 0, 0);
	return Fill;
}

void ml_event_queue_run(event_scheduler_t *Scheduler) {
	while (!ml_scheduler_queue_fill(Scheduler->Queue)) event_base_loop(Scheduler->Events, EVLOOP_NO_EXIT_ON_EMPTY);
	ml_queued_state_t QueuedState = ml_scheduler_queue_next(Scheduler->Queue);
	if (QueuedState.State) QueuedState.State->run(QueuedState.State, QueuedState.Value);
}

int ml_event_queue_fill(event_scheduler_t *Scheduler) {
	return ml_scheduler_queue_fill(Scheduler->Queue);
}

typedef struct {
	ml_state_t *State;
	ml_value_t *Result;
	struct event *Event;
} ml_event_sleep_t;

static void sleep_run(evutil_socket_t Socket, short Events, ml_event_sleep_t *Sleep) {
	ml_state_schedule(Sleep->State, Sleep->Result);
	event_free(Sleep->Event);
}

void ml_event_queue_sleep(event_scheduler_t *Scheduler, ml_state_t *State, double Duration, ml_value_t *Result) {
	ml_event_sleep_t *Sleep = new(ml_event_sleep_t);
	Sleep->State = State;
	Sleep->Result = Result;
	Sleep->Event = event_new(Scheduler->Events, -1, 0, (event_callback_fn)sleep_run, Sleep);
	struct timeval Timeout;
	Timeout.tv_sec = floor(Duration);
	Timeout.tv_usec = (Duration - Timeout.tv_sec) * 1000000;
	event_add(Sleep->Event, &Timeout);
}

static void event_queue_run(evutil_socket_t Socket, short Events, event_scheduler_t *Scheduler) {
	event_base_loopbreak(Scheduler->Events);
}

static void nop_free(void *Ptr) {
}

static void log_run(int Severity, const char *Message) {
	ML_LOG_INFO(NULL, "libevent [%d]: %s", Severity, Message);
}

ML_LIBRARY_ENTRY(event_libevent) {
	SSL_library_init();
	evthread_use_pthreads();
	event_set_mem_functions(GC_malloc, GC_realloc, nop_free);
	event_set_log_callback(log_run);
#include "libevent_init.c"
	Scheduler->Base.add = (ml_scheduler_add_fn)ml_event_queue_add;
	Scheduler->Base.run = (ml_scheduler_run_fn)ml_event_queue_run;
	Scheduler->Base.fill = (ml_scheduler_fill_fn)ml_event_queue_fill;
	Scheduler->Base.sleep = (ml_scheduler_sleep_fn)ml_event_queue_sleep;
	Scheduler->Queue = ml_default_queue_init(Caller->Context, 256);
	Scheduler->Events = event_base_new();
	Scheduler->QueueEvent = event_new(Scheduler->Events, -1, EV_PERSIST, (event_callback_fn)event_queue_run, Scheduler);
	ml_context_set_static(Caller->Context, ML_SCHEDULER_INDEX, Scheduler);
	stringmap_insert(EventHttpT->Exports, "request", HttpRequestT);
	stringmap_insert(EventHttpT->Exports, "method", HttpMethodT);
	ml_value_t *Module = Slot[0] = ml_module("libevent",
		"http", EventHttpT,
	NULL);
	ML_RETURN(Module);
}
