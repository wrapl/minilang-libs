#include <minilang/minilang.h>
#include <minilang/ml_library.h>
#include <minilang/ml_object.h>
#include <minilang/ml_macros.h>
#include "diff.h"

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

ML_ENUM(DiffT, "diff", "Add", "Delete", "Common");

ML_FUNCTION(Diff) {
	ML_CHECK_ARG_COUNT(2);
	ML_CHECK_ARG_TYPE(0, MLSliceT);
	ML_CHECK_ARG_TYPE(1, MLSliceT);
	ml_value_t **A = (ml_value_t **)(((ml_slice_t *)Args[0])->Nodes + ((ml_slice_t *)Args[0])->Offset);
	ml_value_t **B = (ml_value_t **)(((ml_slice_t *)Args[1])->Nodes + ((ml_slice_t *)Args[1])->Offset);
	struct diff Diff[1];
	if (diff(Diff, NULL, diff_value0, sizeof(ml_value_t *), A, ml_slice_length(Args[0]), B, ml_slice_length(Args[1])) < 0) {
		return ml_error("DiffError", "Error computing difference");
	}
	ml_value_t *Result = ml_slice(Diff->sessz);
	for (int I = 0; I < Diff->sessz; ++I) {
		struct diff_ses *Ses = Diff->ses + I;
		ml_value_t *Type = ml_enum_value(DiffT, Ses->type + 1);
		ml_slice_put(Result, ml_tuplev(4,
			Type, *(ml_value_t **)Ses->e,
			ml_integer(Ses->originIdx),
			ml_integer(Ses->targetIdx)
		));
	}
	return Result;
}

ML_LIBRARY_ENTRY0(util_compare) {
#include "compare_init.c"
	Slot[0] = ml_module("util/compare",
		"diff", Diff,
	NULL);
}
