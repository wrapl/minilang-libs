#include <minilang/ml_library.h>
#include <minilang/ml_macros.h>
#include <minilang/ml_object.h>
#include <minilang/ml_stream.h>
#include <minilang/ml_logging.h>
#include <semaphore.h>
#include <curl/curl.h>

#undef ML_CATEGORY
#define ML_CATEGORY "net/curl"

typedef struct {
	void **Ptrs;
	int Space, Size;
} ptrset_t;

#define PTRSET_INIT {NULL, 0, 0}
#define PTRSET_INITIAL_SIZE 4

static void ptrset_insert(ptrset_t *Set, void *Ptr) {
	if (!Set->Space) {
		int Size = Set->Size + PTRSET_INITIAL_SIZE;
		void **Ptrs = anew(void *, Size);
		memcpy(Ptrs, Set->Ptrs, Set->Size * sizeof(void *));
		Ptrs[Set->Size] = Ptr;
		Set->Ptrs = Ptrs;
		Set->Size = Size;
		Set->Space += PTRSET_INITIAL_SIZE - 1;
		return;
	}
	void **Slot = Set->Ptrs;
	while (Slot[0]) ++Slot;
	Slot[0] = Ptr;
	--Set->Space;
}

static void ptrset_remove(ptrset_t *Set, void *Ptr) {
	for (void **Slot = Set->Ptrs, **Limit = Set->Ptrs + Set->Size; Slot < Limit; ++Slot) {
		if (Slot[0] == Ptr) {
			Slot[0] = NULL;
			++Set->Space;
			return;
		}
	}
}

typedef struct curl_multi_t curl_multi_t;
typedef struct curl_t curl_t;

typedef enum {
	CURL_ACTION_NONE,
	CURL_ACTION_ADD,
	CURL_ACTION_REMOVE,
	CURL_ACTION_PAUSE,
	CURL_ACTION_RESUME,
	CURL_ACTION_ABORT
} curl_action_t;

struct curl_multi_t {
	ml_type_t *Type;
	CURLM *Handle;
	curl_t *Queue;
	ml_scheduler_t *Scheduler;
	pthread_mutex_t Lock[1];
};

struct curl_t {
	ml_type_t *Type;
	ml_state_t *Caller;
	curl_t *Next;
	CURL *Handle;
	curl_multi_t *Multi;
	//ptrset_t Handlers[1];
	curl_action_t Action;
	char Error[CURL_ERROR_SIZE];
};

extern ml_type_t CurlT[];

/*static int progress_callback(curl_t *Curl, curl_off_t DLTotal, curl_off_t DLNow, curl_off_t ULTotal, curl_off_t ULNow) {
	// TODO: Check and call different progress fn
	curl_easy_pause(Curl->Handle, Curl->Pause);
	return Curl->Abort;
}

static void curl_state_run(curl_t *Curl, ml_value_t *Value) {
	if (ml_is_error(Value)) Curl->Abort = 1;
}*/

ML_FUNCTIONX(Curl) {
//>curl
// Returns a new Curl easy instance.
	curl_t *Curl = new(curl_t);
	Curl->Type = CurlT;
	Curl->Handle = curl_easy_init();
	Curl->Action = CURL_ACTION_NONE;
	curl_easy_setopt(Curl->Handle, CURLOPT_PRIVATE, Curl);
	//curl_easy_setopt(Curl->Handle, CURLOPT_XFERINFOFUNCTION, progress_callback);
	//curl_easy_setopt(Curl->Handle, CURLOPT_XFERINFODATA, Curl);
	curl_easy_setopt(Curl->Handle, CURLOPT_NOPROGRESS, 1);
	curl_easy_setopt(Curl->Handle, CURLOPT_ERRORBUFFER, Curl->Error);
	ML_RETURN(Curl);
}

ML_TYPE(CurlT, (), "curl",
	.Constructor = (ml_value_t *)Curl
);

#include "curl_options.c"

