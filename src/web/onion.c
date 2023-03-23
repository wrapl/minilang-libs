#include <minilang/ml_library.h>
#include <minilang/ml_macros.h>
#include <minilang/ml_object.h>
#include <minilang/ml_stream.h>
#include <minilang/ml_thread.h>
#define HAVE_PTHREADS
#include <onion/onion.h>
#include <onion/block.h>
#include <onion/low.h>
#include <onion/log.h>
#include <onion/exportlocal.h>
#include <onion/static.h>
#include <onion/websocket.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>

#undef ML_CATEGORY
#define ML_CATEGORY "web/onion"

static ML_FLAGS2(OnionModeT, "onion::mode",
	"One", O_ONE,
	"OneLoop", O_ONE_LOOP,
	"Threaded", O_THREADED,
	"DetachListen", O_DETACH_LISTEN,
	"Systemd", O_SYSTEMD,
	"Poll", O_POLL,
	"Pool", O_POOL,
	"NoSIGPIPE", O_NO_SIGPIPE,
	"NoSIGTERM", O_NO_SIGTERM,
	"SSLAvailable", O_SSL_AVAILABLE,
	"SSLEnabed", O_SSL_ENABLED,
	"ThreadsAvailable", O_THREADS_AVAILABLE,
	"ThreadsEnabled", O_THREADS_ENABLED,
	"Detached", O_DETACHED,
	"Listening", O_LISTENING
);

typedef struct {
	const ml_type_t *Type;
	onion *Handle;
} ml_onion_t;

ML_TYPE(OnionT, (), "onion");

ML_METHOD(OnionT) {
	ml_onion_t *Onion = new(ml_onion_t);
	Onion->Type = OnionT;
	Onion->Handle = onion_new(0);
	onion_set_client_data(Onion->Handle, Onion, NULL);
	return (ml_value_t *)Onion;
}

ML_METHOD(OnionT, OnionModeT) {
	ml_onion_t *Onion = new(ml_onion_t);
	Onion->Type = OnionT;
	Onion->Handle = onion_new(ml_flags_value_value(Args[0]));
	onion_set_client_data(Onion->Handle, Onion, NULL);
	return (ml_value_t *)Onion;
}

ML_METHOD("listen", OnionT) {
	ml_onion_t *Onion = (ml_onion_t *)Args[0];
	return ml_integer(onion_listen(Onion->Handle));
}

ML_METHOD("listen_stop", OnionT) {
	ml_onion_t *Onion = (ml_onion_t *)Args[0];
	onion_listen_stop(Onion->Handle);
	return MLNil;
}

typedef struct {
	const ml_type_t *Type;
	onion_handler *Handle;
	ml_context_t *Context;
	ml_value_t *Callback;
} ml_onion_handler_t;

ML_TYPE(OnionHandlerT, (), "onion-handler");

typedef struct {
	const ml_type_t *Type;
	onion_request *Handle;
} ml_onion_request_t;

ML_TYPE(OnionRequestT, (), "onion-request");

typedef struct {
	const ml_type_t *Type;
	onion_response *Handle;
} ml_onion_response_t;

ML_TYPE(OnionResponseT, (MLStreamT), "onion-response");

typedef struct {
	ml_state_t Base;
	ml_value_t *Args[2];
	onion_connection_status Status;
} ml_onion_state_t;

ML_TYPE(OnionStateT, (), "onion-state");

static ML_ENUM2(OnionConnectionStatusT, "onion::connection_status",
	"NotProcessed", OCS_NOT_PROCESSED,
	"NeedMoreData", OCS_NEED_MORE_DATA,
	"Processed", OCS_PROCESSED,
	"CloseConnection", OCS_CLOSE_CONNECTION,
	"KeepAlive", OCS_KEEP_ALIVE,
	"Websocket", OCS_WEBSOCKET,
	"RequestReady", OCS_REQUEST_READY,
	"InternalError", OCS_INTERNAL_ERROR,
	"NotImplemented", OCS_NOT_IMPLEMENTED,
	"Forbidden", OCS_FORBIDDEN,
	"Yield", OCS_YIELD
);

