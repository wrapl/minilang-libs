#include <minilang/minilang.h>
#include <minilang/ml_macros.h>
#include <minilang/ml_object.h>
#include <minilang/ml_library.h>

typedef struct connections_t connections_t;
typedef struct signal_t signal_t;
typedef struct connection_t connection_t;

struct connections_t {
	ml_type_t *Type;
	stringmap_t Signals[1];
};

ML_TYPE(ConnectionsT, (), "connections");

struct signal_t {
	connections_t *Connections;
	const char *Name;
	connection_t *Head;
};

#define CONNECTION_ONCE 1

struct connection_t {
	ml_type_t *Type;
	signal_t *Signal;
	connection_t *Next;
	ml_value_t *Fn;
	int Count, Flags;
	ml_value_t *Args[];
};

ML_TYPE(ConnectionT, (), "connection");

static connection_t *connection_new(connections_t *Connections, const char *Name, ml_value_t *Fn, int Count, ml_value_t **Args) {
	connection_t *Connection = xnew(connection_t, Count, ml_value_t *);
	Connection->Type = ConnectionT;
	Connection->Fn = Fn;
	Connection->Count = Count;
	for (int I = 0; I < Count; ++I) Connection->Args[I] = Args[I];
	signal_t **Slot = (signal_t **)stringmap_slot(Connections->Signals, Name);
	signal_t *Signal = Slot[0];
	if (!Signal) {
		Signal = Slot[0] = new(signal_t);
		Signal->Connections = Connections;
		Signal->Name = Name;
	}
	Connection->Signal = Signal;
	Connection->Next = Signal->Head;
	Signal->Head = Connection;
	return Connection;
}

static void connection_free(connection_t *Connection) {
	signal_t *Signal = Connection->Signal;
	connection_t **Slot = &Signal->Head;
	while (Slot[0] != Connection) Slot = &Slot[0]->Next;
	Slot[0] = Connection->Next;
	if (!Signal->Head) stringmap_remove(Signal->Connections->Signals, Signal->Name);
}

typedef struct {
	ml_state_t Base;
	connection_t **Slot;
	int Count, Flags;
	ml_value_t *Args[];
} event_t;

static void event_run(event_t *Event, ml_value_t *Value) {
	if (ml_is_error(Value)) ML_CONTINUE(Event->Base.Caller, Value);
	connection_t *Connection = Event->Slot[0];
	if (Connection->Flags & CONNECTION_ONCE) {
		Event->Slot[0] = Connection->Next;
	} else {
		Event->Slot = &Connection->Next;
	}
	if (Connection->Next) {
		Connection = Connection->Next;
		ml_value_t **Args = ml_alloc_args(Event->Count + Connection->Count);
		ml_value_t **Arg = Args;
		for (int I = 0; I < Event->Count; ++I) *Arg++ = Event->Args[I];
		for (int I = 0; I < Connection->Count; ++I) *Arg++ = Connection->Args[I];
		return ml_call(Event, Connection->Fn, Event->Count + Connection->Count, Args);
	} else {
		signal_t *Signal = Connection->Signal;
		if (!Signal->Head) stringmap_remove(Signal->Connections->Signals, Signal->Name);
		ML_CONTINUE(Event->Base.Caller, Value);
	}
}

static void event_emit(ml_state_t *Caller, connections_t *Connections, const char *Name, int Count, ml_value_t **Args) {
	signal_t *Signal = stringmap_search(Connections->Signals, Name);
	if (!Signal) ML_RETURN(MLNil);
	event_t *Event = xnew(event_t, Count, ml_value_t *);
	Event->Base.Caller = Caller;
	Event->Base.Context = Caller->Context;
	Event->Base.run = (ml_state_fn)event_run;
	Event->Slot = &Signal->Head;
	Event->Count = Count;
	for (int I = 0; I < Count; ++I) Event->Args[I] = Args[I];
	connection_t *Connection = Signal->Head;
	ml_value_t **Args2 = ml_alloc_args(Count + Connection->Count);
	ml_value_t **Arg = Args2;
	for (int I = 0; I < Count; ++I) *Arg++ = Args[I];
	for (int I = 0; I < Connection->Count; ++I) *Arg++ = Connection->Args[I];
	return ml_call(Event, Connection->Fn, Count + Connection->Count, Args2);
}

ML_METHOD_ANON(SourceEvents, "source::events");

ML_FUNCTION(Connect) {
	ML_CHECK_ARG_COUNT(3);
	ML_CHECK_ARG_TYPE(0, MLStringT);
	ML_CHECK_ARG_TYPE(1, MLObjectT);
	ml_object_t *Object = (ml_object_t *)Args[1];
	int Index;
	for (ml_field_info_t *Info = Object->Type->Fields; Info; Info = Info->Next) {
		if (Info->Method == SourceEvents) {
			Index = Info->Index;
			goto found;
		}
	}
	return ml_error("TypeError", "Object does not support events");
found:;
	connections_t *Connections = (connections_t *)Object->Fields[Index].Value;
	if (ml_typeof((ml_value_t *)Connections) != ConnectionsT) {
		Connections = new(connections_t);
		Connections->Type = ConnectionsT;
		Object->Fields[Index].Value = (ml_value_t *)Connections;
	}
	connection_t *Connection = connection_new(Connections, ml_string_value(Args[0]), Args[Count - 1], Count - 3, Args + 2);
	return (ml_value_t *)Connection;
}

ML_FUNCTIONX(Emit) {
	ML_CHECKX_ARG_COUNT(3);
	ML_CHECKX_ARG_TYPE(0, MLStringT);
	ML_CHECKX_ARG_TYPE(1, MLObjectT);
	ml_object_t *Object = (ml_object_t *)Args[1];
	int Index;
	for (ml_field_info_t *Info = Object->Type->Fields; Info; Info = Info->Next) {
		if (Info->Method == SourceEvents) {
			Index = Info->Index;
			goto found;
		}
	}
	ML_ERROR("TypeError", "Object does not support events");
found:;
	connections_t *Connections = (connections_t *)Object->Fields[Index].Value;
	if (ml_typeof((ml_value_t *)Connections) != ConnectionsT) {
		ML_RETURN(MLNil);
	}
	return event_emit(Caller, Connections, ml_string_value(Args[0]), Count - 1, Args + 1);
}

typedef struct {

} source_field_t;

static ml_value_t *source_field_deref(ml_field_t *Field) {
	return Field->Value;
}

static void source_field_assign(ml_state_t *Caller, ml_field_t *Field, ml_value_t *Value) {
}

static void source_field_call(ml_state_t *Caller, ml_field_t *Field, int Count, ml_value_t **Args) {

}

ML_TYPE(SourceFieldT, (), "source::field",
	.deref = (void *)source_field_deref,
	.assign = (void *)source_field_assign,
	.call = (void *)source_field_call
);

ML_LIBRARY_ENTRY {
#include "event_init.c"
	ml_type_t *SourceT = ml_class("event::source");
	ml_class_add_field(Caller->Context, SourceT, SourceEvents);
	Slot[0] = ml_module("event/event",
		"source", SourceT,
		"connect", Connect,
		"emit", Emit,
	NULL);
}