ML_METHOD("set", CurlT, CurlOptionT, MLNilT) {
//<Curl
//<Option
//<nil
//>curl
// Sets :mini:`Option` in :mini:`Curl` to :mini:`nil`.
	curl_t *Curl = (curl_t *)Args[0];
	if (!Curl->Handle) return ml_error("CurlError", "Curl handle already closed");
	CURLoption Option = ml_enum_value_value(Args[1]);
	curl_easy_setopt(Curl->Handle, Option, 0);
	return (ml_value_t *)Curl;
}

ML_METHOD("set", CurlT, CurlOptionIntegerT, MLIntegerT) {
//<Curl
//<Option
//<Value
//>curl
// Sets :mini:`Option` in :mini:`Curl` to :mini:`Value`.
	curl_t *Curl = (curl_t *)Args[0];
	if (!Curl->Handle) return ml_error("CurlError", "Curl handle already closed");
	CURLoption Option = ml_enum_value_value(Args[1]);
	curl_easy_setopt(Curl->Handle, Option, ml_integer_value(Args[2]));
	return (ml_value_t *)Curl;
}

ML_METHOD("set", CurlT, CurlOptionEnumT, MLEnumValueT) {
//<Curl
//<Option
//<Value
//>curl
// Sets :mini:`Option` in :mini:`Curl` to :mini:`Value`.
	curl_t *Curl = (curl_t *)Args[0];
	if (!Curl->Handle) return ml_error("CurlError", "Curl handle already closed");
	CURLoption Option = ml_enum_value_value(Args[1]);
	curl_easy_setopt(Curl->Handle, Option, ml_enum_value_value(Args[2]));
	return (ml_value_t *)Curl;
}

ML_METHOD("set", CurlT, CurlOptionIntegerT, MLBooleanT) {
//<Curl
//<Option
//<Value
//>curl
// Sets :mini:`Option` in :mini:`Curl` to :mini:`Value`.
	curl_t *Curl = (curl_t *)Args[0];
	if (!Curl->Handle) return ml_error("CurlError", "Curl handle already closed");
	CURLoption Option = ml_enum_value_value(Args[1]);
	curl_easy_setopt(Curl->Handle, Option, ml_boolean_value(Args[2]));
	return (ml_value_t *)Curl;
}

ML_METHOD("set", CurlT, CurlOptionStringT, MLStringT) {
//<Curl
//<Option
//<Value
//>curl
// Sets :mini:`Option` in :mini:`Curl` to :mini:`Value`.
	curl_t *Curl = (curl_t *)Args[0];
	if (!Curl->Handle) return ml_error("CurlError", "Curl handle already closed");
	CURLoption Option = ml_enum_value_value(Args[1]);
	curl_easy_setopt(Curl->Handle, Option, ml_string_value(Args[2]));
	return (ml_value_t *)Curl;
}

ML_METHOD("set", CurlT, CurlOptionSetT, MLListT) {
//<Curl
//<Option
//<Value
//>curl
// Sets :mini:`Option` in :mini:`Curl` to :mini:`Value`.
	curl_t *Curl = (curl_t *)Args[0];
	if (!Curl->Handle) return ml_error("CurlError", "Curl handle already closed");
	ML_LIST_FOREACH(Args[2], Iter) {
		if (!ml_is(Iter->Value, MLStringT)) return ml_error("CurlError", "Expected list of strings");
	}
	CURLoption Option = ml_enum_value_value(Args[1]);
	struct curl_slist *List = NULL;
	ML_LIST_FOREACH(Args[2], Iter) {
		List = curl_slist_append(List, ml_string_value(Iter->Value));
	}
	curl_easy_setopt(Curl->Handle, Option, List);
	return (ml_value_t *)Curl;
}

typedef struct {
	ml_state_t Base;
	curl_t *Curl;
	ml_value_t *Stream, *Result;
	char *Buffer;
	union {
		typeof(ml_stream_read) *read;
		typeof(ml_stream_write) *write;
	};
	sem_t Ready[1];
	size_t Size;
} stream_callback_t;

static void stream_done(stream_callback_t *State, ml_value_t *Value) {
	State->Result = Value;
	sem_post(State->Ready);
}

static void stream_read_start(stream_callback_t *State, ml_value_t *Value) {
	State->Base.run = (ml_state_fn)stream_done;
	return State->read((ml_state_t *)State, State->Stream, State->Buffer, State->Size);
}