static ml_value_t *ml_onion_state_run(ml_onion_state_t *State, ml_value_t *Result) {
	if (ml_is_error(Result)) {
		printf("Error: %s\n", ml_error_message(Result));
		ml_source_t Source;
		int Level = 0;
		while (ml_error_source(Result, Level++, &Source)) {
			printf("\t%s:%d\n", Source.Name, Source.Line);
		}
		State->Status = OCS_INTERNAL_ERROR;
		return Result;
	}
	if (State->Status == OCS_NOT_PROCESSED) {
		if (ml_is(Result, OnionConnectionStatusT)) {
			State->Status = ml_enum_value_value(Result);
		} else {
			State->Status = OCS_PROCESSED;
		}
	}
	//ml_onion_request_t *Request = (ml_onion_request_t *)State->Args[0];
	//ml_onion_request_t *Response = (ml_onion_request_t *)State->Args[1];
	//onion_request_free(Request->Handle);
	//onion_response_free(Response->Handle);
	return Result;
}

static onion_connection_status ml_onion_handler(ml_onion_handler_t *Handler, onion_request *Req, onion_response *Res) {
	ml_onion_request_t *Request = new(ml_onion_request_t);
	Request->Type = OnionRequestT;
	Request->Handle = Req;
	ml_onion_response_t *Response = new(ml_onion_response_t);
	Response->Type = OnionResponseT;
	Response->Handle = Res;
	ml_onion_state_t *State = new(ml_onion_state_t);
	State->Base.Type = OnionStateT;
	State->Base.run = (void *)ml_onion_state_run;
	State->Base.Context = Handler->Context;
	State->Args[0] = (ml_value_t *)Request;
	State->Args[1] = (ml_value_t *)Response;
	State->Status = OCS_NOT_PROCESSED;
	ml_call((ml_state_t *)State, Handler->Callback, 2, State->Args);
	if (State->Status == OCS_NOT_PROCESSED) {
		return (State->Status = OCS_YIELD);
	} else {
		return State->Status;
	}
}

ML_METHOD("get_root_handler", OnionT) {
	ml_onion_t *Onion = (ml_onion_t *)Args[0];
	ml_onion_handler_t *Handler = new(ml_onion_handler_t);
	Handler->Type = OnionHandlerT;
	Handler->Handle = onion_get_root_handler(Onion->Handle);
	return (ml_value_t *)Handler;
}

ML_METHOD("set_root_handler", OnionT, OnionHandlerT) {
	ml_onion_t *Onion = (ml_onion_t *)Args[0];
	ml_onion_handler_t *Handler = (ml_onion_handler_t *)Args[1];
	if (onion_flags(Onion->Handle) & O_THREADS_ENABLED) {
		ml_value_t *Error = ml_is_threadsafe(Handler->Callback);
		if (Error) return Error;
	}
	onion_set_root_handler(Onion->Handle, Handler->Handle);
	return Args[0];
}

ML_METHODX("set_root_handler", OnionT, MLFunctionT) {
	ml_onion_t *Onion = (ml_onion_t *)Args[0];
	if (onion_flags(Onion->Handle) & O_THREADS_ENABLED) {
		ml_value_t *Error = ml_is_threadsafe(Args[1]);
		if (Error) ML_RETURN(Error);
	}
	ml_onion_handler_t *Handler = new(ml_onion_handler_t);
	Handler->Type = OnionHandlerT;
	Handler->Handle = onion_handler_new((void *)ml_onion_handler, Handler, NULL);
	Handler->Context = Caller->Context;
	Handler->Callback = Args[1];
	onion_set_root_handler(Onion->Handle, Handler->Handle);
	ML_RETURN(Onion);
}

ML_METHOD("set_internal_error_handler", OnionT, OnionHandlerT) {
	ml_onion_t *Onion = (ml_onion_t *)Args[0];
	ml_onion_handler_t *Handler = (ml_onion_handler_t *)Args[1];
	if (onion_flags(Onion->Handle) & O_THREADS_ENABLED) {
		ml_value_t *Error = ml_is_threadsafe(Handler->Callback);
		if (Error) return Error;
	}
	onion_set_internal_error_handler(Onion->Handle, Handler->Handle);
	return Args[0];
}

ML_METHODX("set_internal_error_handler", OnionT, MLFunctionT) {
	ml_onion_t *Onion = (ml_onion_t *)Args[0];
	if (onion_flags(Onion->Handle) & O_THREADS_ENABLED) {
		ml_value_t *Error = ml_is_threadsafe(Args[1]);
		if (Error) ML_RETURN(Error);
	}
	ml_onion_handler_t *Handler = new(ml_onion_handler_t);
	Handler->Type = OnionHandlerT;
	Handler->Handle = onion_handler_new((void *)ml_onion_handler, Handler, NULL);
	Handler->Context = Caller->Context;
	Handler->Callback = Args[1];
	onion_set_internal_error_handler(Onion->Handle, Handler->Handle);
	ML_RETURN(Onion);
}

