#include <minilang/ml_library.h>
#include <minilang/ml_macros.h>
#include <yaml.h>

#undef ML_CATEGORY
#define ML_CATEGORY "fmt/yaml"

ML_METHOD_ANON(Decode, "yaml::decode");

typedef struct ml_yaml_stack_t ml_yaml_stack_t;

typedef struct {
	ml_value_t *Container, *Key;
} ml_yaml_stack_node_t;

struct ml_yaml_stack_t {
	ml_yaml_stack_t *Prev, *Next;
	ml_yaml_stack_node_t Nodes[32];
};

typedef struct {
	ml_yaml_stack_t *Stack;
	ml_value_t *Container, *Key;
	int Top;
} ml_yaml_state_t;

ML_VALUE(IsList, MLAnyT);

static void ml_yaml_state_push(ml_yaml_state_t *State, ml_value_t *Container, ml_value_t *Key) {
	ml_yaml_stack_t *Stack = State->Stack;
	if (!State->Top) {
		if (!Stack) {
			Stack = new(ml_yaml_stack_t);
		} else if (Stack->Next) {
			Stack = Stack->Next;
		} else {
			ml_yaml_stack_t *Next = new(ml_yaml_stack_t);
			Next->Prev = Stack;
			Stack->Next = Next;
			Stack = Next;
		}
		State->Stack = Stack;
		State->Top = 32;
	}
	Stack->Nodes[--State->Top] = (ml_yaml_stack_node_t){State->Container, State->Key};
	State->Container = Container;
	State->Key = Key;
}

static ml_value_t *ml_yaml_state_pop(ml_yaml_state_t *State) {
	ml_yaml_stack_t *Stack = State->Stack;
	int Top = State->Top;
	if (Top == 32) {
		State->Stack = Stack = Stack->Prev;
		Top = 0;
	}
	ml_value_t *Result = State->Container;
	State->Container = Stack->Nodes[Top].Container;
	State->Key = Stack->Nodes[Top].Key;
	State->Top = Top + 1;
	return Result;
}

ML_METHOD(Decode, MLStringT) {
	yaml_parser_t Parser[1];
	yaml_parser_initialize(Parser);
	yaml_parser_set_input_string(Parser,
		(unsigned char *)ml_string_value(Args[0]),
		ml_string_length(Args[0])
	);
	yaml_event_t Event[1];
	ml_yaml_state_t State[1] = {{0,}};
	State->Container = ml_list();
	State->Key = IsList;
	for (;;) {
		if (!yaml_parser_parse(Parser, Event)) {
			State->Container = ml_error("YAMLError", "%s at %ld (%s)", Parser->problem, Parser->problem_offset, Parser->context);
			goto done;
		}
		if (Event->type) printf("Event = %d\n", Event->type);
		switch (Event->type) {
		case YAML_NO_EVENT: break;
		case YAML_STREAM_START_EVENT: {
			break;
		}
		case YAML_STREAM_END_EVENT: {
			yaml_event_delete(Event);
			goto done;
			break;
		}
		case YAML_DOCUMENT_START_EVENT: {
			ml_yaml_state_push(State, ml_map(), NULL);
			break;
		}
		case YAML_DOCUMENT_END_EVENT: {
			ml_value_t *Document = ml_yaml_state_pop(State);
			ml_list_put(State->Container, Document);
			break;
		}
		case YAML_ALIAS_EVENT: {
			printf("Alias: <%s>\n", Event->data.alias.anchor);
			break;
		}
		case YAML_SCALAR_EVENT: {
			printf("Scalar: <%s> <%s> <%.*s> <%d/%d>\n",
				Event->data.scalar.anchor,
				Event->data.scalar.tag,
				(int)Event->data.scalar.length,
				Event->data.scalar.value,
				Event->data.scalar.plain_implicit,
				Event->data.scalar.quoted_implicit
			);
			ml_value_t *Value;
			if (Event->data.scalar.quoted_implicit) {
				Value = ml_string_copy(Event->data.scalar.value, Event->data.scalar.length);
			} else if (Event->data.scalar.plain_implicit) {

			} else {
				// TODO: use tag to get correct type
				Value = MLNil;
			}
			break;
		}
		case YAML_SEQUENCE_START_EVENT: {
			printf("Sequence: <%s> <%s>\n",
				Event->data.scalar.anchor,
				Event->data.scalar.tag
			);
			ml_yaml_state_push(State, ml_list(), IsList);
			break;
		}
		case YAML_SEQUENCE_END_EVENT: {
			ml_value_t *Value = ml_yaml_state_pop(State);

			break;
		}
		case YAML_MAPPING_START_EVENT: {
			printf("Mapping: <%s> <%s>\n",
				Event->data.scalar.anchor,
				Event->data.scalar.tag
			);
			ml_yaml_state_push(State, ml_map(), NULL);
			break;
		}
		case YAML_MAPPING_END_EVENT: {
			ml_value_t *Value = ml_yaml_state_pop(State);

			break;
		}
		}
		yaml_event_delete(Event);
	}
done:
	yaml_parser_delete(Parser);
	return State->Container;
}

ML_LIBRARY_ENTRY0(fmt_yaml) {
#include "yaml_init.c"
	Slot[0] = ml_callable_module("yaml", (ml_value_t *)Decode,
		"decode", Decode,
	NULL);
}