static void stream_write_start(stream_callback_t *State, ml_value_t *Value) {
	State->Base.run = (ml_state_fn)stream_done;
	return State->write((ml_state_t *)State, State->Stream, State->Buffer, State->Size);
}

static size_t stream_read_callback(char *Buffer, size_t Size, size_t N, stream_callback_t *State) {
	State->Base.run = (ml_state_fn)stream_read_start;
	State->Buffer = Buffer;
	State->Size = Size * N;
	ml_scheduler_t *Scheduler = State->Curl->Multi->Scheduler;
	Scheduler->add(Scheduler, (ml_state_t *)State, MLNil);
	sem_wait(State->Ready);
	if (ml_is_error(State->Result)) return CURL_READFUNC_ABORT;
	if (State->Result == MLNil) return 0;
	return ml_integer_value(State->Result);
}

static size_t stream_write_callback(char *Buffer, size_t Size, size_t N, stream_callback_t *State) {
	State->Base.run = (ml_state_fn)stream_write_start;
	State->Buffer = Buffer;
	State->Size = Size * N;
	ml_scheduler_t *Scheduler = State->Curl->Multi->Scheduler;
	Scheduler->add(Scheduler, (ml_state_t *)State, MLNil);
	sem_wait(State->Ready);
	if (ml_is_error(State->Result)) return CURL_WRITEFUNC_ERROR;
	if (State->Result == MLNil) return 0;
	return ml_integer_value(State->Result);
}

ML_METHODX("set", CurlT, CurlOptionFunctionT, MLStreamT) {
//<Curl
//<Option
//<Value
//>curl
// Sets :mini:`Option` in :mini:`Curl` to :mini:`Value`.
	curl_t *Curl = (curl_t *)Args[0];
	if (!Curl->Handle) ML_ERROR("CurlError", "Curl handle already closed");
	CURLoption Option = ml_enum_value_value(Args[1]);
	stream_callback_t *State = new(stream_callback_t);
	State->Base.Context = Caller->Context;
	State->Curl = Curl;
	State->Stream = Args[2];
	sem_init(State->Ready, 0, 0);
	switch (Option) {
	case CURLOPT_WRITEFUNCTION:
		State->write = ml_typed_fn_get(ml_typeof(State->Stream), ml_stream_write);
		curl_easy_setopt(Curl->Handle, CURLOPT_WRITEFUNCTION, stream_write_callback);
		curl_easy_setopt(Curl->Handle, CURLOPT_WRITEDATA, State);
		break;
	case CURLOPT_HEADERFUNCTION:
		State->write = ml_typed_fn_get(ml_typeof(State->Stream), ml_stream_write);
		curl_easy_setopt(Curl->Handle, CURLOPT_HEADERFUNCTION, stream_write_callback);
		curl_easy_setopt(Curl->Handle, CURLOPT_HEADERDATA, State);
		break;
	case CURLOPT_READFUNCTION:
		State->read = ml_typed_fn_get(ml_typeof(State->Stream), ml_stream_read);
		curl_easy_setopt(Curl->Handle, CURLOPT_READFUNCTION, stream_read_callback);
		curl_easy_setopt(Curl->Handle, CURLOPT_READDATA, State);
		break;
	default:
		ML_ERROR("CurlError", "Unsupported option for stream");
	}
	//ptrset_insert(Curl->Handlers, State);
	ML_RETURN(Curl);
}

static size_t stringbuffer_read_callback(char *Buffer, size_t Size, size_t N, ml_stringbuffer_t *StringBuffer) {
	return ml_stringbuffer_read(StringBuffer, Buffer, Size * N);
}

static size_t stringbuffer_write_callback(char *Buffer, size_t Size, size_t N, ml_stringbuffer_t *StringBuffer) {
	return ml_stringbuffer_write(StringBuffer, Buffer, Size * N);
}

