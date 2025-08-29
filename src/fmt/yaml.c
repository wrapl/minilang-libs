#include <minilang/ml_library.h>
#include <minilang/ml_macros.h>
#include <minilang/ml_time.h>
#include <yaml.h>
#include <math.h>
#include <ctype.h>

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

static ml_value_t *ml_decode_scalar(const char *Scalar, size_t Length) {
	if (Length == 4) {
		if (Scalar[0] == 'n' && Scalar[1] == 'u' && Scalar[2] == 'l' && Scalar[3] == 'l') {
			return MLNil;
		} else if (Scalar[0] == 'N') {
			if (Scalar[1] == 'u' && Scalar[2] == 'l' && Scalar[3] == 'l') {
				return MLNil;
			} else if (Scalar[1] == 'U' && Scalar[2] == 'L' && Scalar[3] == 'L') {
				return MLNil;
			}
		} else if (Scalar[0] == 't' && Scalar[1] == 'r' && Scalar[2] == 'u' && Scalar[3] == 'e') {
			return (ml_value_t *)MLTrue;
		} else if (Scalar[0] == 'T') {
			if (Scalar[1] == 'R' && Scalar[2] == 'U' && Scalar[3] == 'E') {
				return (ml_value_t *)MLTrue;
			} else if (Scalar[1] == 'r' && Scalar[2] == 'u' && Scalar[3] == 'e') {
				return (ml_value_t *)MLTrue;
			}
		}
		if (Scalar[0] == '.') {
			if (Scalar[1] == 'i' && Scalar[2] == 'n' && Scalar[3] == 'f') {
				return ml_real(INFINITY);
			} else if (Scalar[1] == 'I' && Scalar[2] == 'n' && Scalar[3] == 'f') {
				return ml_real(INFINITY);
			} else if (Scalar[1] == 'I' && Scalar[2] == 'N' && Scalar[3] == 'F') {
				return ml_real(INFINITY);
			}
			if (Scalar[1] == 'n' && Scalar[2] == 'a' && Scalar[3] == 'n') {
				return ml_real(NAN);
			} else if (Scalar[1] == 'N' && Scalar[2] == 'a' && Scalar[3] == 'N') {
				return ml_real(NAN);
			} else if (Scalar[1] == 'N' && Scalar[2] == 'A' && Scalar[3] == 'N') {
				return ml_real(NAN);
			}
		}
	} else if (Length == 5) {
		if (Scalar[0] == 'f' && Scalar[1] == 'a' && Scalar[2] == 'l' && Scalar[3] == 's' && Scalar[4] == 'e') {
			return (ml_value_t *)MLFalse;
		} else if (Scalar[0] == 'F') {
			if (Scalar[1] == 'A' && Scalar[2] == 'L' && Scalar[3] == 'S' && Scalar[4] == 'E') {
				return (ml_value_t *)MLFalse;
			} else if (Scalar[1] == 'a' && Scalar[2] == 'l' && Scalar[3] == 's' && Scalar[4] == 'e') {
				return (ml_value_t *)MLFalse;
			}
		}
		if (Scalar[0] == '-' && Scalar[1] == '.') {
			if (Scalar[2] == 'i' && Scalar[3] == 'n' && Scalar[4] == 'f') {
				return ml_real(-INFINITY);
			} else if (Scalar[2] == 'I' && Scalar[3] == 'n' && Scalar[4] == 'f') {
				return ml_real(-INFINITY);
			} else if (Scalar[2] == 'I' && Scalar[3] == 'N' && Scalar[4] == 'F') {
				return ml_real(-INFINITY);
			}
		}
		if (Scalar[0] == '+' && Scalar[1] == '.') {
			if (Scalar[2] == 'i' && Scalar[3] == 'n' && Scalar[4] == 'f') {
				return ml_real(INFINITY);
			} else if (Scalar[2] == 'I' && Scalar[3] == 'n' && Scalar[4] == 'f') {
				return ml_real(INFINITY);
			} else if (Scalar[2] == 'I' && Scalar[3] == 'N' && Scalar[4] == 'F') {
				return ml_real(INFINITY);
			}
		}
	}
	if (Scalar[0] == '-') {
		char *End;
		long Int = strtol(Scalar + 1, &End, 10);
		if (End == Scalar + Length) return ml_integer(-Int);
		double Real = strtod(Scalar + 1, &End);
		if (End == Scalar + Length) return ml_real(-Real);
	}
	if (Scalar[0] == '+') {
		char *End;
		long Int = strtol(Scalar + 1, &End, 10);
		if (End == Scalar + Length) return ml_integer(Int);
		double Real = strtod(Scalar + 1, &End);
		if (End == Scalar + Length) return ml_real(Real);
	}
	if (Scalar[0] == '.') {
		char *End;
		double Real = strtod(Scalar, &End);
		if (End == Scalar + Length) return ml_real(Real);
	}
	if (Scalar[0] == '0') {
		if (Scalar[1] == 'o') {
			char *End;
			long Int = strtol(Scalar + 2, &End, 8);
			if (End == Scalar + Length) return ml_integer(Int);
		} else if (Scalar[1] == 'x') {
			char *End;
			long Int = strtol(Scalar + 2, &End, 16);
			if (End == Scalar + Length) return ml_integer(Int);
		}
	}
	if (isdigit(Scalar[0])) {
		char *End;
		long Int = strtol(Scalar, &End, 10);
		if (End == Scalar + Length) return ml_integer(Int);
		double Real = strtod(Scalar, &End);
		if (End == Scalar + Length) return ml_real(Real);
		struct tm TM = {0,};
		int Local = 1;
		int Offset = 0;
		time_t Sec;
		unsigned long NSec = 0;
		if (Length > 10) {
			const char *Rest = strptime(Scalar, "%FT%T", &TM);
			if (!Rest) Rest = strptime(Scalar, "%Ft%T", &TM);
			if (!Rest) Rest = strptime(Scalar, "%F %T", &TM);
			if (!Rest) goto string;
			if (Rest[0] == '.') {
				++Rest;
				char *End;
				NSec = strtoul(Rest, &End, 10);
				for (int I = 9 - (End - Rest); --I >= 0;) NSec *= 10;
				Rest = End;
			}
			if (Rest[0] == 'Z') {
				Local = 0;
				++Rest;
			} else {
				if (Rest[0] == ' ') ++Rest;
				if (Rest[0] == '+' || Rest[0] == '-') {
					Local = 0;
					const char *Next = Rest + 1;
					if (!isdigit(Next[0])) goto string;
					if (isdigit(Next[1])) {
						Offset = 3600 * (10 * (Next[0] - '0') + (Next[1] - '0'));
						Next += 2;
					} else {
						Offset = 3600 * (Next[0] - '0');
						Next += 1;
					}
					if (Next[0] == ':') ++Next;
					if (isdigit(Next[0]) && isdigit(Next[1])) {
						Offset += 60 * (10 * (Next[0] - '0') + (Next[1] - '0'));
						Next += 2;
					}
					if (Rest[0] == '-') Offset = -Offset;
					Rest = Next;
				}
			}
			if (Rest != Scalar + Length) goto string;
		} else {
			const char *Rest = strptime(Scalar, "%F", &TM);
			if (Rest != Scalar + Length) goto string;
		}
		if (Local) {
			Sec = mktime(&TM);
		} else {
			Sec = timegm(&TM) - Offset;
		}
		return ml_time(Sec, NSec);
	}
string:
	return ml_string_copy(Scalar, Length);
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
	stringmap_t Aliases[1] = {STRINGMAP_INIT};
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
		}
		case YAML_DOCUMENT_START_EVENT: {
			ml_yaml_state_push(State, ml_list(), IsList);
			break;
		}
		case YAML_DOCUMENT_END_EVENT: {
			ml_value_t *Document = ml_yaml_state_pop(State);
			ml_list_put(State->Container, Document);
			break;
		}
		case YAML_ALIAS_EVENT: {
			printf("Alias: <%s>\n", Event->data.alias.anchor);
			ml_value_t *Value = stringmap_search(Aliases, (const char *)Event->data.alias.anchor);
			if (!Value) {
				State->Container = ml_error("YAMLError", "Undefined anchor: %s", Event->data.alias.anchor);
				goto done;
			}
			if (State->Key == IsList) {
				ml_list_put(State->Container, Value);
			} else if (State->Key) {
				ml_map_insert(State->Container, State->Key, Value);
				State->Key = NULL;
			} else {
				State->Key = Value;
			}
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
				Value = ml_string_copy((const char *)Event->data.scalar.value, Event->data.scalar.length);
			} else if (Event->data.scalar.plain_implicit) {
				Value = ml_decode_scalar((const char *)Event->data.scalar.value, Event->data.scalar.length);
			} else {
				// TODO: use tag to get correct type
				Value = ml_string_copy((const char *)Event->data.scalar.value, Event->data.scalar.length);
			}
			if (State->Key == IsList) {
				ml_list_put(State->Container, Value);
			} else if (State->Key) {
				ml_map_insert(State->Container, State->Key, Value);
				State->Key = NULL;
			} else {
				State->Key = Value;
			}
			break;
		}
		case YAML_SEQUENCE_START_EVENT: {
			printf("Sequence: <%s> <%s>\n",
				Event->data.scalar.anchor,
				Event->data.scalar.tag
			);
			ml_value_t *List = ml_list();
			if (Event->data.scalar.anchor) {
				stringmap_insert(Aliases, GC_strdup((const char *)Event->data.scalar.anchor), List);
			}
			ml_yaml_state_push(State, List, IsList);
			break;
		}
		case YAML_SEQUENCE_END_EVENT: {
			ml_value_t *Value = ml_yaml_state_pop(State);
			if (State->Key == IsList) {
				ml_list_put(State->Container, Value);
			} else if (State->Key) {
				ml_map_insert(State->Container, State->Key, Value);
				State->Key = NULL;
			} else {
				State->Key = Value;
			}
			break;
		}
		case YAML_MAPPING_START_EVENT: {
			printf("Mapping: <%s> <%s>\n",
				Event->data.scalar.anchor,
				Event->data.scalar.tag
			);
			ml_value_t *Map = ml_map();
			if (Event->data.scalar.anchor) {
				stringmap_insert(Aliases, GC_strdup((const char *)Event->data.scalar.anchor), Map);
			}
			ml_yaml_state_push(State, Map, NULL);
			break;
		}
		case YAML_MAPPING_END_EVENT: {
			ml_value_t *Value = ml_yaml_state_pop(State);
			if (State->Key == IsList) {
				ml_list_put(State->Container, Value);
			} else if (State->Key) {
				ml_map_insert(State->Container, State->Key, Value);
				State->Key = NULL;
			} else {
				State->Key = Value;
			}
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
