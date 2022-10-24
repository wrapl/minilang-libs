#include <minilang/ml_library.h>
#include <minilang/ml_macros.h>
#include <minilang/ml_file.h>
#include <gc/gc.h>
#include "mpc/mpc.h"

#undef ML_CATEGORY
#define ML_CATEGORY "parse/mpc"

typedef struct ml_mpc_parser_t {
	const ml_type_t *Type;
	mpc_parser_t *Handle;
} ml_mpc_parser_t;

ML_TYPE(MLParserT, (), "parser");
// Base type of parsers.

ML_TYPE(MLParserStringT, (MLParserT), "string-parser");
// A parser that returns a string.

ML_TYPE(MLParserValueT, (MLParserT), "value-parser");
// A parser that returns an arbitrary value.

static ml_value_t Skip[1] = {{MLAnyT}};

static mpc_val_t *ml_mpc_apply_value(mpc_val_t *Value) {
	return ml_string(Value, -1);
}

static ml_value_t *ml_mpc_value_parser(ml_mpc_parser_t *StringParser) {
	ml_mpc_parser_t *ValueParser = new(ml_mpc_parser_t);
	ValueParser->Type = MLParserValueT;
	ValueParser->Handle = mpc_apply(StringParser->Handle, ml_mpc_apply_value);
	return (ml_value_t *)ValueParser;
}

static ml_value_t *ml_mpc_string_parser(mpc_parser_t *Handle) {
	mpc_optimise(Handle);
	ml_mpc_parser_t *Parser = new(ml_mpc_parser_t);
	Parser->Type = MLParserStringT;
	Parser->Handle = Handle;
	return (ml_value_t *)Parser;
}

static mpc_val_t *ml_mpc_to_string(ml_value_t *Value) {
	if (ml_is(Value, MLStringT)) return (void *)ml_string_value(Value);
	return "";
}

static mpc_parser_t *ml_mpc_to_string_parser(mpc_parser_t *ValueParser) {
	return mpc_apply(ValueParser, (void *)ml_mpc_to_string);
}

ML_METHOD("$", MLParserStringT) {
//<Parser
//>parser::value
// Returns a new parser that wraps any string returned by :mini:`Parser` into a general value.
	return ml_mpc_value_parser((ml_mpc_parser_t *)Args[0]);
}

static mpc_val_t *ml_mpc_value_to(mpc_val_t *_, void *Value) {
	return Value;
}

ML_METHOD("$", MLParserStringT, MLAnyT) {
//<Parser
//<Fn
//>parser::value
// Returns a new parser that returns :mini:`Fn(String)` for each string returned by :mini:`Parser`.
	ml_mpc_parser_t *Parser = new(ml_mpc_parser_t);
	Parser->Type = MLParserValueT;
	Parser->Handle = mpc_apply_to(((ml_mpc_parser_t *)Args[0])->Handle, ml_mpc_value_to, Args[1]);
	return (ml_value_t *)Parser;
}

ML_METHOD("^", MLParserStringT) {
	ml_mpc_parser_t *Parser = new(ml_mpc_parser_t);
	Parser->Type = MLParserValueT;
	Parser->Handle = mpc_apply_to(((ml_mpc_parser_t *)Args[0])->Handle, ml_mpc_value_to, Skip);
	return (ml_value_t *)Parser;
}

static ml_value_t *ml_mpc_pass(void *Data, int Count, ml_value_t **Args) {
	ml_mpc_parser_t *Parser = new(ml_mpc_parser_t);
	Parser->Type = MLParserT;
	Parser->Handle = mpc_pass();
	return (ml_value_t *)Parser;
}

static ml_value_t *ml_mpc_fail(void *Data, int Count, ml_value_t **Args) {
	ML_CHECK_ARG_COUNT(1);
	ML_CHECK_ARG_TYPE(0, MLStringT);
	const char *Message = ml_string_value(Args[0]);
	ml_mpc_parser_t *Parser = new(ml_mpc_parser_t);
	Parser->Type = MLParserT;
	Parser->Handle = mpc_fail(Message);
	return (ml_value_t *)Parser;
}