ML_METHOD("set_hostname", OnionT, MLStringT) {
	ml_onion_t *Onion = (ml_onion_t *)Args[0];
	onion_set_hostname(Onion->Handle, ml_string_value(Args[1]));
	return Args[0];
}

ML_METHOD("set_port", OnionT, MLStringT) {
	ml_onion_t *Onion = (ml_onion_t *)Args[0];
	onion_set_port(Onion->Handle, ml_string_value(Args[1]));
	return Args[0];
}

ML_METHOD("get_path", OnionRequestT) {
	ml_onion_request_t *Request = (ml_onion_request_t *)Args[0];
	return ml_string(onion_request_get_path(Request->Handle), -1);
}

ML_METHOD("get_fullpath", OnionRequestT) {
	ml_onion_request_t *Request = (ml_onion_request_t *)Args[0];
	return ml_string(onion_request_get_fullpath(Request->Handle), -1);
}

ML_METHOD("get_header", OnionRequestT, MLStringT) {
	ml_onion_request_t *Request = (ml_onion_request_t *)Args[0];
	return ml_string(onion_request_get_header(Request->Handle, ml_string_value(Args[1])), -1);
}

ML_METHOD("get_query", OnionRequestT, MLStringT) {
	ml_onion_request_t *Request = (ml_onion_request_t *)Args[0];
	return ml_string(onion_request_get_query(Request->Handle, ml_string_value(Args[1])), -1);
}

ML_METHOD("get_post", OnionRequestT, MLStringT) {
	ml_onion_request_t *Request = (ml_onion_request_t *)Args[0];
	return ml_string(onion_request_get_post(Request->Handle, ml_string_value(Args[1])), -1);
}

ML_METHOD("get_file", OnionRequestT, MLStringT) {
	ml_onion_request_t *Request = (ml_onion_request_t *)Args[0];
	return ml_string(onion_request_get_file(Request->Handle, ml_string_value(Args[1])), -1);
}

ML_METHOD("get_cookie", OnionRequestT, MLStringT) {
	ml_onion_request_t *Request = (ml_onion_request_t *)Args[0];
	return ml_string(onion_request_get_cookie(Request->Handle, ml_string_value(Args[1])), -1);
}

ML_METHOD("get_data", OnionRequestT) {
	ml_onion_request_t *Request = (ml_onion_request_t *)Args[0];
	const onion_block *Block = onion_request_get_data(Request->Handle);
	if (!Block) return MLNil;
	return ml_string(onion_block_data(Block), onion_block_size(Block));
}

ML_METHOD("set_code", OnionResponseT, MLIntegerT) {
	ml_onion_response_t *Response = (ml_onion_response_t *)Args[0];
	onion_response_set_code(Response->Handle, ml_integer_value(Args[1]));
	return Args[0];
}

ML_METHOD("set_header", OnionResponseT, MLStringT, MLStringT) {
	ml_onion_response_t *Response = (ml_onion_response_t *)Args[0];
	onion_response_set_header(Response->Handle, ml_string_value(Args[1]), ml_string_value(Args[2]));
	return Args[0];
}

ML_METHOD("add_cookie", OnionResponseT, MLStringT, MLStringT) {
	time_t Validity = 0;
	const char *Path = NULL, *Domain = NULL;
	int Flags = 0;
	ml_onion_response_t *Response = (ml_onion_response_t *)Args[0];
	onion_response_add_cookie(Response->Handle, ml_string_value(Args[1]), ml_string_value(Args[2]), Validity, Path, Domain, Flags);
	return Args[0];
}

ML_METHOD("write", OnionResponseT, MLStringT) {
	ml_onion_response_t *Response = (ml_onion_response_t *)Args[0];
	onion_response_write(Response->Handle, ml_string_value(Args[1]), ml_string_length(Args[1]));
	return Args[0];
}

ML_METHOD("flush", OnionResponseT) {
	ml_onion_response_t *Response = (ml_onion_response_t *)Args[0];
	onion_response_flush(Response->Handle);
	return Args[0];
}

static void ML_TYPED_FN(ml_stream_write, OnionResponseT, ml_state_t *Caller, ml_onion_response_t *Response, const void *Address, int Count) {
	ssize_t Result = onion_response_write(Response->Handle, Address, Count);
	if (Result < 0) {
		ML_ERROR("OnionError", "Error writing response");
	} else {
		ML_RETURN(ml_integer(Result));
	}
}

ML_METHODX(OnionHandlerT, MLFunctionT) {
	ml_onion_handler_t *Handler = new(ml_onion_handler_t);
	Handler->Type = OnionHandlerT;
	Handler->Handle = onion_handler_new((void *)ml_onion_handler, Handler, NULL);
	Handler->Context = Caller->Context;
	Handler->Callback = Args[0];
	ML_RETURN(Handler);
}

