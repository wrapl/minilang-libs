#include <minilang/ml_library.h>
#include <minilang/ml_array.h>
#include <minilang/ml_macros.h>
#include <minilang/ml_object.h>

#undef ML_CATEGORY
#define ML_CATEGORY "math/stat"

ML_TYPE(MLStatisticT, (MLFunctionT), "statistic");

ML_TYPE(MLAccumulatorT, (MLFunctionT), "accumulator");

ML_TYPE(MLCalculatorT, (MLFunctionT), "calculator");

static void ml_statistic_accumulators(ml_value_t *Statistic, inthash_t Accumulators) {

}

ML_LIBRARY_ENTRY0(math_stat) {
#include "stat_init.c"

}