static ml_value_t *ml_mpc_lift_val(void *Data, int Count, ml_value_t **Args) {
	ML_CHECK_ARG_COUNT(1);
	ml_mpc_parser_t *Parser = new(ml_mpc_parser_t);
	Parser->Type = MLParserValueT;
	Parser->Handle = mpc_lift_val(Args[0]);
	return (ml_value_t *)Parser;
}

ML_METHOD("expect", MLParserT, MLStringT) {
	ml_mpc_parser_t *Parser = new(ml_mpc_parser_t);
	Parser->Type = ((ml_mpc_parser_t *)Args[0])->Type;
	Parser->Handle = mpc_expect(((ml_mpc_parser_t *)Args[0])->Handle, ml_string_value(Args[1]));
	return (ml_value_t *)Parser;
}

static mpc_val_t *ml_mpc_apply_to(mpc_val_t *Value, void *Function) {
	ml_value_t *Args[1] = {(ml_value_t *)Value};
	return ml_simple_call((ml_value_t *)Function, 1, Args);
}

ML_METHOD("->", MLParserValueT, MLFunctionT) {
	ml_mpc_parser_t *Parser = new(ml_mpc_parser_t);
	Parser->Type = MLParserValueT;
	Parser->Handle = mpc_apply_to(((ml_mpc_parser_t *)Args[0])->Handle, ml_mpc_apply_to, Args[1]);
	return (ml_value_t *)Parser;
}

static mpc_val_t *ml_mpc_apply_to_string(mpc_val_t *Value, void *Function) {
	ml_value_t *Args[1] = {ml_string(Value, -1)};
	return ml_simple_call((ml_value_t *)Function, 1, Args);
}

ML_METHOD("->", MLParserStringT, MLFunctionT) {
	ml_mpc_parser_t *Parser = new(ml_mpc_parser_t);
	Parser->Type = MLParserValueT;
	Parser->Handle = mpc_apply_to(((ml_mpc_parser_t *)Args[0])->Handle, ml_mpc_apply_to_string, Args[1]);
	return (ml_value_t *)Parser;
}

static int ml_mpc_check_with(mpc_val_t **Slot, void *Function) {
	ml_value_t *Result = ml_simple_call((ml_value_t *)Function, 1, (ml_value_t **)Slot);
	if (Result == MLNil) return 0;
	return 1;
}

ML_METHOD("?", MLParserValueT, MLFunctionT) {
	ml_mpc_parser_t *Parser = new(ml_mpc_parser_t);
	Parser->Type = MLParserValueT;
	Parser->Handle = mpc_check_with(((ml_mpc_parser_t *)Args[0])->Handle, mpcf_dtor_null, ml_mpc_check_with, Args[1], "failed");
	return (ml_value_t *)Parser;
}

static int ml_mpc_check_with_string(mpc_val_t **Slot, void *Function) {
	Slot[0] = ml_string(Slot[0], -1);
	ml_value_t *Result = ml_simple_call((ml_value_t *)Function, 1, (ml_value_t **)Slot);
	if (Result == MLNil) return 0;
	return 1;
}

ML_METHOD("?", MLParserStringT, MLFunctionT) {
	ml_mpc_parser_t *Parser = new(ml_mpc_parser_t);
	Parser->Type = MLParserStringT;
	Parser->Handle = mpc_check_with(((ml_mpc_parser_t *)Args[0])->Handle, mpcf_dtor_null, ml_mpc_check_with_string, Args[1], "failed");
	return (ml_value_t *)Parser;
}

static int ml_mpc_filter_with(mpc_val_t **Slot, void *Function) {
	ml_value_t *Result = ml_simple_call((ml_value_t *)Function, 1, (ml_value_t **)Slot);
	if (Result == MLNil) return 0;
	Slot[0] = Result;
	return 1;
}