ML_METHOD(OnionHandlerT, MLStringT) {
	ml_onion_handler_t *Handler = new(ml_onion_handler_t);
	Handler->Type = OnionHandlerT;
	Handler->Handle = onion_handler_export_local_new(ml_string_value(Args[0]));
	return (ml_value_t *)Handler;
}

ML_METHOD(OnionHandlerT, MLIntegerT, MLStringT) {
	ml_onion_handler_t *Handler = new(ml_onion_handler_t);
	Handler->Type = OnionHandlerT;
	Handler->Handle = onion_handler_static(ml_string_value(Args[1]), ml_integer_value(Args[0]));
	return (ml_value_t *)Handler;
}

ML_METHOD("add", OnionHandlerT, OnionHandlerT) {
	ml_onion_handler_t *Base = (ml_onion_handler_t *)Args[0];
	ml_onion_handler_t *New = (ml_onion_handler_t *)Args[1];
	onion_handler_add(Base->Handle, New->Handle);
	return Args[0];
}

typedef struct ml_onion_url_t {
	const ml_type_t *Type;
	onion_url *Handle;
	stringmap_t Callbacks[1];
} ml_onion_url_t;

extern ml_type_t OnionUrlT[];

ML_METHOD("root_url", OnionT) {
	ml_onion_t *Onion = (ml_onion_t *)Args[0];
	ml_onion_url_t *Url = new(ml_onion_url_t);
	Url->Type = OnionUrlT;
	Url->Handle = onion_root_url(Onion->Handle);
	return (ml_value_t *)Url;
}

ML_FUNCTION(OnionUrl) {
	ml_onion_url_t *Url = new(ml_onion_url_t);
	Url->Type = OnionUrlT;
	Url->Handle = onion_url_new();
	return (ml_value_t *)Url;
}

ML_TYPE(OnionUrlT, (), "onion-url",
	.Constructor = (ml_value_t *)OnionUrl
);

ML_METHODX("add", OnionUrlT, MLStringT, MLFunctionT) {
	ml_onion_url_t *Url = (ml_onion_url_t *)Args[0];
	ml_onion_handler_t *Handler = new(ml_onion_handler_t);
	Handler->Type = OnionHandlerT;
	Handler->Context = Caller->Context;
	Handler->Callback = Args[2];
	onion_url_add_with_data(Url->Handle, ml_string_value(Args[1]), ml_onion_handler, Handler, NULL);
	ML_RETURN(Url);
}

ML_METHOD("add", OnionUrlT, MLStringT, OnionHandlerT) {
	ml_onion_url_t *Url = (ml_onion_url_t *)Args[0];
	ml_onion_handler_t *Handler = (ml_onion_handler_t *)Args[1];
	onion_url_add_handler(Url->Handle, ml_string_value(Args[1]), Handler->Handle);
	return Args[0];
}

ML_METHOD("add_static", OnionUrlT, MLStringT, MLIntegerT, MLStringT) {
	ml_onion_url_t *Url = (ml_onion_url_t *)Args[0];
	onion_url_add_static(Url->Handle, ml_string_value(Args[1]), ml_string_value(Args[3]), ml_integer_value(Args[2]));
	return Args[0];
}

ML_METHOD("to_handler", OnionUrlT) {
	ml_onion_url_t *Url = (ml_onion_url_t *)Args[0];
	ml_onion_handler_t *Handler = new(ml_onion_handler_t);
	Handler->Type = OnionHandlerT;
	Handler->Handle = onion_url_to_handler(Url->Handle);
	return (ml_value_t *)Handler;
}

typedef struct ml_onion_websocket_t {
	ml_state_t Base;
	onion_websocket *Handle;
	ml_value_t *Callback;
	ml_value_t *Args[1];
} ml_onion_websocket_t;

static void ml_onion_websocket_run(ml_onion_websocket_t *Websocket, ml_value_t *Result) {
}

