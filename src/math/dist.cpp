#define BOOST_MATH_DOMAIN_ERROR_POLICY errno_on_error
#define BOOST_MATH_POLE_ERROR_POLICY errno_on_error
#define BOOST_MATH_OVERFLOW_ERROR_POLICY errno_on_error
#define BOOST_MATH_ROUNDING_ERROR_POLICY errno_on_error
#define BOOST_MATH_EVALUATION_ERROR_POLICY errno_on_error
#define BOOST_MATH_UNDERFLOW_ERROR_POLICY errno_on_error
#define BOOST_MATH_DENORM_ERROR_POLICY errno_on_error
#define BOOST_MATH_INDETERMINATE_RESULT_ERROR_POLICY errno_on_error

#include <minilang/ml_library.h>
#include <minilang/ml_array.h>
#include <boost/random.hpp>
#include <boost/math/distributions.hpp>
#include <gc/gc_cpp.h>

using namespace boost;

#undef ML_CATEGORY
#define ML_CATEGORY "math/dist"

ML_TYPE(DistT, (MLFunctionT), "math::dist");

static random::minstd_rand RNG;

#define PROP_FN(TYPE, NAME, METHOD, FIELD) \
\
ML_METHOD(#METHOD, TYPE) { \
	NAME ## _t *Dist = (NAME ## _t *)Args[0]; \
	return ml_real(Dist->Dist.FIELD()); \
}

#define DIST_FN(METHOD, TYPE, NAME, FN) \
\
ML_METHOD(#METHOD, TYPE) { \
	NAME ## _t *Dist = (NAME ## _t *)Args[0]; \
	return ml_real(math::FN(Dist->Dist)); \
}

#define DIST_FN_REAL(METHOD, TYPE, NAME, FN) \
\
ML_METHOD(#METHOD, TYPE, MLRealT) { \
	NAME ## _t *Dist = (NAME ## _t *)Args[0]; \
	double X = ml_real_value(Args[1]); \
	return ml_real(math::FN(Dist->Dist, X)); \
} \
\
ML_METHOD(#METHOD, TYPE, MLArrayT) { \
	NAME ## _t *Dist = (NAME ## _t *)Args[0]; \
	ml_array_t *A = (ml_array_t *)Args[1]; \
	if (A->Degree == -1) return (ml_value_t *)A; \
	if (A->Format == ML_ARRAY_FORMAT_ANY) return ml_error("TypeError", "Invalid types for array operation"); \
	int Degree = A->Degree; \
	ml_array_t *C = ml_array_alloc(ML_ARRAY_FORMAT_F64, Degree); \
	int DataSize = ml_array_copy(C, A); \
	double *Values = (double *)C->Base.Value; \
	for (int I = DataSize / sizeof(double); --I >= 0; ++Values) *Values = math::FN(Dist->Dist, *Values); \
	return (ml_value_t *)C; \
}

#define RAND_FN(TYPE, NAME) \
\
ML_METHOD("random", TYPE) { \
	NAME ## _t *Dist = (NAME ## _t *)Args[0]; \
	return ml_real(Dist->Rand(RNG)); \
}

#define DIST_FNS(TYPE, NAME) \
\
DIST_FN_REAL(pdf, TYPE, NAME, pdf) \
DIST_FN_REAL(cdf, TYPE, NAME, cdf) \
DIST_FN(mean, TYPE, NAME, mean) \
DIST_FN(stddev, TYPE, NAME, standard_deviation) \
DIST_FN(variance, TYPE, NAME, variance) \
DIST_FN(skewness, TYPE, NAME, skewness) \
DIST_FN(kurtosis, TYPE, NAME, kurtosis)

#define DIST_FNS_WITH_RANDOM(TYPE, NAME) \
\
DIST_FNS(TYPE, NAME) \
RAND_FN(TYPE, NAME)

