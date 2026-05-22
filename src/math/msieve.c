#include <minilang/ml_library.h>
#include <minilang/ml_array.h>
#include <minilang/ml_macros.h>
#include <minilang/ml_object.h>
#include <math.h>
#include <msieve.h>

#undef ML_CATEGORY
#define ML_CATEGORY "math/msieve"

static uint32_t Level1Cache, Level2Cache;
static enum cpu_type CpuType;

ML_FUNCTION(Factorize) {
	ML_CHECK_ARG_COUNT(1);
	ML_CHECK_ARG_TYPE(0, MLIntegerT);
	ml_stringbuffer_t Buffer[1] = {ML_STRINGBUFFER_INIT};
	ml_stringbuffer_append(Buffer, Args[0]);
	const char *Input = ml_stringbuffer_get_string(Buffer);
	msieve_obj *MSieve = msieve_obj_new(
		(char *)Input, 0, NULL, NULL, NULL,
		arc4random(), arc4random(),
		0, CpuType, Level1Cache, Level2Cache,
		0, 0, NULL
	);
	if (!MSieve) return ml_error("MathError", "Failed to initialize factorization");
	msieve_run(MSieve);
	if (!(MSieve->flags & MSIEVE_FLAG_FACTORIZATION_DONE)) {
		return ml_error("MathError", "Factorization was interrupted");
	}
	ml_value_t *Factors = ml_list();
	for (msieve_factor *Factor = MSieve->factors; Factor; Factor = Factor->next) {
		ml_list_put(Factors, ml_integer_parse(Factor->number, 10));
	}
	msieve_obj_free(MSieve);
	return Factors;
}

ML_LIBRARY_ENTRY0(math_msieve) {
	get_cache_sizes(&Level1Cache, &Level2Cache);
	CpuType = get_cpu_type();
#include "msieve_init.c"
	Slot[0] = ml_module("math/msieve",
		"factorize", Factorize,
	NULL);
}
