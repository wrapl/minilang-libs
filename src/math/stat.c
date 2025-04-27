#include <minilang/ml_library.h>
#include <minilang/ml_array.h>
#include <minilang/ml_macros.h>
#include <minilang/ml_object.h>

#undef ML_CATEGORY
#define ML_CATEGORY "math/stat"

ML_METHOD("stat::mean", MLVectorT) {

}

ML_LIBRARY_ENTRY0(math_stat) {
#include "stat_init.c"

}