#define DIST_PARAMS_0(TYPE, NAME)
#define DIST_ARGS_0(TYPE, NAME)
#define DIST_CONSTRUCTOR_0(TYPE, NAME) \
\
ML_METHOD(TYPE) { \
	return (ml_value_t *)new NAME ## _t(); \
}

#define DIST_PARAMS_1(TYPE, NAME) double X
#define DIST_ARGS_1(TYPE, NAME) X
#define DIST_CONSTRUCTOR_1(TYPE, NAME) \
\
ML_METHOD(TYPE, MLRealT) { \
	double X = ml_real_value(Args[0]); \
	return (ml_value_t *)new NAME ## _t(X); \
}

#define DIST_PARAMS_2(TYPE, NAME) double X, double Y
#define DIST_ARGS_2(TYPE, NAME) X, Y
#define DIST_CONSTRUCTOR_2(TYPE, NAME) \
\
ML_METHOD(TYPE, MLRealT, MLRealT) { \
	double X = ml_real_value(Args[0]); \
	double Y = ml_real_value(Args[1]); \
	return (ml_value_t *)new NAME ## _t(X, Y); \
}

#define DIST_PARAMS_3(TYPE, NAME) double X, double Y, double Z
#define DIST_ARGS_3(TYPE, NAME) X, Y, Z
#define DIST_CONSTRUCTOR_3(TYPE, NAME) \
\
ML_METHOD(TYPE, MLRealT, MLRealT, MLRealT) { \
	double X = ml_real_value(Args[0]); \
	double Y = ml_real_value(Args[1]); \
	double Z = ml_real_value(Args[2]); \
	return (ml_value_t *)new NAME ## _t(X, Y, Z); \
}

#define APPLY(MACRO, TYPE, NAME) MACRO(TYPE, NAME)

#define DIST_PARAMS(COUNT) APPLY(DIST_PARAMS_ ## COUNT, TYPE, NAME)
#define DIST_ARGS(COUNT) APPLY(DIST_ARGS_ ## COUNT, TYPE, NAME)
#define DIST_CONSTRUCTOR(COUNT, TYPE, NAME) APPLY(DIST_CONSTRUCTOR_ ## COUNT, TYPE, NAME)

#ifdef GENERATE_INIT
#define INITIALIZER(EXPR) INIT_CODE EXPR
#else
#define INITIALIZER(EXPR)
#endif

#define DIST_TYPE(TYPE, NAME, COUNT) \
\
ML_TYPE(TYPE, (DistT), "math::dist::" #NAME); \
\
struct NAME ## _t : public gc { \
	ml_type_t *Type = TYPE; \
	math::NAME ## _distribution<double> Dist; \
	NAME ## _t(DIST_PARAMS(COUNT)) : Dist(DIST_ARGS(COUNT)) {} \
}; \
\
DIST_CONSTRUCTOR(COUNT, TYPE, NAME) \
\
DIST_FNS(TYPE, NAME)

