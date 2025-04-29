#include <minilang/ml_library.h>
#include <minilang/ml_array.h>
#include <minilang/ml_macros.h>
#include <minilang/ml_object.h>

#undef ML_CATEGORY
#define ML_CATEGORY "math/stat"

typedef struct statistic_t statistic_t;
typedef struct accumulator_t accumulator_t;
typedef struct calculator_t calculator_t;

struct calculator_t {
	ml_type_t *Type;
	ml_value_t *Calc;
	int Count;
	calculator_t *Depends[];
};

ML_TYPE(CalculatorT, (MLFunctionT), "calculator");

struct accumulator_t {
	ml_type_t *Type;
	ml_value_t *Init, *Update, *Calc;
	int Count;
	calculator_t *Calculators[];
};

ML_TYPE(AccumulatorT, (MLFunctionT), "accumulator");

struct statistic_t {
	ml_type_t *Type;
	ml_value_t *Calc;
	int Count;
	accumulator_t *Accumulators[];
};

ML_TYPE(StatisticT, (MLFunctionT), "statistic");

ML_GENERIC_TYPE(StatisticsT, MLListT, StatisticT);

typedef struct {
	ml_state_t Base;
	ml_value_t **Values;
	int *Config;
	int NumCalcs, NumAccs, NumStats;
} statistics_state_t;

static int statistics_max_calculator(calculator_t *Calc) {
	int Total = 1;
	for (int I = 0; I < Calc->Depends; ++I) Total += statistics_max_calculator(Calc->Depends[I]);
	return Total;
}

static int statistics_add_calculator(calculator_t *Calc, calculator_t **Calcs, int *NumCalcs) {
	int N = NumCalcs;
	for (int I = 0; I < N; ++I) if (Calcs[I] == Calc) return I;
	Calcs[N] = Calc;
	++*NumCalcs;
}

static __attribute__ ((noinline)) statistics_state_t *statistics_prepare(ml_value_t *Arg) {
	int NumStats = 0, MaxAccs = 0, MaxCalcs = 0;
	ML_LIST_FOREACH(Arg, Iter) {
		statistic_t *Stat = (statistic_t *)Iter->Value;
		++NumStats;
		MaxAccs += Stat->Count;
		for (int I = 0; I < Stat->Count; ++I) {
			accumulator_t *Acc = Stat->Accumulators[I];
			MaxCalcs += Acc->Count;
			for (int J = 0; J < Acc->Count; ++J) {
				calculator_t *Calc = Acc->Calculators[J];
				MaxCalcs += Calc->Count;
			}
		}
	}
	int NumAccs = 0, NumCalcs = 0;
	calculator_t *Calcs[MaxCalcs];
	accumulator_t *Accs[MaxAccs];
	ML_LIST_FOREACH(Arg, Iter) {
		statistic_t *Stat = (statistic_t *)Iter->Value;
		for (int I = 0; I < Stat->Count; ++I) {
			accumulator_t *Acc = Stat->Accumulators[I];
			for (int J = 0; J < NumAccs; ++J) if (Accs[J] == Acc) goto found_acc;
			Accs[NumAccs++] = Acc;
		found_acc:
			for (int J = 0; J < Acc->Count; ++J) {
				calculator_t *Calc = Acc->Calculators[J];
				MaxCalcs += Calc->Count;
			}
		}
	}
}

ML_METHODX("()", StatisticsT, MLSequenceT) {
	// 1. Compute set of unique accumulators
	// 2. Initialize accumulators
	// 3. Compute set of unique calculators (including dependencies)
	// 4. Iterate over sequence, invoking calculators and accumulators
	// 5. Finalize accumulators
	// 6. Calculate statistics


}

ML_LIBRARY_ENTRY0(math_stat) {
#include "stat_init.c"
	Slot[0] = ml_module("stat",
	NULL);
}