ML_METHOD("->?", MLParserValueT, MLFunctionT) {
	ml_mpc_parser_t *Parser = new(ml_mpc_parser_t);
	Parser->Type = MLParserValueT;
	Parser->Handle = mpc_check_with(((ml_mpc_parser_t *)Args[0])->Handle, mpcf_dtor_null, ml_mpc_filter_with, Args[1], "failed");
	return (ml_value_t *)Parser;
}

static int ml_mpc_filter_with_string(mpc_val_t **Slot, void *Function) {
	Slot[0] = ml_string(Slot[0], -1);
	ml_value_t *Result = ml_simple_call((ml_value_t *)Function, 1, (ml_value_t **)Slot);
	if (Result == MLNil) return 0;
	Slot[0] = Result;
	return 1;
}

ML_METHOD("->?", MLParserStringT, MLFunctionT) {
	ml_mpc_parser_t *Parser = new(ml_mpc_parser_t);
	Parser->Type = MLParserValueT;
	Parser->Handle = mpc_check_with(((ml_mpc_parser_t *)Args[0])->Handle, mpcf_dtor_null, ml_mpc_filter_with_string, Args[1], "failed");
	return (ml_value_t *)Parser;
}

static mpc_val_t *ml_mpc_ctor_nil(void) {
	return MLNil;
}

ML_METHOD("!", MLParserValueT) {
	ml_mpc_parser_t *Parser = new(ml_mpc_parser_t);
	Parser->Type = MLParserValueT;
	Parser->Handle = mpc_not_lift(((ml_mpc_parser_t *)Args[0])->Handle, mpcf_dtor_null, ml_mpc_ctor_nil);
	return (ml_value_t *)Parser;
}

ML_METHOD("!", MLParserStringT) {
	ml_mpc_parser_t *Parser = new(ml_mpc_parser_t);
	Parser->Type = MLParserValueT;
	Parser->Handle = mpc_not_lift(((ml_mpc_parser_t *)Args[0])->Handle, mpcf_dtor_null, mpcf_ctor_str);
	return (ml_value_t *)Parser;
}

ML_METHOD("~", MLParserValueT) {
	ml_mpc_parser_t *Parser = new(ml_mpc_parser_t);
	Parser->Type = MLParserValueT;
	Parser->Handle = mpc_maybe_lift(((ml_mpc_parser_t *)Args[0])->Handle, ml_mpc_ctor_nil);
	return (ml_value_t *)Parser;
}

ML_METHOD("~", MLParserStringT) {
	ml_mpc_parser_t *Parser = new(ml_mpc_parser_t);
	Parser->Type = MLParserStringT;
	Parser->Handle = mpc_maybe(((ml_mpc_parser_t *)Args[0])->Handle);
	return (ml_value_t *)Parser;
}

static mpc_val_t *ml_mpc_fold_list(int Count, mpc_val_t **Values) {
	ml_value_t *List = ml_list();
	for (int I = 0; I < Count; ++I) {
		ml_value_t *Value = (ml_value_t *)Values[I];
		if (Value != Skip) ml_list_append(List, Value);
	}
	return List;
}

ML_METHOD("*", MLParserValueT) {
	ml_mpc_parser_t *Parser = new(ml_mpc_parser_t);
	Parser->Type = MLParserValueT;
	Parser->Handle = mpc_many(ml_mpc_fold_list, ((ml_mpc_parser_t *)Args[0])->Handle);
	return (ml_value_t *)Parser;
}

ML_METHOD("*", MLParserStringT) {
	ml_mpc_parser_t *Parser = new(ml_mpc_parser_t);
	Parser->Type = MLParserStringT;
	Parser->Handle = mpc_many(mpcf_strfold, ((ml_mpc_parser_t *)Args[0])->Handle);
	return (ml_value_t *)Parser;
}

ML_METHOD("+", MLParserValueT) {
	ml_mpc_parser_t *Parser = new(ml_mpc_parser_t);
	Parser->Type = MLParserValueT;
	Parser->Handle = mpc_many1(ml_mpc_fold_list, ((ml_mpc_parser_t *)Args[0])->Handle);
	return (ml_value_t *)Parser;
}

