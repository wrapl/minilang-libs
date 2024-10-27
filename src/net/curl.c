#include <minilang/ml_library.h>
#include <minilang/ml_macros.h>
#include <minilang/ml_object.h>
#include <minilang/ml_stream.h>
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

typedef struct callback_state_t callback_state_t;

typedef struct {
	ml_state_t Base;
	CURL *Handle;
	ml_scheduler_t *Scheduler;
	ptrset_t Handlers[1];
	int Pause, Abort;
} curl_t;

struct callback_state_t {
	ml_state_t Base;
	curl_t *Curl;
	ml_value_t *Fn, *Result;
};

extern ml_type_t CurlT[];

static int progress_callback(curl_t *Curl, curl_off_t DLTotal, curl_off_t DLNow, curl_off_t ULTotal, curl_off_t ULNow) {
	// TODO: Check and call different progress fn
	curl_easy_pause(Curl->Handle, Curl->Pause);
	return Curl->Abort;
}

static void curl_state_run(curl_t *Curl, ml_value_t *Value) {
	if (ml_is_error(Value)) Curl->Abort = 1;
}

ML_FUNCTIONX(Curl) {
	curl_t *Curl = new(curl_t);
	Curl->Base.Type = CurlT;
	Curl->Base.Context = Caller->Context;
	Curl->Base.run = (ml_state_fn)curl_state_run;
	Curl->Handle = curl_easy_init();
	Curl->Pause = CURLPAUSE_CONT;
	curl_easy_setopt(Curl->Handle, CURLOPT_PRIVATE, Curl);
	curl_easy_setopt(Curl->Handle, CURLOPT_XFERINFOFUNCTION, progress_callback);
	curl_easy_setopt(Curl->Handle, CURLOPT_XFERINFODATA, Curl);
	curl_easy_setopt(Curl->Handle, CURLOPT_NOPROGRESS, 0);
	ML_RETURN(Curl);
}

ML_TYPE(CurlT, (), "curl",
	.Constructor = (ml_value_t *)Curl
);

#include "curl_options.c"

ML_METHOD("set", CurlT, CurlOptionT, MLNilT) {
	curl_t *Curl = (curl_t *)Args[0];
	CURLoption Option = ml_enum_value_value(Args[1]);
	curl_easy_setopt(Curl->Handle, Option, 0);
	return (ml_value_t *)Curl;
}

ML_METHOD("set", CurlT, CurlOptionIntegerT, MLIntegerT) {
	curl_t *Curl = (curl_t *)Args[0];
	CURLoption Option = ml_enum_value_value(Args[1]);
	curl_easy_setopt(Curl->Handle, Option, ml_integer_value(Args[2]));
	return (ml_value_t *)Curl;
}

ML_METHOD("set", CurlT, CurlOptionIntegerT, MLBooleanT) {
	curl_t *Curl = (curl_t *)Args[0];
	CURLoption Option = ml_enum_value_value(Args[1]);
	curl_easy_setopt(Curl->Handle, Option, ml_boolean_value(Args[2]));
	return (ml_value_t *)Curl;
}

ML_METHOD("set", CurlT, CurlOptionStringT, MLStringT) {
	curl_t *Curl = (curl_t *)Args[0];
	CURLoption Option = ml_enum_value_value(Args[1]);
	curl_easy_setopt(Curl->Handle, Option, ml_string_value(Args[2]));
	return (ml_value_t *)Curl;
}

