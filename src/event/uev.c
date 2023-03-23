#include <minilang/ml_library.h>
#include <minilang/ml_macros.h>
#include <minilang/ml_stream.h>
#include <minilang/ml_object.h>
#include <uev/uev.h>

typedef struct {
	ml_type_t *Type;
	uev_ctx_t Handle[1];
	int Running;
} ml_uev_t;

ML_TYPE(UevT, (), "uev");

ML_METHOD(UevT) {
	ml_uev_t *Context = new(ml_uev_t);
	Context->Type = UevT;
	uev_init(Context->Handle);
	return (ml_value_t *)Context;
}

ML_METHOD("run", UevT) {
	ml_uev_t *Context = (ml_uev_t *)Args[0];
	Context->Running = 1;
	do {
		ml_queued_state_t Queued = ml_default_queue_next();
		if (Queued.State) {
			uev_run(Context->Handle, UEV_ONCE | UEV_NONBLOCK);
			Queued.State->run(Queued.State, Queued.Value);
		} else {
			uev_run(Context->Handle, UEV_ONCE);
		}
	} while (Context->Running);
	return MLNil;
}

ML_METHOD("exit", UevT) {
	ml_uev_t *Context = (ml_uev_t *)Args[0];
	Context->Running = 0;
	uev_exit(Context->Handle);
	return MLNil;
}

ML_FLAGS2(UevFlagsT, "uev::flags",
	"Err", UEV_ERROR,
	"Read", UEV_READ,
	"Write", UEV_WRITE,
	"Pri", UEV_PRI,
	"Hup", UEV_HUP,
	"RdHup", UEV_RDHUP,
	"Edge", UEV_EDGE,
	"Once", UEV_ONESHOT
);

typedef struct {
	ml_state_t Base;
	ml_value_t *Function;
	int (*start)(uev_t *);
	int (*stop)(uev_t *);
	uev_t Handle[1];
} ml_uev_event_t;

ML_TYPE(UevEventT, (), "uev::event");

ML_METHOD("start", UevEventT) {
	ml_uev_event_t *Event = (ml_uev_event_t *)Args[0];
	return ml_integer(Event->start(Event->Handle));
}

ML_METHOD("stop", UevEventT) {
	ml_uev_event_t *Event = (ml_uev_event_t *)Args[0];
	return ml_integer(Event->stop(Event->Handle));
}

static void ml_uev_event_run(ml_uev_event_t *State, ml_value_t *Value) {
	// TODO: check for errors and send somewhere
}

static void ml_uev_callback(uev_t *Handle, void *Data, int Events) {
	ml_uev_event_t *Event = (ml_uev_event_t *)Data;
	ml_value_t **Args = ml_alloc_args(1);
	Args[0] = ml_flags_value(UevFlagsT, Events);
	return ml_call((ml_state_t *)Event, Event->Function, 1, Args);
}

ML_METHODX("io", UevT, MLStreamFdT, UevFlagsT, MLFunctionT) {
	ml_uev_t *Context = (ml_uev_t *)Args[0];
	int Fd = ml_fd_stream_fd(Args[1]);
	int Flags = ml_flags_value_value(Args[2]);
	ml_uev_event_t *Event = new(ml_uev_event_t);
	Event->Base.Type = UevEventT;
	Event->Base.Context = Caller->Context;
	Event->Base.run = (ml_state_fn)ml_uev_event_run;
	Event->Function = Args[3];
	Event->start = uev_io_start;
	Event->stop = uev_io_stop;
	uev_io_init(Context->Handle, Event->Handle, ml_uev_callback, Event, Fd, Flags);
	ML_RETURN(Event);
}

ML_METHODX("timer", UevT, MLIntegerT, MLFunctionT) {
	ml_uev_t *Context = (ml_uev_t *)Args[0];
	int Timeout = ml_integer_value(Args[1]);
	ml_uev_event_t *Event = new(ml_uev_event_t);
	Event->Base.Type = UevEventT;
	Event->Base.Context = Caller->Context;
	Event->Base.run = (ml_state_fn)ml_uev_event_run;
	Event->Function = Args[2];
	Event->start = uev_timer_start;
	Event->stop = uev_timer_stop;
	uev_timer_init(Context->Handle, Event->Handle, ml_uev_callback, Event, Timeout, 0);
	ML_RETURN(Event);
}

ML_METHODX("timer", UevT, MLIntegerT, MLIntegerT, MLFunctionT) {
	ml_uev_t *Context = (ml_uev_t *)Args[0];
	int Timeout = ml_integer_value(Args[1]);
	int Period = ml_integer_value(Args[2]);
	ml_uev_event_t *Event = new(ml_uev_event_t);
	Event->Base.Type = UevEventT;
	Event->Base.Context = Caller->Context;
	Event->Base.run = (ml_state_fn)ml_uev_event_run;
	Event->Function = Args[3];
	Event->start = uev_timer_start;
	Event->stop = uev_timer_stop;
	uev_timer_init(Context->Handle, Event->Handle, ml_uev_callback, Event, Timeout, Period);
	ML_RETURN(Event);
}

ML_METHODX("event", UevT, MLFunctionT) {
	ml_uev_t *Context = (ml_uev_t *)Args[0];
	ml_uev_event_t *Event = new(ml_uev_event_t);
	Event->Base.Type = UevEventT;
	Event->Base.Context = Caller->Context;
	Event->Base.run = (ml_state_fn)ml_uev_event_run;
	Event->Function = Args[3];
	Event->start = uev_event_post;
	Event->stop = uev_event_stop;
	uev_event_init(Context->Handle, Event->Handle, ml_uev_callback, Event);
	ML_RETURN(Event);
}

ML_LIBRARY_ENTRY0 {
#include "uev_init.c"
	stringmap_insert(UevT->Exports, "flags", UevFlagsT);
	stringmap_insert(UevT->Exports, "event", UevEventT);
	Slot[0] = (ml_value_t *)UevT;
}