ML_METHOD("+", MLParserStringT) {
	ml_mpc_parser_t *Parser = new(ml_mpc_parser_t);
	Parser->Type = MLParserStringT;
	Parser->Handle = mpc_many1(mpcf_strfold, ((ml_mpc_parser_t *)Args[0])->Handle);
	return (ml_value_t *)Parser;
}

ML_METHOD("*", MLIntegerT, MLParserValueT) {
	ml_mpc_parser_t *Parser = new(ml_mpc_parser_t);
	Parser->Type = MLParserValueT;
	Parser->Handle = mpc_count(ml_integer_value(Args[0]), ml_mpc_fold_list, ((ml_mpc_parser_t *)Args[1])->Handle, mpcf_dtor_null);
	return (ml_value_t *)Parser;
}

ML_METHOD("*", MLIntegerT, MLParserStringT) {
	ml_mpc_parser_t *Parser = new(ml_mpc_parser_t);
	Parser->Type = MLParserStringT;
	Parser->Handle = mpc_count(ml_integer_value(Args[0]), mpcf_strfold, ((ml_mpc_parser_t *)Args[1])->Handle, mpcf_dtor_null);
	return (ml_value_t *)Parser;
}

ML_METHOD("|", MLParserStringT, MLParserStringT) {
	ml_mpc_parser_t *Parser = new(ml_mpc_parser_t);
	Parser->Type = MLParserStringT;
	Parser->Handle = mpc_or(2, ((ml_mpc_parser_t *)Args[0])->Handle, ((ml_mpc_parser_t *)Args[1])->Handle);
	return (ml_value_t *)Parser;
}

ML_METHOD("|", MLParserValueT, MLParserValueT) {
	ml_mpc_parser_t *Parser = new(ml_mpc_parser_t);
	Parser->Type = MLParserValueT;
	Parser->Handle = mpc_or(2, ((ml_mpc_parser_t *)Args[0])->Handle, ((ml_mpc_parser_t *)Args[1])->Handle);
	return (ml_value_t *)Parser;
}

extern mpc_parser_t *mpc_andv(int n, mpc_fold_t f, mpc_parser_t **parsers);

ML_FUNCTION(MLParserSeq) {
//@seq
//<Parser/i...:parser|string|regex
//>parser::value
// Returns a new parser that matches the sequence of parsers defined by :mini:`Parser/i`. The parser returns a list of the parsed values.
	mpc_parser_t *Parsers[Count];
	for (int I = 0; I < Count; ++I) {
		if (ml_is(Args[I], MLParserValueT)) {
			ml_mpc_parser_t *Arg = (ml_mpc_parser_t *)Args[I];
			Parsers[I] = Arg->Handle;
		} else if (ml_is(Args[I], MLParserStringT)) {
			ml_mpc_parser_t *Arg = (ml_mpc_parser_t *)Args[I];
			Parsers[I] = mpc_apply(Arg->Handle, ml_mpc_apply_value);
		} else if (ml_is(Args[I], MLStringT)) {
			Parsers[I] = mpc_apply(mpc_string(ml_string_value(Args[I])), ml_mpc_apply_value);
		} else if (ml_is(Args[I], MLRegexT)) {
			Parsers[I] = mpc_apply(mpc_re(ml_regex_pattern(Args[I])), ml_mpc_apply_value);
		} else {
			ML_CHECK_ARG_TYPE(I, MLParserT);
		}
	}
	ml_mpc_parser_t *Parser = new(ml_mpc_parser_t);
	Parser->Type = MLParserValueT;
	Parser->Handle = mpc_andv(Count, ml_mpc_fold_list, Parsers);
	return (ml_value_t *)Parser;
}

typedef struct {
	ml_mpc_parser_t Base;
	ml_value_t *Name;
} ml_mpc_field_t;

ML_TYPE(MLParserNamedT, (MLParserValueT), "mpc::field");

