#include <minilang/minilang.h>
#include <minilang/ml_library.h>
#include <minilang/ml_object.h>
#include <minilang/ml_macros.h>
#include "diff.h"

ML_ENUM(DiffT, "diff", "Insert", "Delete", "Common");

ML_METHOD_ANON(DiffMethod, "compare::diff");

static int diff_utf8(void *Data, const void *A, const void *B) {
	return *(uint32_t *)A == *(uint32_t *)B;
}

ML_METHOD(DiffMethod, MLStringT, MLStringT) {
	int ACount = ml_string_count(Args[0]);
	int BCount = ml_string_count(Args[1]);
	uint32_t *A = anew(uint32_t, ACount + 1);
	uint32_t *B = anew(uint32_t, BCount + 1);
	ml_string_codes(Args[0], A);
	ml_string_codes(Args[1], B);
	struct diff Diff[1];
	if (diff(Diff, NULL, diff_utf8, sizeof(uint32_t), A, ACount, B, BCount) < 0) {
		return ml_error("DiffError", "Error computing difference");
	}
	ml_value_t *DiffInsert = ml_enum_value(DiffT, 1);
	ml_value_t *DiffDelete = ml_enum_value(DiffT, 2);
	ml_value_t *DiffCommon = ml_enum_value(DiffT, 3);
	ml_value_t *Result = ml_list();
	struct diff_ses *Ses = Diff->ses;
	struct diff_ses *End = Ses + Diff->sessz;
	ml_stringbuffer_t Buffer[1] = {ML_STRINGBUFFER_INIT};
	while (Ses < End) {
		struct diff_ses *Beg = Ses;
		switch (Ses->type) {
		case DIFF_ADD: {
			int Target = Ses->targetIdx;
			do { ++Target; ++Ses; } while (Ses < End && Ses->type == DIFF_ADD && Ses->targetIdx == Target);
			while (Beg < Ses) ml_stringbuffer_put32(Buffer, *(uint32_t *)((Beg++)->e));
			ml_list_put(Result, ml_tuplev(3, DiffInsert, ml_stringbuffer_get_value(Buffer), MLNil));
			break;
		}
		case DIFF_DELETE: {
			int Origin = Ses->originIdx;
			ml_value_t *OriginValue = ml_integer(Origin);
			do { ++Origin; ++Ses; } while (Ses < End && Ses->type == DIFF_DELETE && Ses->originIdx == Origin);
			while (Beg < Ses) ml_stringbuffer_put32(Buffer, *(uint32_t *)((Beg++)->e));
			ml_list_put(Result, ml_tuplev(3, DiffDelete, ml_stringbuffer_get_value(Buffer), OriginValue));
			break;
		}
		case DIFF_COMMON: {
			int Origin = Ses->originIdx;
			int Target = Ses->targetIdx;
			ml_value_t *OriginValue = ml_integer(Origin);
			do { ++Origin; ++Target; ++Ses; } while (Ses < End && Ses->type == DIFF_COMMON && Ses->originIdx == Origin && Ses->targetIdx == Target);
			while (Beg < Ses) ml_stringbuffer_put32(Buffer, *(uint32_t *)((Beg++)->e));
			ml_list_put(Result, ml_tuplev(3, DiffCommon, ml_stringbuffer_get_value(Buffer), OriginValue));
			break;
		}
		}
	}
	return Result;
}

static int diff_value(void *Data, ml_value_t *A, ml_value_t *B) {
	ml_type_t *Type = ml_typeof(A);
	if (Type != ml_typeof(B)) return 0;
	typeof(diff_value) *fn = ml_typed_fn_get(Type, diff_value);
	if (fn) return fn(Data, A, B);
	return A == B;
}

static int ML_TYPED_FN(diff_value, MLIntegerT, void *Data, ml_value_t *A, ml_value_t *B) {
	return ml_integer_value(A) == ml_integer_value(B);
}

static int ML_TYPED_FN(diff_value, MLRealT, void *Data, ml_value_t *A, ml_value_t *B) {
	return ml_real_value(A) == ml_real_value(B);
}

static int ML_TYPED_FN(diff_value, MLAddressT, void *Data, ml_value_t *A, ml_value_t *B) {
	size_t Length = ml_address_length(A);
	if (Length != ml_address_length(B)) return 0;
	return !memcmp(ml_address_value(A), ml_address_value(B), Length);
}

static int diff_value0(void *Data, const void *A, const void *B) {
	return diff_value(Data, *(ml_value_t **)A, *(ml_value_t **)B);
}