ML_METHODX("set", CurlT, CurlOptionFunctionT, MLStringBufferT) {
//<Curl
//<Option
//<Value
//>curl
// Sets :mini:`Option` in :mini:`Curl` to :mini:`Value`.
	curl_t *Curl = (curl_t *)Args[0];
	if (!Curl->Handle) ML_ERROR("CurlError", "Curl handle already closed");
	CURLoption Option = ml_enum_value_value(Args[1]);
	switch (Option) {
	case CURLOPT_WRITEFUNCTION:
		curl_easy_setopt(Curl->Handle, CURLOPT_WRITEFUNCTION, stringbuffer_write_callback);
		curl_easy_setopt(Curl->Handle, CURLOPT_WRITEDATA, Args[2]);
		break;
	case CURLOPT_HEADERFUNCTION:
		curl_easy_setopt(Curl->Handle, CURLOPT_HEADERFUNCTION, stringbuffer_write_callback);
		curl_easy_setopt(Curl->Handle, CURLOPT_HEADERDATA, Args[2]);
		break;
	case CURLOPT_READFUNCTION:
		curl_easy_setopt(Curl->Handle, CURLOPT_READFUNCTION, stringbuffer_read_callback);
		curl_easy_setopt(Curl->Handle, CURLOPT_READDATA, Args[2]);
		break;
	default:
		ML_ERROR("CurlError", "Unsupported option for stream");
	}
	//ptrset_insert(Curl->Handlers, Args[2]);
	ML_RETURN(Curl);
}

typedef struct {
	ml_state_t Base;
	curl_t *Curl;
	ml_value_t *Fn, *Result;
	sem_t Ready[1];
} function_callback_t;

static void function_done(function_callback_t *State, ml_value_t *Value) {
	State->Result = Value;
	sem_post(State->Ready);
}

static void function_start(function_callback_t *State, ml_value_t *Value) {
	State->Base.run = (ml_state_fn)function_done;
	return ml_call((ml_state_t *)State, State->Fn, 1, &State->Result);
}

static size_t function_read_callback(char *Buffer, size_t Size, size_t N, function_callback_t *State) {
	State->Base.run = (ml_state_fn)function_start;
	State->Result = ml_address(Buffer, Size * N);
	ml_scheduler_t *Scheduler = State->Curl->Multi->Scheduler;
	Scheduler->add(Scheduler, (ml_state_t *)State, MLNil);
	sem_wait(State->Ready);
	if (ml_is_error(State->Result)) return CURL_READFUNC_ABORT;
	if (State->Result == MLNil) return 0;
	return ml_integer_value(State->Result);
}

static size_t function_write_callback(char *Buffer, size_t Size, size_t N, function_callback_t *State) {
	State->Base.run = (ml_state_fn)function_start;
	State->Result = ml_buffer(Buffer, Size * N);
	ml_scheduler_t *Scheduler = State->Curl->Multi->Scheduler;
	Scheduler->add(Scheduler, (ml_state_t *)State, MLNil);
	sem_wait(State->Ready);
	if (ml_is_error(State->Result)) return CURL_WRITEFUNC_ERROR;
	if (State->Result == MLNil) return 0;
	return ml_integer_value(State->Result);
}

ML_METHODX("set", CurlT, CurlOptionFunctionT, MLFunctionT) {
//<Curl
//<Option
//<Value
//>curl
// Sets :mini:`Option` in :mini:`Curl` to :mini:`Value`.
	curl_t *Curl = (curl_t *)Args[0];
	if (!Curl->Handle) ML_ERROR("CurlError", "Curl handle already closed");
	CURLoption Option = ml_enum_value_value(Args[1]);
	function_callback_t *State = new(function_callback_t);
	State->Base.Context = Caller->Context;
	State->Curl = Curl;
	State->Fn = Args[2];
	sem_init(State->Ready, 0, 0);
	switch (Option) {
	case CURLOPT_WRITEFUNCTION:
		curl_easy_setopt(Curl->Handle, CURLOPT_WRITEFUNCTION, function_write_callback);
		curl_easy_setopt(Curl->Handle, CURLOPT_WRITEDATA, State);
		break;
	case CURLOPT_HEADERFUNCTION:
		curl_easy_setopt(Curl->Handle, CURLOPT_HEADERFUNCTION, function_write_callback);
		curl_easy_setopt(Curl->Handle, CURLOPT_HEADERDATA, State);
		break;
	case CURLOPT_READFUNCTION:
		curl_easy_setopt(Curl->Handle, CURLOPT_READFUNCTION, function_read_callback);
		curl_easy_setopt(Curl->Handle, CURLOPT_READDATA, State);
		break;
	default:
		ML_ERROR("CurlError", "Unsupported option for callback");
	}
	//ptrset_insert(Curl->Handlers, State);
	ML_RETURN(Curl);
}