ML_METHOD("as", MLParserValueT, MLStringT) {
//<Parser
//<Name
//>parser::named
// Returns a new named parser, for use in :mini:`mpc::map`.
	ml_mpc_field_t *Field = new(ml_mpc_field_t);
	Field->Base.Type = MLParserNamedT;
	Field->Base.Handle = ((ml_mpc_parser_t *)Args[0])->Handle;
	Field->Name = Args[1];
	return (ml_value_t *)Field;
}

ML_METHOD("as", MLParserStringT, MLStringT) {
//<Parser
//<Name
//>parser::named
// Returns a new named parser, for use in :mini:`mpc::map`.
	ml_mpc_field_t *Field = new(ml_mpc_field_t);
	Field->Base.Type = MLParserNamedT;
	Field->Base.Handle = mpc_apply(((ml_mpc_parser_t *)Args[0])->Handle, ml_mpc_apply_value);
	Field->Name = Args[1];
	return (ml_value_t *)Field;
}

static mpc_val_t *ml_mpc_fold_map(int Count, mpc_val_t **Values) {
	ml_value_t *Map = ml_map();
	ml_value_t **Names = Values[Count];
	--Count;
	for (int I = 0; I < Count; ++I) {
		if (Names[I]) ml_map_insert(Map, Names[I], (ml_value_t *)Values[I]);
	}
	return Map;
}

ML_FUNCTION(MLParserMap) {
//@map
//<Parser/i...:parser|string|regex
//>parser::value
// Returns a new parser that matches the sequence of parsers defined by :mini:`Parser/i`. The parser returns a map of the parsed values corresponding to any named parsers. Unnamed parsers are still matched but the values are discarded.
	ml_value_t **Names = anew(ml_value_t *, Count);
	mpc_parser_t *Parsers[Count + 1];
	for (int I = 0; I < Count; ++I) {
		if (ml_is(Args[I], MLParserNamedT)) {
			ml_mpc_field_t *Arg = (ml_mpc_field_t *)Args[I];
			Names[I] = Arg->Name;
			Parsers[I] = Arg->Base.Handle;
		} else if (ml_is(Args[I], MLParserValueT)) {
			ml_mpc_parser_t *Arg = (ml_mpc_parser_t *)Args[I];
			Parsers[I] = Arg->Handle;
		} else if (ml_is(Args[I], MLParserStringT)) {
			ml_mpc_parser_t *Arg = (ml_mpc_parser_t *)Args[I];
			Parsers[I] = mpc_apply(Arg->Handle, ml_mpc_apply_value);
		} else if (ml_is(Args[I], MLStringT)) {
			Parsers[I] = mpc_apply(mpc_string(ml_string_value(Args[I])), ml_mpc_apply_value);
		} else if (ml_is(Args[I], MLRegexT)) {
			Parsers[I] = mpc_apply(mpc_re(ml_regex_pattern(Args[I])), ml_mpc_apply_value);
		} else {
			ML_CHECK_ARG_TYPE(I, MLParserT);
		}
	}
	Parsers[Count] = mpc_lift_val(Names);
	ml_mpc_parser_t *Parser = new(ml_mpc_parser_t);
	Parser->Type = MLParserValueT;
	Parser->Handle = mpc_andv(Count + 1, ml_mpc_fold_map, Parsers);
	return (ml_value_t *)Parser;
}

ML_METHOD(".", MLParserStringT, MLParserStringT) {
	ml_mpc_parser_t *Parser = new(ml_mpc_parser_t);
	Parser->Type = MLParserStringT;
	Parser->Handle = mpc_and(2, mpcf_strfold, ((ml_mpc_parser_t *)Args[0])->Handle, ((ml_mpc_parser_t *)Args[1])->Handle, mpcf_dtor_null);
	return (ml_value_t *)Parser;
}

ML_METHOD(".", MLParserStringT, MLStringT) {
	ml_mpc_parser_t *Parser = new(ml_mpc_parser_t);
	Parser->Type = MLParserStringT;
	Parser->Handle = mpc_and(2, mpcf_strfold, ((ml_mpc_parser_t *)Args[0])->Handle, mpc_string(ml_string_value(Args[1])), mpcf_dtor_null);
	return (ml_value_t *)Parser;
}