ML_METHOD("set", CurlT, CurlOptionSetT, MLListT) {
	curl_t *Curl = (curl_t *)Args[0];
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

static void read_state_run(callback_state_t *State, ml_value_t *Value) {
	curl_t *Curl = State->Curl;
	if (ml_is_error(Value)) {
		Curl->Abort = 1;
	} else {
		Curl->Pause &= ~CURLPAUSE_SEND;
		State->Result = Value;
	}
}

static void write_state_run(callback_state_t *State, ml_value_t *Value) {
	curl_t *Curl = State->Curl;
	if (ml_is_error(Value)) {
		Curl->Abort = 1;
	} else {
		Curl->Pause &= ~CURLPAUSE_RECV;
		State->Result = Value;
	}
}

static size_t stream_read_callback(char *Buffer, size_t Size, size_t N, callback_state_t *State) {
	ml_value_t *Result = State->Result;
	if (!Result) {
		ml_scheduler_join(State->Curl->Scheduler);
		ml_stream_read((ml_state_t *)State, State->Fn, Buffer, Size * N);
		ml_scheduler_split(State->Curl->Scheduler);
		if (!State->Result) {
			State->Curl->Pause |= CURLPAUSE_SEND;
			return CURL_READFUNC_PAUSE;
		} else {
			Result = State->Result;
		}
	}
	State->Result = NULL;
	if (ml_is_error(Result)) return CURL_READFUNC_ABORT;
	if (Result == MLNil) return 0;
	return ml_integer_value(Result);
}

static size_t stream_write_callback(char *Buffer, size_t Size, size_t N, callback_state_t *State) {
	ml_value_t *Result = State->Result;
	if (!Result) {
		ml_scheduler_join(State->Curl->Scheduler);
		ml_stream_write((ml_state_t *)State, State->Fn, Buffer, Size * N);
		ml_scheduler_split(State->Curl->Scheduler);
		if (!State->Result) {
			State->Curl->Pause |= CURLPAUSE_RECV;
			return CURL_WRITEFUNC_PAUSE;
		} else {
			Result = State->Result;
		}
	}
	State->Result = NULL;
	if (ml_is_error(Result)) return CURL_WRITEFUNC_ERROR;
	if (Result == MLNil) return 0;
	return ml_integer_value(Result);
}

ML_METHODX("set", CurlT, CurlOptionFunctionT, MLStreamT) {
	curl_t *Curl = (curl_t *)Args[0];
	CURLoption Option = ml_enum_value_value(Args[1]);
	callback_state_t *State = new(callback_state_t);
	State->Base.Context = Caller->Context;
	State->Curl = Curl;
	State->Fn = Args[2];
	switch (Option) {
	case CURLOPT_WRITEFUNCTION:
		State->Base.run = (ml_state_fn)write_state_run;
		curl_easy_setopt(Curl->Handle, CURLOPT_WRITEFUNCTION, stream_write_callback);
		curl_easy_setopt(Curl->Handle, CURLOPT_WRITEDATA, State);
		break;
	case CURLOPT_HEADERFUNCTION:
		State->Base.run = (ml_state_fn)write_state_run;
		curl_easy_setopt(Curl->Handle, CURLOPT_HEADERFUNCTION, stream_write_callback);
		curl_easy_setopt(Curl->Handle, CURLOPT_HEADERDATA, State);
		break;
	case CURLOPT_READFUNCTION:
		State->Base.run = (ml_state_fn)read_state_run;
		curl_easy_setopt(Curl->Handle, CURLOPT_READFUNCTION, stream_read_callback);
		curl_easy_setopt(Curl->Handle, CURLOPT_READDATA, State);
		break;
	default:
		ML_ERROR("CurlError", "Unsupported option for stream");
	}
	ptrset_insert(Curl->Handlers, State);
	ML_RETURN(Curl);
}

static size_t function_read_callback(char *Buffer, size_t Size, size_t N, callback_state_t *State) {
	ml_value_t *Result = State->Result;
	if (!Result) {
		ml_value_t **Args = ml_alloc_args(1);
		Args[0] = ml_buffer(Buffer, Size * N);
		ml_scheduler_join(State->Curl->Scheduler);
		ml_call((ml_state_t *)State, State->Fn, 1, Args);
		ml_scheduler_split(State->Curl->Scheduler);
		if (!State->Result) {
			State->Curl->Pause |= CURLPAUSE_SEND;
			return CURL_READFUNC_PAUSE;
		} else {
			Result = State->Result;
		}
	}
	State->Result = NULL;
	if (ml_is_error(Result)) return CURL_READFUNC_ABORT;
	if (Result == MLNil) return 0;
	return ml_integer_value(Result);
}

static size_t function_write_callback(char *Buffer, size_t Size, size_t N, callback_state_t *State) {
	ml_value_t *Result = State->Result;
	if (!Result) {
		ml_value_t **Args = ml_alloc_args(1);
		Args[0] = ml_string_unchecked(Buffer, Size * N);
		ml_scheduler_join(State->Curl->Scheduler);
		ml_call((ml_state_t *)State, State->Fn, 1, Args);
		ml_scheduler_split(State->Curl->Scheduler);
		if (!State->Result) {
			State->Curl->Pause |= CURLPAUSE_RECV;
			return CURL_WRITEFUNC_PAUSE;
		} else {
			Result = State->Result;
		}
	}
	State->Result = NULL;
	if (ml_is_error(Result)) return CURL_WRITEFUNC_ERROR;
	if (Result == MLNil) return 0;
	return ml_integer_value(Result);
}

ML_METHODX("set", CurlT, CurlOptionFunctionT, MLFunctionT) {
	curl_t *Curl = (curl_t *)Args[0];
	CURLoption Option = ml_enum_value_value(Args[1]);
	callback_state_t *State = new(callback_state_t);
	State->Base.Context = Caller->Context;
	State->Curl = Curl;
	State->Fn = Args[2];
	switch (Option) {
	case CURLOPT_WRITEFUNCTION:
		State->Base.run = (ml_state_fn)write_state_run;
		curl_easy_setopt(Curl->Handle, CURLOPT_WRITEFUNCTION, function_write_callback);
		curl_easy_setopt(Curl->Handle, CURLOPT_WRITEDATA, State);
		break;
	case CURLOPT_HEADERFUNCTION:
		State->Base.run = (ml_state_fn)write_state_run;
		curl_easy_setopt(Curl->Handle, CURLOPT_HEADERFUNCTION, function_write_callback);
		curl_easy_setopt(Curl->Handle, CURLOPT_HEADERDATA, State);
		break;
	case CURLOPT_READFUNCTION:
		State->Base.run = (ml_state_fn)read_state_run;
		curl_easy_setopt(Curl->Handle, CURLOPT_READFUNCTION, function_read_callback);
		curl_easy_setopt(Curl->Handle, CURLOPT_READDATA, State);
		break;
	default:
		ML_ERROR("CurlError", "Unsupported option for callback");
	}
	ptrset_insert(Curl->Handlers, State);
	ML_RETURN(Curl);
}

ML_METHODX("perform", CurlT) {
	curl_t *Curl = (curl_t *)Args[0];
	if (Curl->Scheduler) ML_ERROR("CurlError", "Curl handle cannot be used concurrently");
	Curl->Scheduler = ml_context_get_scheduler(Caller->Context);
	ml_scheduler_split(Curl->Scheduler);
	curl_easy_perform(Curl->Handle);
	ml_scheduler_join(Curl->Scheduler);
	Curl->Scheduler = NULL;
	ML_RETURN(Curl);
}

static void nop_free(void *Ptr) {}

static void *GC_calloc(size_t N, size_t S) {
	return GC_malloc(N * S);
}

ML_LIBRARY_ENTRY0(net_curl) {
	curl_global_init_mem(CURL_GLOBAL_DEFAULT,
		GC_malloc, nop_free, GC_realloc,
		GC_strdup, GC_calloc
	);
#include "curl_init.c"
	stringmap_insert(CurlT->Exports, "option", CurlOptionT);
	Slot[0] = (ml_value_t *)CurlT;
}