static curl_multi_t DefaultMulti[1];

static void *multi_thread_fn(void *Arg) {
	curl_multi_t *Multi = (curl_multi_t *)Arg;
	for (;;) {
		CURLMcode Result = curl_multi_poll(Multi->Handle, NULL, 0, 1000, NULL);
		if (Result != CURLM_OK) {
			ML_LOG_ERROR(NULL, "Error polling curl handle: %d", Result);
			return NULL;
		}
		pthread_mutex_lock(Multi->Lock);
		curl_t *Queue = Multi->Queue;
		Multi->Queue = NULL;
		pthread_mutex_unlock(Multi->Lock);
		for (curl_t *Curl = Queue; Curl; Curl = Curl->Next) {
			//ML_LOG_INFO(NULL, "Updating Curl instance in multi: %lx -> %d", Curl, Curl->Action);
			switch (Curl->Action) {
			case CURL_ACTION_NONE:
				break;
			case CURL_ACTION_ADD:
				curl_multi_add_handle(Multi->Handle, Curl->Handle);
				Curl->Multi = Multi;
				break;
			case CURL_ACTION_REMOVE:
				curl_multi_remove_handle(Multi->Handle, Curl->Handle);
				Curl->Multi = NULL;
				// Possibly scheduler Curl->Caller with an error.
				break;
			case CURL_ACTION_PAUSE:
				curl_easy_pause(Curl->Handle, CURLPAUSE_ALL);
				break;
			case CURL_ACTION_RESUME:
				curl_easy_pause(Curl->Handle, CURLPAUSE_CONT);
				break;
			case CURL_ACTION_ABORT:
				curl_multi_remove_handle(Multi->Handle, Curl->Handle);
				Curl->Multi = NULL;
				// Possibly scheduler Curl->Caller with an error.
				break;
			}
		}
		int Running;
		Result = curl_multi_perform(Multi->Handle, &Running);
		if (Result != CURLM_OK) {
			ML_LOG_ERROR(NULL, "Error polling curl handle: %d", Result);
			return NULL;
		}
		int Remaining;
		CURLMsg *Message;
		ml_scheduler_t *Scheduler = Multi->Scheduler;
		while ((Message = curl_multi_info_read(Multi->Handle, &Remaining))) {
			if (Message->msg == CURLMSG_DONE) {
				curl_t *Curl = NULL;
				curl_easy_getinfo(Message->easy_handle, CURLINFO_PRIVATE, &Curl);
				ml_value_t *Result = MLNil;
				if (Message->data.result != CURLE_OK) {
					Result = ml_error("CurlError", "%s", Curl->Error);
				}
				Scheduler->add(Scheduler, Curl->Caller, Result);
				Curl->Caller = NULL;
				curl_multi_remove_handle(Multi->Handle, Curl->Handle);
			}
		}
	}
	return NULL;
}

ML_METHODX("perform", CurlT) {
	curl_t *Curl = (curl_t *)Args[0];
	if (!Curl->Handle) ML_ERROR("CurlError", "Curl handle already closed");
	if (Curl->Caller) ML_ERROR("CurlError", "Curl handle cannot be used concurrently");
	Curl->Caller = Caller;
	Curl->Action = CURL_ACTION_ADD;
	pthread_mutex_lock(DefaultMulti->Lock);
	Curl->Next = DefaultMulti->Queue;
	DefaultMulti->Queue = Curl;
	DefaultMulti->Scheduler = ml_context_get_scheduler(Caller->Context);
	pthread_mutex_unlock(DefaultMulti->Lock);
	curl_multi_wakeup(DefaultMulti->Handle);
}