ML_METHOD(".", MLStringT, MLParserStringT) {
	ml_mpc_parser_t *Parser = new(ml_mpc_parser_t);
	Parser->Type = MLParserStringT;
	Parser->Handle = mpc_and(2, mpcf_strfold, mpc_string(ml_string_value(Args[0])), ((ml_mpc_parser_t *)Args[1])->Handle, mpcf_dtor_null);
	return (ml_value_t *)Parser;
}

ML_METHOD(".", MLParserValueT, MLParserValueT) {
	ml_mpc_parser_t *Parser = new(ml_mpc_parser_t);
	Parser->Type = MLParserValueT;
	Parser->Handle = mpc_and(2, ml_mpc_fold_list, ((ml_mpc_parser_t *)Args[0])->Handle, ((ml_mpc_parser_t *)Args[1])->Handle, mpcf_dtor_null);
	return (ml_value_t *)Parser;
}

ML_METHOD("predictive", MLParserT) {
	ml_mpc_parser_t *Parser = new(ml_mpc_parser_t);
	Parser->Type = ((ml_mpc_parser_t *)Args[0])->Type;
	Parser->Handle = mpc_predictive(((ml_mpc_parser_t *)Args[0])->Handle);
	return (ml_value_t *)Parser;
}

ML_METHOD("define", MLParserT, MLParserT) {
	mpc_define(((ml_mpc_parser_t *)Args[0])->Handle, ((ml_mpc_parser_t *)Args[1])->Handle);
	((ml_mpc_parser_t *)Args[0])->Type = ((ml_mpc_parser_t *)Args[1])->Type;
	return Args[0];
}

ML_METHOD("copy", MLParserT) {
	ml_mpc_parser_t *Parser = new(ml_mpc_parser_t);
	Parser->Type = ((ml_mpc_parser_t *)Args[0])->Type;
	Parser->Handle = mpc_copy(((ml_mpc_parser_t *)Args[0])->Handle);
	return (ml_value_t *)Parser;
}

ML_METHOD("%", MLStringT, MLParserValueT) {
	const char *String = ml_string_value(Args[0]);
	ml_mpc_parser_t *Parser = (ml_mpc_parser_t *)Args[1];
	mpc_result_t Result[1];
	if (mpc_parse("", String, Parser->Handle, Result)) {
		return (ml_value_t *)Result->output;
	} else {
		return ml_error("ParseError", "Error parsing string: %s", mpc_err_string(Result->error));
	}
}

ML_METHOD("%", MLFileT, MLParserValueT) {
	FILE *File = ml_file_handle(Args[0]);
	ml_mpc_parser_t *Parser = (ml_mpc_parser_t *)Args[1];
	mpc_result_t Result[1];
	if (mpc_parse_file("", File, Parser->Handle, Result)) {
		return (ml_value_t *)Result->output;
	} else {
		return ml_error("ParseError", "Error parsing file: %s", mpc_err_string(Result->error));
	}
}

ML_METHOD("%", MLStringT, MLParserStringT) {
	const char *String = ml_string_value(Args[0]);
	ml_mpc_parser_t *Parser = (ml_mpc_parser_t *)Args[1];
	mpc_result_t Result[1];
	if (mpc_parse("", String, Parser->Handle, Result)) {
		return ml_string(Result->output, -1);
	} else {
		return ml_error("ParseError", "Error parsing string: %s", mpc_err_string(Result->error));
	}
}

ML_METHOD("%", MLFileT, MLParserStringT) {
	FILE *File = ml_file_handle(Args[0]);
	ml_mpc_parser_t *Parser = (ml_mpc_parser_t *)Args[1];
	mpc_result_t Result[1];
	if (mpc_parse_file("", File, Parser->Handle, Result)) {
		return ml_string(Result->output, -1);
	} else {
		return ml_error("ParseError", "Error parsing file: %s", mpc_err_string(Result->error));
	}
}