ML_METHOD(DiffMethod, MLSliceT, MLSliceT) {
	ml_value_t **A = (ml_value_t **)(((ml_slice_t *)Args[0])->Nodes + ((ml_slice_t *)Args[0])->Offset);
	ml_value_t **B = (ml_value_t **)(((ml_slice_t *)Args[1])->Nodes + ((ml_slice_t *)Args[1])->Offset);
	struct diff Diff[1];
	if (diff(Diff, NULL, diff_value0, sizeof(ml_value_t *), A, ml_slice_length(Args[0]), B, ml_slice_length(Args[1])) < 0) {
		return ml_error("DiffError", "Error computing difference");
	}
	ml_value_t *DiffInsert = ml_enum_value(DiffT, 1);
	ml_value_t *DiffDelete = ml_enum_value(DiffT, 2);
	ml_value_t *DiffCommon = ml_enum_value(DiffT, 3);
	ml_value_t *Result = ml_list();
	struct diff_ses *Ses = Diff->ses;
	struct diff_ses *End = Ses + Diff->sessz;
	while (Ses < End) {
		struct diff_ses *Beg = Ses;
		switch (Ses->type) {
		case DIFF_ADD: {
			int Target = Ses->targetIdx;
			do { ++Target; ++Ses; } while (Ses < End && Ses->type == DIFF_ADD && Ses->targetIdx == Target);
			ml_value_t *Slice = ml_list();
			while (Beg < Ses) ml_list_put(Slice, *(ml_value_t **)((Beg++)->e));
			ml_list_put(Result, ml_tuplev(3, DiffInsert, Slice, MLNil));
			break;
		}
		case DIFF_DELETE: {
			int Origin = Ses->originIdx;
			ml_value_t *OriginValue = ml_integer(Origin);
			do { ++Origin; ++Ses; } while (Ses < End && Ses->type == DIFF_DELETE && Ses->originIdx == Origin);
			ml_value_t *Slice = ml_list();
			while (Beg < Ses) ml_list_put(Slice, *(ml_value_t **)((Beg++)->e));
			ml_list_put(Result, ml_tuplev(3, DiffDelete, Slice, OriginValue));
			break;
		}
		case DIFF_COMMON: {
			int Origin = Ses->originIdx;
			int Target = Ses->targetIdx;
			ml_value_t *OriginValue = ml_integer(Origin);
			do { ++Origin; ++Target; ++Ses; } while (Ses < End && Ses->type == DIFF_COMMON && Ses->originIdx == Origin && Ses->targetIdx == Target);
			ml_value_t *Slice = ml_list();
			while (Beg < Ses) ml_list_put(Slice, *(ml_value_t **)((Beg++)->e));
			ml_list_put(Result, ml_tuplev(3, DiffCommon, Slice, OriginValue));
			break;
		}
		}
	}
	return Result;
}

typedef struct {
	ml_state_t Base;
	ml_value_t *Args[2];
} diff_sequence_state_t;

static void diff_sequence_b(diff_sequence_state_t *State, ml_value_t *Value) {
	if (ml_is_error(Value)) ML_CONTINUE(State->Base.Caller, Value);
	State->Args[1] = Value;
	return ml_call(State->Base.Caller, DiffMethod, 2, State->Args);
}

static void diff_sequence_a(diff_sequence_state_t *State, ml_value_t *Value) {
	if (ml_is_error(Value)) ML_CONTINUE(State->Base.Caller, Value);
	State->Args[0] = Value;
	if (ml_is(State->Args[1], MLSliceT)) {
		return ml_call(State->Base.Caller, DiffMethod, 2, State->Args);
	} else {
		State->Base.run = (ml_state_fn)diff_sequence_b;
		return ml_call(State, MLSliceT->Constructor, 1, State->Args + 1);
	}
}

ML_METHODX(DiffMethod, MLSequenceT, MLSequenceT) {
	diff_sequence_state_t *State = new(diff_sequence_state_t);
	State->Base.Caller = Caller;
	State->Base.Context = Caller->Context;
	State->Args[0] = Args[0];
	State->Args[1] = Args[1];
	if (ml_is(State->Args[0], MLStateT)) {
		State->Base.run = (ml_state_fn)diff_sequence_b;
		return ml_call(State, MLSliceT->Constructor, 1, State->Args + 1);
	} else {
		State->Base.run = (ml_state_fn)diff_sequence_a;
		return ml_call(State, MLSliceT->Constructor, 1, State->Args);
	}
}

ML_LIBRARY_ENTRY0(util_compare) {
#include "compare_init.c"
	Slot[0] = ml_module("util/compare",
		"diff", DiffMethod,
	NULL);
}
