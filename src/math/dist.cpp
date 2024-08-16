#define BOOST_MATH_DOMAIN_ERROR_POLICY errno_on_error
#define BOOST_MATH_POLE_ERROR_POLICY errno_on_error
#define BOOST_MATH_OVERFLOW_ERROR_POLICY errno_on_error
#define BOOST_MATH_ROUNDING_ERROR_POLICY errno_on_error
#define BOOST_MATH_EVALUATION_ERROR_POLICY errno_on_error
#define BOOST_MATH_UNDERFLOW_ERROR_POLICY errno_on_error
#define BOOST_MATH_DENORM_ERROR_POLICY errno_on_error
#define BOOST_MATH_INDETERMINATE_RESULT_ERROR_POLICY errno_on_error

#include <minilang/ml_library.h>
#include <boost/random.hpp>
#include <boost/math/distributions.hpp>
#include <gc/gc_cpp.h>

using namespace boost;

ML_TYPE(DistT, (MLFunctionT), "math::dist");

static random::minstd_rand RNG;

#define RAND_FN(TYPE, CTYPE) \
\
ML_METHOD("random", TYPE) { \
	CTYPE *Dist = (CTYPE *)Args[0]; \
	return ml_real(Dist->Rand(RNG)); \
}

#define PROP_FN(METHOD, TYPE, CTYPE, FIELD) \
\
ML_METHOD(#METHOD, TYPE) { \
	CTYPE *Dist = (CTYPE *)Args[0]; \
	return ml_real(Dist->Dist.FIELD()); \
}

#define DIST_FN(METHOD, TYPE, CTYPE, FN) \
\
ML_METHOD(#METHOD, TYPE) { \
	CTYPE *Dist = (CTYPE *)Args[0]; \
	return ml_real(math::FN(Dist->Dist)); \
}

#define DIST_FN_REAL(METHOD, TYPE, CTYPE, FN) \
\
ML_METHOD(#METHOD, TYPE, MLRealT) { \
	CTYPE *Dist = (CTYPE *)Args[0]; \
	double X = ml_real_value(Args[1]); \
	return ml_real(math::FN(Dist->Dist, X)); \
}

#define DIST_FNS(TYPE, CTYPE) \
\
DIST_FN_REAL(pdf, TYPE, CTYPE, pdf) \
DIST_FN_REAL(cdf, TYPE, CTYPE, cdf) \
DIST_FN(mean, TYPE, CTYPE, mean) \
DIST_FN(stddev, TYPE, CTYPE, standard_deviation) \
DIST_FN(variance, TYPE, CTYPE, variance) \
DIST_FN(skewness, TYPE, CTYPE, skewness) \
DIST_FN(kurtosis, TYPE, CTYPE, kurtosis)

#define DIST_FNS_WITH_RANDOM(TYPE, CTYPE) \
\
RAND_FN(TYPE, CTYPE) \
DIST_FNS(TYPE, CTYPE)

#define DIST_PARAMS_0(TYPE, CTYPE)
#define DIST_ARGS_0(TYPE, CTYPE)
#define DIST_CONSTRUCTOR_0(TYPE, CTYPE) \
\
ML_METHOD(TYPE) { \
	return (ml_value_t *)new CTYPE(); \
}

#define DIST_PARAMS_1(TYPE, CTYPE) double X
#define DIST_ARGS_1(TYPE, CTYPE) X
#define DIST_CONSTRUCTOR_1(TYPE, CTYPE) \
\
ML_METHOD(TYPE, MLRealT) { \
	double X = ml_real_value(Args[0]); \
	return (ml_value_t *)new CTYPE(X); \
}

#define DIST_PARAMS_2(TYPE, CTYPE) double X, double Y
#define DIST_ARGS_2(TYPE, CTYPE) X, Y
#define DIST_CONSTRUCTOR_2(TYPE, CTYPE) \
\
ML_METHOD(TYPE, MLRealT, MLRealT) { \
	double X = ml_real_value(Args[0]); \
	double Y = ml_real_value(Args[1]); \
	return (ml_value_t *)new CTYPE(X, Y); \
}