static onion_connection_status ml_onion_websocket_callback(ml_onion_websocket_t *Websocket, onion_websocket *Handle, ssize_t DataReadyLength) {
	ml_stringbuffer_t Buffer[1] = {ML_STRINGBUFFER_INIT};
	if (DataReadyLength >= 0) {
		char Temp[128];
		while (DataReadyLength > 0) {
			int Request = DataReadyLength < 128 ? DataReadyLength : 128;
			int Actual = onion_websocket_read(Handle, Temp, Request);
			if (Actual < 0) {
				Websocket->Args[0] = ml_error("ReadError", "Error reading from websocket: %s", strerror(errno));
				ml_call((ml_state_t *)Websocket, Websocket->Callback, 1, Websocket->Args);
				return OCS_INTERNAL_ERROR;
			}
			ml_stringbuffer_write(Buffer, Temp, Actual);
			DataReadyLength -= Actual;
		}
		Websocket->Args[0] = ml_stringbuffer_get_value(Buffer);
		ml_call((ml_state_t *)Websocket, Websocket->Callback, 1, Websocket->Args);
		return OCS_NEED_MORE_DATA;
	} else {
		Websocket->Args[0] = MLNil;
		ml_call((ml_state_t *)Websocket, Websocket->Callback, 1, Websocket->Args);
		return OCS_CLOSE_CONNECTION;
	}
}

extern ml_type_t OnionWebsocketT[];

ML_FUNCTIONX(OnionWebsocket) {
	ML_CHECKX_ARG_COUNT(2);
	ML_CHECKX_ARG_TYPE(0, OnionRequestT);
	ML_CHECKX_ARG_TYPE(1, OnionResponseT);
	ml_onion_request_t *Request = (ml_onion_request_t *)Args[0];
	ml_onion_response_t *Response = (ml_onion_response_t *)Args[1];
	onion_websocket *Handle = onion_websocket_new(Request->Handle, Response->Handle);
	if (!Handle) ML_RETURN(MLNil);
	ml_onion_websocket_t *Websocket = new(ml_onion_websocket_t);
	Websocket->Base.Type = OnionWebsocketT;
	Websocket->Base.Context = Caller->Context;
	Websocket->Base.run = (ml_state_fn)ml_onion_websocket_run;
	Websocket->Handle = Handle;
	onion_websocket_set_userdata(Handle, Websocket, NULL);
	onion_websocket_set_callback(Websocket->Handle, (void *)ml_onion_websocket_callback);
	ML_RETURN(Websocket);
}

ML_TYPE(OnionWebsocketT, (), "onion-websocket",
	.Constructor = (ml_value_t *)OnionWebsocket
);

ML_METHOD("set_callback", OnionWebsocketT, MLFunctionT) {
	ml_onion_websocket_t *Websocket = (ml_onion_websocket_t *)Args[0];
	Websocket->Callback = Args[1];
	return Args[0];
}

static ML_ENUM2(OnionWebsocketOpcodeT, "onion::websocket_opcode",
	"Text", OWS_TEXT,
	"Binary", OWS_BINARY,
	"ConnectionClose", OWS_CONNECTION_CLOSE,
	"Ping", OWS_PING,
	"Pong", OWS_PONG
);

ML_METHOD("set_opcode", OnionWebsocketT, OnionWebsocketOpcodeT) {
	ml_onion_websocket_t *Websocket = (ml_onion_websocket_t *)Args[0];
	onion_websocket_set_opcode(Websocket->Handle, ml_enum_value_value(Args[1]));
	return Args[0];
}

ML_METHOD("write", OnionWebsocketT, MLStringT) {
	ml_onion_websocket_t *Websocket = (ml_onion_websocket_t *)Args[0];
	int Result = onion_websocket_write(Websocket->Handle, ml_string_value(Args[1]), ml_string_length(Args[1]));
	return ml_integer(Result);
}

void memory_allocation_error(const char *Message) {
	ONION_ERROR("memory failure: %s (%s)", Message, strerror(errno));
	exit(EXIT_FAILURE);
}

void *GC_calloc(size_t N, size_t Size) {
	return GC_malloc(N * Size);
}

ML_LIBRARY_ENTRY0(web_onion) {
	onion_low_initialize_memory_allocation(
		GC_malloc, GC_malloc_atomic, GC_calloc,
		GC_realloc, GC_strdup, GC_free,
		memory_allocation_error
	);
	onion_low_initialize_threads(
		GC_pthread_create, GC_pthread_join,
		GC_pthread_cancel, GC_pthread_detach,
		GC_pthread_exit, GC_pthread_sigmask
	);
#include "onion_init.c"
	stringmap_insert(OnionT->Exports, "mode", OnionModeT);
	stringmap_insert(OnionT->Exports, "url", OnionUrlT);
	stringmap_insert(OnionT->Exports, "handler", OnionHandlerT);
	stringmap_insert(OnionT->Exports, "websocket", OnionWebsocketT);
	stringmap_insert(OnionT->Exports, "connection_status", OnionConnectionStatusT);
	stringmap_insert(OnionT->Exports, "websocket_opcode", OnionWebsocketOpcodeT);
	Slot[0] = (ml_value_t *)OnionT;
}
