#include <minilang/minilang.h>
#include <minilang/ml_macros.h>
#include <minilang/ml_object.h>
#include <minilang/ml_library.h>

typedef struct events_t events_t;
typedef struct signal_t signal_t;
typedef struct connection_t connection_t;

struct events_t {
	ml_type_t *Type, *Class;
	stringmap_t Signals[1];
};

ML_TYPE(EventsT, (), "source::events");

#define CONNECTION_ONCE 1

struct connection_t {
	ml_type_t *Type;
	connection_t *Next;
	ml_value_t *Fn;
	int Count, Flags;
	ml_value_t *Args[];
};

ML_TYPE(ConnectionT, (), "source::connection");

static connection_t *connection_new(events_t *Events, const char *Name, ml_value_t *Fn, int Count, ml_value_t **Args) {
	connection_t *Connection = xnew(connection_t, Count, ml_value_t *);
	Connection->Type = ConnectionT;
	Connection->Fn = Fn;
	Connection->Count = Count;
	for (int I = 0; I < Count; ++I) Connection->Args[I] = Args[I];
	Connection->Next = (connection_t *)stringmap_insert(Events->Signals, Name, Connection);
	return Connection;
}

static void connection_free(events_t *Events, const char *Name, connection_t *Connection) {
	connection_t **Slot = (connection_t **)stringmap_slot(Events->Signals, Name);
	if (Slot[0] == Connection) {
		if (!Connection->Next) stringmap_remove(Events->Signals, Name);
	} else do {
		Slot = &Slot[0]->Next;
		if (!Slot[0]) return;
	} while (Slot[0] != Connection);
	Slot[0] = Connection->Next;
}

typedef struct {
	ml_state_t Base;
	events_t *Events;
	const char *Name;
	connection_t *Connection;
	int Count, Flags;
	ml_value_t *Args[];
} event_t;

static void event_run_class(event_t *Event, ml_value_t *Value) {
	if (ml_is_error(Value)) ML_CONTINUE(Event->Base.Caller, Value);
	connection_t *Connection = Event->Connection;
	connection_t *Next = Connection->Next;
	if (Connection->Flags & CONNECTION_ONCE) connection_free(Event->Events, Event->Name, Connection);
	if (!Next) ML_CONTINUE(Event->Base.Caller, Value);
	Event->Connection = Next;
	ml_value_t **Args = ml_alloc_args(Event->Count + Next->Count);
	ml_value_t **Arg = Args;
	for (int I = 0; I < Event->Count; ++I) *Arg++ = Event->Args[I];
	for (int I = 0; I < Next->Count; ++I) *Arg++ = Next->Args[I];
	return ml_call(Event, Next->Fn, Event->Count + Next->Count, Args);
}

static void event_run_object(event_t *Event, ml_value_t *Value) {
	if (ml_is_error(Value)) ML_CONTINUE(Event->Base.Caller, Value);
	connection_t *Connection = Event->Connection;
	connection_t *Next = Connection->Next;
	if (Connection->Flags & CONNECTION_ONCE) connection_free(Event->Events, Event->Name, Connection);
	if (!Next) {
		events_t *Events = (events_t *)ml_typed_fn_get(ml_typeof(Event->Args[0]), EventsT);
		if (!Events) ML_CONTINUE(Event->Base.Caller, Value);
		Next = (connection_t *)stringmap_search(Events->Signals, Event->Name);
		if (!Next) ML_CONTINUE(Event->Base.Caller, Value);
		Event->Base.run = (ml_state_fn)event_run_class;
		Event->Events = Events;
	}
	Event->Connection = Next;
	ml_value_t **Args = ml_alloc_args(Event->Count + Next->Count);
	ml_value_t **Arg = Args;
	for (int I = 0; I < Event->Count; ++I) *Arg++ = Event->Args[I];
	for (int I = 0; I < Next->Count; ++I) *Arg++ = Next->Args[I];
	return ml_call(Event, Next->Fn, Event->Count + Next->Count, Args);
}