#define DIST_PARAMS_3(TYPE, CTYPE) (double X, double Y, double Z)
#define DIST_ARGS_3(TYPE, CTYPE) (X, Y, Z)
#define DIST_CONSTRUCTOR_3(TYPE, CTYPE) \
\
ML_METHOD(TYPE, MLRealT, MLRealT, MLRealT) { \
	double X = ml_real_value(Args[0]); \
	double Y = ml_real_value(Args[1]); \
	double Z = ml_real_value(Args[2]); \
	return (ml_value_t *)new CTYPE(X, Y, Z); \
}

#define APPLY(MACRO, TYPE, CTYPE) MACRO(TYPE, CTYPE)

#define DIST_PARAMS(COUNT) APPLY(DIST_PARAMS_ ## COUNT, TYPE, CTYPE)
#define DIST_ARGS(COUNT) APPLY(DIST_ARGS_ ## COUNT, TYPE, CTYPE)
#define DIST_CONSTRUCTOR(COUNT, TYPE, CTYPE) APPLY(DIST_CONSTRUCTOR_ ## COUNT, TYPE, CTYPE)

#define DIST_TYPE_WITH_RANDOM(TYPE, NAME, COUNT) \
\
ML_TYPE(TYPE, (DistT), "math::dist::" #NAME); \
\
struct NAME ## _t : public gc { \
	ml_type_t *Type = TYPE; \
	math::NAME Dist; \
	random::NAME ## _distribution<double> Rand; \
	NAME ## _t(DIST_PARAMS(COUNT)) : Dist(DIST_ARGS(COUNT)), Rand(DIST_ARGS(COUNT)) {} \
}; \
\
DIST_CONSTRUCTOR(COUNT, TYPE, NAME ## _t) \
\
DIST_FNS_WITH_RANDOM(TYPE, NAME ## _t)

#define DIST_TYPE(TYPE, NAME, COUNT) \
\
ML_TYPE(TYPE, (DistT), "math::dist::" #NAME); \
\
struct NAME ## _t : public gc { \
	ml_type_t *Type = TYPE; \
	math::NAME Dist; \
	NAME ## _t(DIST_PARAMS(COUNT)) : Dist(DIST_ARGS(COUNT)) {} \
}; \
\
DIST_CONSTRUCTOR(COUNT, TYPE, NAME ## _t) \
\
DIST_FNS(TYPE, NAME ## _t)

/****************************************************/

DIST_TYPE_WITH_RANDOM(BernoulliT, bernoulli, 1)
PROP_FN(probability, BernoulliT, bernoulli_t, success_fraction)

DIST_TYPE(BinomialT, binomial, 2)
PROP_FN(trials, BinomialT, binomial_t, trials)
PROP_FN(probability, BinomialT, binomial_t, success_fraction)

DIST_TYPE(ChiSquaredT, chi_squared, 1)
PROP_FN(degrees, ChiSquaredT, chi_squared_t, degrees_of_freedom)

DIST_TYPE_WITH_RANDOM(ExponentialT, exponential, 1)
PROP_FN(lambda, ExponentialT, exponential_t, lambda)

DIST_TYPE_WITH_RANDOM(NormalT, normal, 2)

ML_LIBRARY_ENTRY0(math_dist) {
	RNG.seed(time(0));
#include "dist_init.cpp"
	stringmap_insert(DistT->Exports, "bernoulli", BernoulliT);
	stringmap_insert(DistT->Exports, "binomial", BinomialT);
	stringmap_insert(DistT->Exports, "chi_squared", ChiSquaredT);
	stringmap_insert(DistT->Exports, "exponential", ExponentialT);
	stringmap_insert(DistT->Exports, "normal", NormalT);
	Slot[0] = (ml_value_t *)DistT;
}