ML_METHOD(MLParserT, MLStringT) {
	ml_mpc_parser_t *Parser = new(ml_mpc_parser_t);
	Parser->Type = MLParserT;
	Parser->Handle = mpc_new(ml_string_value(Args[0]));
	return (ml_value_t *)Parser;
}

ML_FUNCTION(MpcRegex) {
	ML_CHECK_ARG_COUNT(1);
	ML_CHECK_ARG_TYPE(0, MLStringT);
	ml_mpc_parser_t *Parser = new(ml_mpc_parser_t);
	Parser->Type = MLParserStringT;
	Parser->Handle = mpc_re(ml_string_value(Args[0]));
	return (ml_value_t *)Parser;
}

extern mpc_parser_t *mpc_orv(int n, mpc_parser_t **parsers);

ML_FUNCTION(MLParserAny) {
//@any
//<Parser/i...:parser|string|regex
//>parser::value
// Returns a new parser that matches any of :mini:`Parser/i`, returning its value.
	mpc_parser_t *Parsers[Count];
	for (int I = 0; I < Count; ++I) {
		if (ml_is(Args[I], MLParserValueT)) {
			ml_mpc_parser_t *Arg = (ml_mpc_parser_t *)Args[I];
			Parsers[I] = Arg->Handle;
		} else if (ml_is(Args[I], MLParserStringT)) {
			ml_mpc_parser_t *Arg = (ml_mpc_parser_t *)Args[I];
			Parsers[I] = mpc_apply(Arg->Handle, ml_mpc_apply_value);
		} else if (ml_is(Args[I], MLStringT)) {
			Parsers[I] = mpc_apply(mpc_string(ml_string_value(Args[I])), ml_mpc_apply_value);
		} else if (ml_is(Args[I], MLRegexT)) {
			Parsers[I] = mpc_apply(mpc_re(ml_regex_pattern(Args[I])), ml_mpc_apply_value);
		} else {
			ML_CHECK_ARG_TYPE(I, MLParserT);
		}
	}
	ml_mpc_parser_t *Parser = new(ml_mpc_parser_t);
	Parser->Type = MLParserValueT;
	Parser->Handle = mpc_orv(Count, Parsers);
	return (ml_value_t *)Parser;
}

static ml_value_t *ml_mpc_char(void *Data, int Count, ml_value_t **Args) {
	ML_CHECK_ARG_COUNT(1);
	ML_CHECK_ARG_TYPE(0, MLStringT);
	const char *Chars = ml_string_value(Args[0]);
	ml_mpc_parser_t *Parser = new(ml_mpc_parser_t);
	Parser->Type = MLParserStringT;
	Parser->Handle = mpc_char(Chars[0]);
	return (ml_value_t *)Parser;
}

static ml_value_t *ml_mpc_range(void *Data, int Count, ml_value_t **Args) {
	ML_CHECK_ARG_COUNT(1);
	ML_CHECK_ARG_TYPE(0, MLStringT);
	if (ml_string_length(Args[0]) < 2) {
		return ml_error("ValueError", "MPC Range requires 2 characters");
	}
	const char *Chars = ml_string_value(Args[0]);
	ml_mpc_parser_t *Parser = new(ml_mpc_parser_t);
	Parser->Type = MLParserStringT;
	Parser->Handle = mpc_range(Chars[0], Chars[1]);
	return (ml_value_t *)Parser;
}

static ml_value_t *ml_mpc_oneof(void *Data, int Count, ml_value_t **Args) {
	ML_CHECK_ARG_COUNT(1);
	ML_CHECK_ARG_TYPE(0, MLStringT);
	const char *Chars = ml_string_value(Args[0]);
	ml_mpc_parser_t *Parser = new(ml_mpc_parser_t);
	Parser->Type = MLParserStringT;
	Parser->Handle = mpc_oneof(Chars);
	return (ml_value_t *)Parser;
}