static void event_emit(ml_state_t *Caller, events_t *Events, const char *Name, int Count, ml_value_t **Args) {
	connection_t *First = (connection_t *)stringmap_search(Events->Signals, Name);
	ml_state_fn run = (ml_state_fn)event_run_object;
	if (!First) {
		Events = (events_t *)ml_typed_fn_get(ml_typeof(Args[0]), EventsT);
		if (!Events) ML_RETURN(MLNil);
		First = (connection_t *)stringmap_search(Events->Signals, Name);
		if (!First) ML_RETURN(MLNil);
		run = (ml_state_fn)event_run_class;
	}
	event_t *Event = xnew(event_t, Count, ml_value_t *);
	Event->Base.Caller = Caller;
	Event->Base.Context = Caller->Context;
	Event->Base.run = run;
	Event->Events = Events;
	Event->Name = Name;
	Event->Connection = First;
	Event->Count = Count;
	for (int I = 0; I < Count; ++I) Event->Args[I] = Args[I];
	ml_value_t **Args2 = ml_alloc_args(Count + First->Count);
	ml_value_t **Arg = Args2;
	for (int I = 0; I < Count; ++I) *Arg++ = Args[I];
	for (int I = 0; I < First->Count; ++I) *Arg++ = First->Args[I];
	return ml_call(Event, First->Fn, Count + First->Count, Args2);
}

ML_METHOD_ANON(SourceEvents, "source::events");

ML_METHOD_ANON(Connect, "event::connect");

ML_METHODV(Connect, MLStringT, MLObjectT, MLAnyT) {
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
	events_t *Events = (events_t *)Object->Fields[Index].Value;
	if (ml_typeof((ml_value_t *)Events) != EventsT) {
		Events = new(events_t);
		Events->Type = EventsT;
		Object->Fields[Index].Value = (ml_value_t *)Events;
	}
	connection_t *Connection = connection_new(Events, ml_string_value(Args[0]), Args[Count - 1], Count - 3, Args + 2);
	return (ml_value_t *)Connection;
}

ML_METHODV(Connect, MLStringT, MLClassT, MLAnyT) {
	ml_type_t *Class = (ml_type_t *)Args[1];
	events_t *Events = (events_t *)ml_typed_fn_get(Class, EventsT);
	if (!Events) return ml_error("TypeError", "Class does not support events");
	if (Events->Class != Class) {
		Events = new(events_t);
		Events->Type = EventsT;
		Events->Class = Class;
		ml_typed_fn_set(Class, EventsT, Events);
	}
	connection_t *Connection = connection_new(Events, ml_string_value(Args[0]), Args[Count - 1], Count - 3, Args + 2);
	return (ml_value_t *)Connection;
}

ML_METHOD_ANON(Emit, "event::emit");

ML_METHODVX(Emit, MLStringT, MLObjectT) {
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
	events_t *Events = (events_t *)Object->Fields[Index].Value;
	if (ml_typeof((ml_value_t *)Events) != EventsT) {
		Events = new(events_t);
		Events->Type = EventsT;
		Object->Fields[Index].Value = (ml_value_t *)Events;
	}
	return event_emit(Caller, Events, ml_string_value(Args[0]), Count - 1, Args + 1);
}

ML_METHODVX(Emit, MLMethodT, MLObjectT) {
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
	events_t *Events = (events_t *)Object->Fields[Index].Value;
	if (ml_typeof((ml_value_t *)Events) != EventsT) {
		Events = new(events_t);
		Events->Type = EventsT;
		Object->Fields[Index].Value = (ml_value_t *)Events;
	}
	return event_emit(Caller, Events, ml_method_name(Args[0]), Count - 1, Args + 1);
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

ML_LIBRARY_ENTRY(event) {
#include "event_init.c"
	ml_type_t *SourceT = ml_class("event::source");
	ml_class_add_field(Caller->Context, SourceT, SourceEvents, MLFieldT);
	events_t *Events = new(events_t);
	Events->Type = EventsT;
	Events->Class = SourceT;
	ml_typed_fn_set(SourceT, EventsT, Events);
	Slot[0] = ml_module("event",
		"source", SourceT,
		"connect", Connect,
		"emit", Emit,
	NULL);
}