#define DIST_TYPE_WITH_RANDOM(TYPE, NAME, NAME2, COUNT) \
\
struct NAME ## _t; \
\
ML_TYPE(TYPE, (DistT), "math::dist::" #NAME); \
\
INITIALIZER(TYPE->call = ((void (*)(ml_state_t *, ml_value_t *, int, ml_value_t **))NAME ## _call);) \
\
struct NAME ## _t : public gc { \
	ml_type_t *Type = TYPE; \
	math::NAME ## _distribution<double> Dist; \
	random::NAME2 ## _distribution<double> Rand; \
	NAME ## _t(DIST_PARAMS(COUNT)) : Dist(DIST_ARGS(COUNT)), Rand(DIST_ARGS(COUNT)) {} \
}; \
static void NAME ## _call(ml_state_t *Caller, NAME ## _t *Dist, int Count, ml_value_t **Args) { \
	ML_RETURN(ml_real(Dist->Rand(RNG))); \
} \
\
DIST_CONSTRUCTOR(COUNT, TYPE, NAME) \
\
DIST_FNS_WITH_RANDOM(TYPE, NAME)

/****************************************************/

DIST_TYPE_WITH_RANDOM(BernoulliT, bernoulli, bernoulli, 1)
PROP_FN(BernoulliT, bernoulli, probability, success_fraction)

DIST_TYPE(BinomialT, binomial, 2)
PROP_FN(BinomialT, binomial, trials, trials)
PROP_FN(BinomialT, binomial, probability, success_fraction)

DIST_TYPE_WITH_RANDOM(ChiSquaredT, chi_squared, chi_squared, 1)
PROP_FN(ChiSquaredT, chi_squared, degrees, degrees_of_freedom)

DIST_TYPE_WITH_RANDOM(ExponentialT, exponential, exponential, 1)
PROP_FN(ExponentialT, exponential, lambda, lambda)

DIST_TYPE_WITH_RANDOM(GammaT, gamma, gamma, 2)
PROP_FN(GammaT, gamma, shape, shape)
PROP_FN(GammaT, gamma, scale, scale)

DIST_TYPE(HyperGeometricT, hypergeometric, 3)
PROP_FN(HyperGeometricT, hypergeometric, total, total)
PROP_FN(HyperGeometricT, hypergeometric, defective, defective)
PROP_FN(HyperGeometricT, hypergeometric, sample, sample_count)

DIST_TYPE_WITH_RANDOM(LognormalT, lognormal, lognormal, 2)
PROP_FN(LognormalT, lognormal, location, location)
PROP_FN(LognormalT, lognormal, scale, scale)

DIST_TYPE(NegativeBinomialT, negative_binomial, 2)
PROP_FN(NegativeBinomialT, negative_binomial, successes, successes)
PROP_FN(NegativeBinomialT, negative_binomial, probability, success_fraction)

DIST_TYPE_WITH_RANDOM(NormalT, normal, normal, 2)

DIST_TYPE(ParetoT, pareto, 2)
PROP_FN(ParetoT, pareto, scale, scale)
PROP_FN(ParetoT, pareto, shape, shape)

DIST_TYPE(PoissonT, poisson, 1)

DIST_TYPE_WITH_RANDOM(StudentsT, students_t, student_t, 1)
PROP_FN(StudentsT, students_t, degrees, degrees_of_freedom)

DIST_TYPE_WITH_RANDOM(TriangularT, triangular, triangle, 3)
PROP_FN(TriangularT, triangular, lower, lower)
PROP_FN(TriangularT, triangular, mode, mode)
PROP_FN(TriangularT, triangular, upper, upper)

DIST_TYPE_WITH_RANDOM(UniformT, uniform, uniform_real, 2)
PROP_FN(UniformT, uniform, lower, lower)
PROP_FN(UniformT, uniform, upper, upper)

ML_LIBRARY_ENTRY0(math_dist) {
	RNG.seed(time(0));
#include "dist_init.cpp"
	stringmap_insert(DistT->Exports, "bernoulli", BernoulliT);
	stringmap_insert(DistT->Exports, "binomial", BinomialT);
	stringmap_insert(DistT->Exports, "chi_squared", ChiSquaredT);
	stringmap_insert(DistT->Exports, "exponential", ExponentialT);
	stringmap_insert(DistT->Exports, "gamma", GammaT);
	stringmap_insert(DistT->Exports, "hypergeometric", HyperGeometricT);
	stringmap_insert(DistT->Exports, "lognormal", LognormalT);
	stringmap_insert(DistT->Exports, "negative_binomial", NegativeBinomialT);
	stringmap_insert(DistT->Exports, "normal", NormalT);
	stringmap_insert(DistT->Exports, "pareto", ParetoT);
	stringmap_insert(DistT->Exports, "poisson", PoissonT);
	stringmap_insert(DistT->Exports, "students_t", StudentsT);
	stringmap_insert(DistT->Exports, "triangular", TriangularT);
	stringmap_insert(DistT->Exports, "uniform", UniformT);
	Slot[0] = (ml_value_t *)DistT;
}