ML_METHOD("reset", CurlT) {
	curl_t *Curl = (curl_t *)Args[0];
	if (!Curl->Handle) return ml_error("CurlError", "Curl handle already closed");
	if (Curl->Caller) return ml_error("CurlError", "Curl handle cannot be used concurrently");
	curl_easy_reset(Curl->Handle);
	return (ml_value_t *)Curl;
}

ML_METHOD("cleanup", CurlT) {
	curl_t *Curl = (curl_t *)Args[0];
	if (!Curl->Handle) return ml_error("CurlError", "Curl handle already closed");
	if (Curl->Caller) return ml_error("CurlError", "Curl handle cannot be used concurrently");
	curl_easy_cleanup(Curl->Handle);
	Curl->Handle = NULL;
	return MLNil;
}

ML_METHOD("get", CurlT, CurlInfoIntegerT) {
	curl_t *Curl = (curl_t *)Args[0];
	if (!Curl->Handle) return ml_error("CurlError", "Curl handle already closed");
	CURLINFO Info = ml_enum_value_value(Args[1]);
	long Value;
	if (curl_easy_getinfo(Curl->Handle, Info, &Value) != CURLE_OK) return ml_error("CurlError", "Error fetching info");
	return ml_integer(Value);
}

ML_METHOD("get", CurlT, CurlInfoRealT) {
	curl_t *Curl = (curl_t *)Args[0];
	if (!Curl->Handle) return ml_error("CurlError", "Curl handle already closed");
	CURLINFO Info = ml_enum_value_value(Args[1]);
	double Value;
	if (curl_easy_getinfo(Curl->Handle, Info, &Value) != CURLE_OK) return ml_error("CurlError", "Error fetching info");
	return ml_real(Value);
}

ML_METHOD("get", CurlT, CurlInfoStringT) {
	curl_t *Curl = (curl_t *)Args[0];
	if (!Curl->Handle) return ml_error("CurlError", "Curl handle already closed");
	CURLINFO Info = ml_enum_value_value(Args[1]);
	const char *Value;
	if (curl_easy_getinfo(Curl->Handle, Info, &Value) != CURLE_OK) return ml_error("CurlError", "Error fetching info");
	return ml_string_copy(Value, -1);
}

ML_METHOD("get", CurlT, CurlInfoSetT) {
	curl_t *Curl = (curl_t *)Args[0];
	if (!Curl->Handle) return ml_error("CurlError", "Curl handle already closed");
	CURLINFO Info = ml_enum_value_value(Args[1]);
	struct curl_slist *Value;
	if (curl_easy_getinfo(Curl->Handle, Info, &Value) != CURLE_OK) return ml_error("CurlError", "Error fetching info");
	ml_value_t *Result = ml_list();
	for (struct curl_slist *Node = Value; Node; Node = Node->next) {
		ml_list_put(Result, ml_string_copy(Node->data, -1));
	}
	curl_slist_free_all(Value);
	return Result;
}

ML_ENUM2(CurlUseSslT, "curl::usessl",
	"None", CURLUSESSL_NONE,
	"Try", CURLUSESSL_TRY,
	"Control", CURLUSESSL_CONTROL,
	"All", CURLUSESSL_ALL
);

static void nop_free(void *Ptr) {}

static void *GC_calloc(size_t N, size_t S) {
	return GC_malloc(N * S);
}

ML_LIBRARY_ENTRY0(net_curl) {
	curl_global_init_mem(CURL_GLOBAL_DEFAULT,
		GC_malloc, nop_free, GC_realloc,
		GC_strdup, GC_calloc
	);
	DefaultMulti->Handle = curl_multi_init();
	pthread_mutex_init(DefaultMulti->Lock, NULL);
	DefaultMulti->Queue = NULL;
	pthread_t Thread;
	pthread_create(&Thread, NULL, multi_thread_fn, DefaultMulti);
	pthread_setname_np(Thread, "curl");
#include "curl_init.c"
	stringmap_insert(CurlT->Exports, "option", CurlOptionT);
	stringmap_insert(CurlT->Exports, "info", CurlInfoT);
	stringmap_insert(CurlT->Exports, "usessl", CurlUseSslT);
	Slot[0] = (ml_value_t *)CurlT;
}