static ml_value_t *ml_mpc_noneof(void *Data, int Count, ml_value_t **Args) {
	ML_CHECK_ARG_COUNT(1);
	ML_CHECK_ARG_TYPE(0, MLStringT);
	const char *Chars = ml_string_value(Args[0]);
	ml_mpc_parser_t *Parser = new(ml_mpc_parser_t);
	Parser->Type = MLParserStringT;
	Parser->Handle = mpc_noneof(Chars);
	return (ml_value_t *)Parser;
}

static ml_value_t *ml_mpc_string(void *Data, int Count, ml_value_t **Args) {
	ML_CHECK_ARG_COUNT(1);
	ML_CHECK_ARG_TYPE(0, MLStringT);
	const char *Chars = ml_string_value(Args[0]);
	ml_mpc_parser_t *Parser = new(ml_mpc_parser_t);
	Parser->Type = MLParserStringT;
	Parser->Handle = mpc_string(Chars);
	return (ml_value_t *)Parser;
}

void ml_mpc_init(ml_value_t **Slot) {
#include "mpc_init.c"
	Slot[0] = ml_module("mpc",
		"seq", MLParserSeq,
		"map", MLParserMap,
		"any", MLParserAny,
		"regex", MpcRegex,
		"char", ml_cfunction(NULL, ml_mpc_char),
		"range", ml_cfunction(NULL, ml_mpc_range),
		"oneof", ml_cfunction(NULL, ml_mpc_oneof),
		"noneof", ml_cfunction(NULL, ml_mpc_noneof),
		"string", ml_cfunction(NULL, ml_mpc_string),
		"Any", ml_mpc_string_parser(mpc_any()),
		"EOI", ml_mpc_string_parser(mpc_eoi()),
		"SOI", ml_mpc_string_parser(mpc_soi()),
		"Boundary", ml_mpc_string_parser(mpc_boundary()),
		"BoundaryNewLine", ml_mpc_string_parser(mpc_boundary_newline()),
		"WhiteSpace", ml_mpc_string_parser(mpc_whitespace()),
		"WhiteSpaces", ml_mpc_string_parser(mpc_whitespaces()),
		"Blank", ml_mpc_string_parser(mpc_blank()),
		"NewLine", ml_mpc_string_parser(mpc_newline()),
		"Tab", ml_mpc_string_parser(mpc_tab()),
		"Escape", ml_mpc_string_parser(mpc_escape()),
		"Digit", ml_mpc_string_parser(mpc_digit()),
		"HexDigit", ml_mpc_string_parser(mpc_hexdigit()),
		"OctDigit", ml_mpc_string_parser(mpc_octdigit()),
		"Digits", ml_mpc_string_parser(mpc_digits()),
		"HexDigits", ml_mpc_string_parser(mpc_hexdigits()),
		"OctDigits", ml_mpc_string_parser(mpc_octdigits()),
		"Lower", ml_mpc_string_parser(mpc_lower()),
		"Upper", ml_mpc_string_parser(mpc_upper()),
		"Alpha", ml_mpc_string_parser(mpc_alpha()),
		"Underscore", ml_mpc_string_parser(mpc_underscore()),
		"AlphaNum", ml_mpc_string_parser(mpc_alphanum()),
		"Int", ml_mpc_string_parser(mpc_int()),
		"Hex", ml_mpc_string_parser(mpc_hex()),
		"Oct", ml_mpc_string_parser(mpc_oct()),
		"Number", ml_mpc_string_parser(mpc_number()),
		"Real", ml_mpc_string_parser(mpc_real()),
		"Float", ml_mpc_string_parser(mpc_float()),
		"CharLit", ml_mpc_string_parser(mpc_char_lit()),
		"StringLit", ml_mpc_string_parser(mpc_string_lit()),
		"RegexLit", ml_mpc_string_parser(mpc_regex_lit()),
		"Ident", ml_mpc_string_parser(mpc_ident()),
	NULL);
}

void ml_library_entry0(ml_value_t **Slot) {
	ml_mpc_init(Slot);
}
