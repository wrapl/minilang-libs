#include <minilang/ml_library.h>
#include <minilang/ml_array.h>
#include <minilang/ml_macros.h>
#include <minilang/ml_object.h>
#include <math.h>

#undef ML_CATEGORY
#define ML_CATEGORY "math/stat"

typedef struct statistic_t statistic_t;
typedef struct accumulator_t accumulator_t;
typedef struct calculator_t calculator_t;

struct calculator_t {
	ml_type_t *Type;
	ml_value_t *Calc;
	int NumDepends, Rank;
	calculator_t *Depends[];
};

ML_TYPE(CalculatorT, (), "calculator");

struct accumulator_t {
	ml_type_t *Type;
	ml_value_t *Init, *Update;
	int NumCalcs;
	calculator_t *Calcs[];
};

ML_TYPE(AccumulatorT, (), "accumulator");

struct statistic_t {
	ml_type_t *Type;
	ml_value_t *Calc;
	calculator_t **Calcs;
	accumulator_t **Accs;
	statistic_t **Stats;
	int NumDepends, ConfigSize, Rank;
	int NumAccs, NumCalcs, NumStats;
	ml_value_t *Depends[];
};

static void statistic_call(ml_state_t *Caller, statistic_t *Stat, int Count, ml_value_t **Args);

ML_TYPE(StatisticT, (MLFunctionT), "statistic",
	.call = (void *)statistic_call
);

static calculator_t *calculator(ml_value_t *Fn, int Count, ...) {
	calculator_t *Calc = xnew(calculator_t, Count, calculator_t *);
	Calc->Type = CalculatorT;
	Calc->Calc = Fn;
	Calc->NumDepends = Count;
	int Rank = 0;
	va_list Args;
	va_start(Args, Count);
	for (int I = 0; I < Count; ++I) {
		calculator_t *Dep = va_arg(Args, calculator_t *);
		Calc->Depends[I] = Dep;
		if (Rank < Dep->Rank) Rank = Dep->Rank;
	}
	va_end(Args);
	Calc->Rank = Rank + 1;
	return Calc;
}

static accumulator_t *accumulator(ml_value_t *Init, ml_value_t *Update, int Count, ...) {
	accumulator_t *Acc = xnew(accumulator_t, Count, accumulator_t *);
	Acc->Type = AccumulatorT;
	Acc->Init = Init;
	Acc->Update = Update;
	Acc->NumCalcs = Count;
	va_list Args;
	va_start(Args, Count);
	for (int I = 0; I < Count; ++I) {
		calculator_t *Calc = va_arg(Args, calculator_t *);
		Acc->Calcs[I] = Calc;

	}
	va_end(Args);
	return Acc;
}

typedef struct {
	calculator_t **Calcs;
	int Max, Num, ConfigSize;
} calculators_t;

static void calculators_add(calculators_t *Calcs, calculator_t *Calc) {
	for (int I = 0; I < Calcs->Num; ++I) if (Calcs->Calcs[I] == Calc) return;
	if (Calcs->Num == Calcs->Max) {
		calculator_t **Calcs2 = anew(calculator_t *, Calcs->Max + 4);
		memcpy(Calcs2, Calcs->Calcs, Calcs->Max * sizeof(calculator_t *));
		Calcs->Calcs = Calcs2;
		Calcs->Max += 4;
	}
	Calcs->Calcs[Calcs->Num++] = Calc;
	Calcs->ConfigSize += 1 + Calc->NumDepends;
	for (int I = 0; I < Calc->NumDepends; ++I) calculators_add(Calcs, Calc->Depends[I]);
}

typedef struct {
	calculators_t *Calcs;
	accumulator_t **Accs;
	int Max, Num, ConfigSize;
} accumulators_t;

static void accumulators_add(accumulators_t *Accs, accumulator_t *Acc) {
	for (int I = 0; I < Accs->Num; ++I) if (Accs->Accs[I] == Acc) return;
	if (Accs->Num == Accs->Max) {
		accumulator_t **Accs2 = anew(accumulator_t *, Accs->Max + 4);
		memcpy(Accs2, Accs->Accs, Accs->Max * sizeof(accumulator_t *));
		Accs->Accs = Accs2;
		Accs->Max += 4;
	}
	Accs->Accs[Accs->Num++] = Acc;
	Accs->ConfigSize += 1 + Acc->NumCalcs;
	for (int J = 0; J < Acc->NumCalcs; ++J) calculators_add(Accs->Calcs, Acc->Calcs[J]);
}

typedef struct {
	accumulators_t *Accs;
	statistic_t **Stats;
	int Max, Num, ConfigSize;
} statistics_t;

static void statistics_add(statistics_t *Stats, statistic_t *Stat) {
	for (int I = 0; I < Stats->Num; ++I) if (Stats->Stats[I] == Stat) return;
	if (Stats->Num == Stats->Max) {
		statistic_t **Stats2 = anew(statistic_t *, Stats->Max + 4);
		memcpy(Stats2, Stats->Stats, Stats->Max * sizeof(accumulator_t *));
		Stats->Stats = Stats2;
		Stats->Max += 4;
	}
	Stats->Stats[Stats->Num++] = Stat;
	Stats->ConfigSize += 1 + Stat->NumDepends;
	for (int J = 0; J < Stat->NumDepends; ++J) {
		ml_value_t *Dep = Stat->Depends[J];
		ml_type_t *Type = ml_typeof(Dep);
		if (Type == AccumulatorT) {
			accumulator_t *Acc = (accumulator_t *)Dep;
			accumulators_add(Stats->Accs, Acc);
		} else if (Type == StatisticT) {
			statistic_t *Stat2 = (statistic_t *)Dep;
			statistics_add(Stats, Stat2);
		}
	}
}

static statistic_t *statistic(ml_value_t *Fn, int Count, ...) {
	statistic_t *Stat = xnew(statistic_t, Count, ml_value_t *);
	Stat->Type = StatisticT;
	Stat->Calc = Fn;
	Stat->NumDepends = Count;
	int Rank = 0;
	calculators_t Calcs[1] = {{anew(calculator_t *, 4), 4, 0, 1}};
	accumulators_t Accs[1] = {{Calcs, anew(accumulator_t *, 4), 4, 0, 1}};
	statistics_t Stats[1] = {{Accs, anew(statistic_t *, 4), 4, 0, 1}};
	va_list Args;
	va_start(Args, Count);
	for (int I = 0; I < Count; ++I) {
		ml_value_t *Dep = va_arg(Args, ml_value_t *);
		Stat->Depends[I] = Dep;
		ml_type_t *Type = ml_typeof(Dep);
		if (Type == AccumulatorT) {
			accumulator_t *Acc = (accumulator_t *)Dep;
			accumulators_add(Accs, Acc);
		} else if (Type == StatisticT) {
			statistic_t *Stat2 = (statistic_t *)Dep;
			statistics_add(Stats, Stat2);
			if (Rank < Stat2->Rank) Rank = Stat2->Rank;
		}
	}
	va_end(Args);
	Stat->Calcs = Calcs->Calcs;
	Stat->Accs = Accs->Accs;
	Stat->Stats = Stats->Stats;
	Stat->NumCalcs = Calcs->Num;
	Stat->NumAccs = Accs->Num;
	Stat->NumStats = Stats->Num;
	Stat->ConfigSize = Count + Stats->ConfigSize + Accs->ConfigSize + Calcs->ConfigSize;
	Stat->Rank = Rank + 1;
	return Stat;
}

ML_GENERIC_TYPE(StatisticsT, MLListT, StatisticT);

typedef struct {
	ml_state_t Base;
	statistic_t **Stats;
	calculator_t **Calcs;
	accumulator_t **Accs;
	ml_value_t **StatValues, **AccValues, **CalcValues;
	ml_value_t *Iter;
	int *StatConfigs, *AccConfigs, *CalcConfigs, *Configs;
	int NumStats, NumAccs, NumCalcs;
	int Index, Count;
	ml_value_t *Args[];
} statistics_state_t;

static void statistics_statistic(statistics_state_t *State, ml_value_t *Value) {
	if (ml_is_error(Value)) ML_CONTINUE(State->Base.Caller, Value);
	int Index = State->Index;
	State->StatValues[Index] = Value;
	if (Index) {
		State->Index = --Index;
		statistic_t *Stat = State->Stats[Index];
		int *Config = State->Configs + State->StatConfigs[Index];
		for (int I = 0; I < Stat->NumDepends; ++I) {
			State->Args[I] = State->AccValues[Config[I]];
		}
		return ml_call(State, Stat->Calc, Stat->NumDepends, State->Args);
	}
	if (!State->Count) ML_CONTINUE(State->Base.Caller, State->StatValues[0]);
	ml_value_t *Result = ml_list();
	int *Config = State->Configs;
	for (int I = 0; I < State->Count; ++I) {
		ml_list_put(Result, State->StatValues[Config[I]]);
	}
	ML_CONTINUE(State->Base.Caller, Result);
}

static void statistics_iterate(statistics_state_t *State, ml_value_t *Value);

static void statistics_accumulator_update(statistics_state_t *State, ml_value_t *Value) {
	if (ml_is_error(Value)) ML_CONTINUE(State->Base.Caller, Value);
	int Index = State->Index;
	State->AccValues[Index] = Value;
	if (Index) {
		State->Index = --Index;
		accumulator_t *Acc = State->Accs[Index];
		int *Config = State->Configs + State->AccConfigs[Index];
		State->Args[0] = State->AccValues[Index];
		for (int I = 0; I < Acc->NumCalcs; ++I) {
			State->Args[I + 1] = State->CalcValues[Config[I]];
		}
		return ml_call(State, Acc->Update, Acc->NumCalcs + 1, State->Args);
	}
	State->Base.run = (ml_state_fn)statistics_iterate;
	return ml_iter_next((ml_state_t *)State, State->Iter);
}

static void statistics_calculator_calc(statistics_state_t *State, ml_value_t *Value) {
	if (ml_is_error(Value)) ML_CONTINUE(State->Base.Caller, Value);
	int Index = State->Index;
	State->CalcValues[Index] = Value;
	if (Index) {
		State->Index = --Index;
		calculator_t *Calc = State->Calcs[Index];
		int *Config = State->Configs + State->CalcConfigs[Index];
		for (int I = 0; I < Calc->NumDepends; ++I) {
			State->Args[I] = State->CalcValues[Config[I]];
		}
		return ml_call(State, Calc->Calc, Calc->NumDepends, State->Args);
	}
	Index = State->Index = State->NumAccs - 1;
	accumulator_t *Acc = State->Accs[Index];
	int *Config = State->Configs + State->AccConfigs[Index];
	State->Args[0] = State->AccValues[Index];
	for (int I = 0; I < Acc->NumCalcs; ++I) {
		State->Args[I + 1] = State->CalcValues[Config[I]];
	}
	State->Base.run = (ml_state_fn)statistics_accumulator_update;
	return ml_call(State, Acc->Update, Acc->NumCalcs + 1, State->Args);
}

static void statistics_iterate(statistics_state_t *State, ml_value_t *Value) {
	if (ml_is_error(Value)) ML_CONTINUE(State->Base.Caller, Value);
	if (Value == MLNil) {
		int Index = State->Index = State->NumStats - 1;
		statistic_t *Stat = State->Stats[Index];
		int *Config = State->Configs + State->StatConfigs[Index];
		for (int I = 0; I < Stat->NumDepends; ++I) {
			State->Args[I] = State->AccValues[Config[I]];
		}
		State->Base.run = (ml_state_fn)statistics_statistic;
		return ml_call(State, Stat->Calc, Stat->NumDepends, State->Args);
	}
	State->Iter = Value;
	int Index = State->Index = State->NumCalcs - 1;
	if (Index >= 0) {
		calculator_t *Calc = State->Calcs[Index];
		int *Config = State->Configs + State->CalcConfigs[Index];
		for (int I = 0; I < Calc->NumDepends; ++I) {
			State->Args[I] = State->CalcValues[Config[I]];
		}
		State->Base.run = (ml_state_fn)statistics_calculator_calc;
		return ml_call(State, Calc->Calc, Calc->NumDepends, State->Args);
	}
	Index = State->Index = State->NumAccs - 1;
	accumulator_t *Acc = State->Accs[Index];
	int *Config = State->Configs + State->AccConfigs[Index];
	State->Args[0] = State->AccValues[Index];
	for (int I = 0; I < Acc->NumCalcs; ++I) {
		State->Args[I + 1] = State->CalcValues[Config[I]];
	}
	State->Base.run = (ml_state_fn)statistics_accumulator_update;
	return ml_call(State, Acc->Update, Acc->NumCalcs + 1, State->Args);
}

static void statistics_accumulator_init(statistics_state_t *State, ml_value_t *Value) {
	if (ml_is_error(Value)) ML_CONTINUE(State->Base.Caller, Value);
	int Index = State->Index;
	State->AccValues[Index] = Value;
	if (Index) {
		State->Index = --Index;
		return ml_call(State, State->Accs[Index]->Init, 0, NULL);
	}
	State->Base.run = (ml_state_fn)statistics_iterate;
	return ml_iterate((ml_state_t *)State, State->Iter);
}

static int calculators_compare(const void *A, const void *B) {
	const calculator_t *CalcA = *(const calculator_t **)A;
	const calculator_t *CalcB = *(const calculator_t **)B;
	if (CalcA->Rank < CalcB->Rank) return 1;
	if (CalcA->Rank > CalcB->Rank) return -1;
	if (CalcA < CalcB) return -1;
	if (CalcA > CalcB) return 1;
	return 0;
}

static int statistics_compare(const void *A, const void *B) {
	const statistic_t *StatA = *(const statistic_t **)A;
	const statistic_t *StatB = *(const statistic_t **)B;
	if (StatA->Rank < StatB->Rank) return 1;
	if (StatA->Rank > StatB->Rank) return -1;
	if (StatA < StatB) return -1;
	if (StatA > StatB) return 1;
	return 0;
}

static __attribute__ ((noinline)) statistics_state_t *statistics_prepare(ml_value_t *Arg) {
	int Length = ml_list_length(Arg);
	if (!Length) return NULL;
	int MaxStats = Length, MaxAccs = 0, MaxCalcs = 0;
	ML_LIST_FOREACH(Arg, Iter) {
		statistic_t *Stat = (statistic_t *)Iter->Value;
		MaxStats += Stat->NumStats;
		MaxAccs += Stat->NumAccs;
		MaxCalcs += Stat->NumCalcs;
	}
	statistic_t **Stats = anew(statistic_t *, MaxStats), **StatSlot = Stats;
	ML_LIST_FOREACH(Arg, Iter) *StatSlot++ = (statistic_t *)Iter->Value;
	accumulator_t **Accs = anew(accumulator_t *, MaxAccs);
	calculator_t **Calcs = anew(calculator_t *, MaxCalcs);
	int NumStats = Length, NumAccs = 0, NumCalcs = 0, MaxArgs = 1, ConfigSize = Length;
	for (int I = 0; I < Length; ++I) {
		statistic_t *Stat = Stats[I];
		ConfigSize += 1 + Stat->NumDepends;
		if (MaxArgs < Stat->NumDepends) MaxArgs = Stat->NumDepends;
		for (int J = 0; J < Stat->NumStats; ++J) {
			statistic_t *Stat2 = Stat->Stats[J];
			if (MaxArgs < Stat2->NumDepends) MaxArgs = Stat2->NumDepends;
			for (int K = 0; K < NumStats; ++K) if (Stats[K] == Stat2) goto found_stat;
			Stats[NumStats++] = Stat2;
			ConfigSize += 1 + Stat2->NumDepends;
		found_stat:;
		}
		for (int J = 0; J < Stat->NumAccs; ++J) {
			accumulator_t *Acc = Stat->Accs[J];
			if (MaxArgs < Acc->NumCalcs + 1) MaxArgs = Acc->NumCalcs + 1;
			for (int K = 0; K < NumAccs; ++K) if (Accs[K] == Acc) goto found_acc;
			Accs[NumAccs++] = Acc;
			ConfigSize += 1 + Acc->NumCalcs;
		found_acc:;
		}
		for (int J = 0; J < Stat->NumCalcs; ++J) {
			calculator_t *Calc = Stat->Calcs[J];
			if (MaxArgs < Calc->NumDepends) MaxArgs = Calc->NumDepends;
			for (int K = 0; K < NumCalcs; ++K) if (Calcs[K] == Calc) goto found_calc;
			Calcs[NumCalcs++] = Calc;
			ConfigSize += 1 + Calc->NumDepends;
		found_calc:;
		}
	}
	qsort(Calcs, NumCalcs, sizeof(calculator_t *), calculators_compare);
	qsort(Stats, NumStats, sizeof(statistic_t *), statistics_compare);
	int *Configs = anew(int, ConfigSize), *Config0 = Configs;
	ML_LIST_FOREACH(Arg, Iter) {
		statistic_t *Stat = (statistic_t *)Iter->Value;
		for (int K = 0; K < NumStats; ++K) {
			if (Stats[K] == Stat) {
				*Config0++ = K;
				break;
			}
		}
	}
	statistics_state_t *State = xnew(statistics_state_t, MaxArgs, ml_value_t *);
	State->CalcConfigs = Config0;
	int *Config1 = Config0 + (NumCalcs + NumAccs + NumStats);
	for (int I = 0; I < NumCalcs; ++I) {
		calculator_t *Calc = Calcs[I];
		*Config0++ = Config1 - Configs;
		for (int J = 0; J < Calc->NumDepends; ++J) {
			calculator_t *Dep = Calc->Depends[J];
			for (int K = 0; K < NumCalcs; ++K) {
				if (Calcs[K] == Dep) {
					*Config1++ = K;
					break;
				}
			}
		}
	}
	State->AccConfigs = Config0;
	for (int I = 0; I < NumAccs; ++I) {
		accumulator_t *Acc = Accs[I];
		*Config0++ = Config1 - Configs;
		for (int J = 0; J < Acc->NumCalcs; ++J) {
			calculator_t *Calc = Acc->Calcs[J];
			for (int K = 0; K < NumCalcs; ++K) {
				if (Calcs[K] == Calc) {
					*Config1++ = K;
					break;
				}
			}
		}
	}
	State->StatConfigs = Config0;
	for (int I = 0; I < NumStats; ++I) {
		statistic_t *Stat = Stats[I];
		*Config0++ = Config1 - Configs;
		for (int J = 0; J < Stat->NumDepends; ++J) {
			ml_value_t *Dep = Stat->Depends[J];
			ml_type_t *Type = ml_typeof(Dep);
			if (Type == AccumulatorT) {
				accumulator_t *Acc = (accumulator_t *)Dep;
				for (int K = 0; K < NumAccs; ++K) {
					if (Accs[K] == Acc) {
						*Config1++ = K;
						break;
					}
				}
			} else if (Type == StatisticT) {
				statistic_t *Stat2 = (statistic_t *)Dep;
				for (int K = 0; K < NumStats; ++K) {
					if (Stats[K] == Stat2) {
						*Config1++ = NumAccs + K;
						break;
					}
				}
			}
		}
	}
	State->Count = Length;
	State->Stats = Stats;
	State->Accs = Accs;
	State->Calcs = Calcs;
	State->NumStats = NumStats;
	State->NumAccs = NumAccs;
	State->NumCalcs = NumCalcs;
	State->Configs = Configs;
	State->CalcValues = anew(ml_value_t *, NumCalcs + NumAccs + NumStats);
	State->AccValues = State->CalcValues + NumCalcs;
	State->StatValues = State->AccValues + NumAccs;
	return State;
}

ML_METHODX("()", StatisticsT, MLSequenceT) {
	// 1. Compute set of unique accumulators
	// 2. Initialize accumulators
	// 3. Compute set of unique calculators (including dependencies)
	// 4. Iterate over sequence, invoking calculators and accumulators
	// 5. Finalize accumulators
	// 6. Calculate statistics
	statistics_state_t *State = statistics_prepare(Args[0]);
	if (!State) ML_ERROR("ValueError", "No statistics requested");
	State->Base.Caller = Caller;
	State->Base.Context = Caller->Context;
	State->Base.run = (ml_state_fn)statistics_accumulator_init;
	State->Iter = Args[1];
	int Index = State->Index = State->NumAccs - 1;
	return ml_call(State, State->Accs[Index]->Init, 0, NULL);
}

static void statistic_call(ml_state_t *Caller, statistic_t *Stat, int Count, ml_value_t **Args) {
	for (int I = 0; I < Count; ++I) Args[I] = ml_deref(Args[I]);
	ML_CHECKX_ARG_COUNT(1);
	ML_CHECKX_ARG_TYPE(0, MLSequenceT);
	ml_value_t *Stats = ml_list();
	ml_list_put(Stats, (ml_value_t *)Stat);
	statistics_state_t *State = statistics_prepare(Stats);
	State->Base.Caller = Caller;
	State->Base.Context = Caller->Context;
	State->Base.run = (ml_state_fn)statistics_accumulator_init;
	State->Iter = ml_chained(Count, Args);
	State->Count = 0;
	int Index = State->Index = State->NumAccs - 1;
	return ml_call(State, State->Accs[Index]->Init, 0, NULL);
}

ML_FUNCTIONX(WFunc) {
	statistics_state_t *State = (statistics_state_t *)Caller;
	return ml_iter_key(Caller, State->Iter);
}

ML_FUNCTIONX(XFunc) {
	statistics_state_t *State = (statistics_state_t *)Caller;
	return ml_iter_value(Caller, State->Iter);
}

ML_METHOD_DECL(AddMethod, "+");
ML_METHOD_DECL(SubMethod, "-");
ML_METHOD_DECL(MulMethod, "*");
ML_METHOD_DECL(DivMethod, "/");
ML_METHOD_DECL(PowMethod, "^");
ML_METHOD_DECL(SqrtMethod, "math::sqrt");
ML_METHOD_DECL(LogMethod, "math::log");
ML_METHOD_DECL(ExpMethod, "math::exp");
ML_METHOD_DECL(MinMethod, "min");
ML_METHOD_DECL(MaxMethod, "max");
ML_METHOD_DECL(PutMethod, "put");
ML_METHOD_DECL(SortMethod, "sort");
ML_METHOD_DECL(DotMethod, ".");
ML_METHOD_DECL(MulMulMethod, "**");

ML_FUNCTION(CountInit) {
	return ml_integer(0);
}

ML_FUNCTION(CountUpdate) {
	ML_CHECK_ARG_COUNT(1);
	return ml_integer(ml_integer_value(Args[0]) + 1);
}

ML_FUNCTIONX(SumUpdate) {
	ML_CHECKX_ARG_COUNT(2);
	if (Args[0] == MLNil) ML_RETURN(Args[1]);
	return ml_call(Caller, AddMethod, 2, Args);
}

ML_MINI_FUNCTION(VarianceFunc, ("SumX2", "SumX", "Count"),
	"let MeanX2 := SumX2 / Count\n"
	"let MeanX := SumX / Count\n"
	"ret MeanX2 - (MeanX * MeanX)"
)

ML_FUNCTIONX(Inverse) {
	ML_CHECKX_ARG_COUNT(1);
	ml_value_t **Args2 = ml_alloc_args(2);
	Args2[0] = Args[0];
	Args2[1] = ml_integer(-1);
	return ml_call(Caller, PowMethod, 2, Args2);
}

static void percentile(ml_state_t *Caller, void *Data, int Count, ml_value_t **Args) {
	ML_CHECKX_ARG_COUNT(1);
	ML_CHECKX_ARG_TYPE(0, MLSliceT);
	double P = ml_real_value((ml_value_t *)Data);
	int N = ml_slice_length(Args[0]);
	double Exact = (N - 1) * P / 100.0;
	int A = floor(Exact);
	int B = ceil(Exact);
	if (A == B) ML_RETURN(ml_slice_get(Args[0], A + 1));
	ml_array_t *Weights = ml_array(ML_ARRAY_FORMAT_F64, 1, 2);
	double *WeightsP = (double *)ml_array_data(Weights);
	WeightsP[0] = B - Exact;
	WeightsP[1] = Exact - A;
	ml_array_t *Values = ml_array(ML_ARRAY_FORMAT_ANY, 1, 2);
	ml_value_t **ValuesP = (ml_value_t **)ml_array_data(Values);
	ValuesP[0] = ml_slice_get(Args[0], A + 1);
	ValuesP[1] = ml_slice_get(Args[0], B + 1);
	ml_value_t **Args2 = ml_alloc_args(2);
	Args2[0] = (ml_value_t *)Weights;
	Args2[1] = (ml_value_t *)Values;
	return ml_call(Caller, DotMethod, 2, Args2);
}

static accumulator_t *AllX = NULL;

ML_FUNCTION(Percentile) {
	ML_CHECK_ARG_COUNT(1);
	ML_CHECK_ARG_TYPE(0, MLRealT);
	return (ml_value_t *)statistic(ml_cfunctionx(Args[0], percentile), 1, AllX);
}

ML_FUNCTION(First) {
	ML_CHECK_ARG_COUNT(1);
	return ml_unpack(Args[0], 1);
}

ML_FUNCTION(Second) {
	ML_CHECK_ARG_COUNT(1);
	return ml_unpack(Args[0], 2);
}

ML_MINI_FUNCTION(CovarianceFunc, ("SumXY", "SumX", "Count"), "(Count * SumXY) - (SumX ** SumX)")

ML_MINI_FUNCTION(CorrelationFunc, ("SumXY", "SumX", "Count", "Covar"),
	"let Degree := SumX:shape[1]\n"
	"let SumX2 := SumXY:diag\n"
	"let StdDevX := math::sqrt((Count * SumX2) - (SumX * SumX))\n"
	"let StdDev := StdDevX ** StdDevX\n"
	"ret Covar / StdDev\n"
)

ML_LIBRARY_ENTRY0(math_stat) {
#include "stat_init.c"
	calculator_t *W = calculator((ml_value_t *)WFunc, 0);
	calculator_t *X = calculator((ml_value_t *)XFunc, 0);
	calculator_t *X2 = calculator(MulMethod, 2, X, X);
	calculator_t *X3 = calculator(MulMethod, 2, X, X2);
	calculator_t *X4 = calculator(MulMethod, 2, X, X3);
	accumulator_t *Count = accumulator((ml_value_t *)CountInit, (ml_value_t *)CountUpdate, 0);
	accumulator_t *SumX = accumulator(ml_integer(0), (ml_value_t *)SumUpdate, 1, X);
	accumulator_t *SumX2 = accumulator(ml_integer(0), (ml_value_t *)SumUpdate, 1, X2);
	accumulator_t *Min = accumulator(ml_integer(0), MinMethod, 1, X);
	accumulator_t *Max = accumulator(ml_integer(0), MaxMethod, 1, X);
	calculator_t *WX = calculator(MulMethod, 2, X, W);
	calculator_t *WX2 = calculator(MulMethod, 2, X, WX);
	calculator_t *WX3 = calculator(MulMethod, 2, X, WX2);
	calculator_t *WX4 = calculator(MulMethod, 2, X, WX3);
	accumulator_t *SumW = accumulator(ml_integer(0), (ml_value_t *)SumUpdate, 1, W);
	accumulator_t *SumWX = accumulator(ml_integer(0), (ml_value_t *)SumUpdate, 1, WX);
	accumulator_t *SumWX2 = accumulator(ml_integer(0), (ml_value_t *)SumUpdate, 1, WX2);
	calculator_t *IX = calculator((ml_value_t *)Inverse, 1, X);
	accumulator_t *SumIX = accumulator(ml_integer(0), (ml_value_t *)SumUpdate, 1, IX);
	calculator_t *LogX = calculator(LogMethod, 1, X);
	accumulator_t *SumLogX = accumulator(ml_integer(0), (ml_value_t *)SumUpdate, 1, LogX);
	AllX = accumulator((ml_value_t *)MLSliceT, PutMethod, 1, X);
	calculator_t *XY = calculator(MulMulMethod, 2, X, X);
	accumulator_t *SumXY = accumulator(ml_integer(0), (ml_value_t *)SumUpdate, 1, XY);
	statistic_t *Variance = statistic((ml_value_t *)VarianceFunc, 3, SumX2, SumX, Count);
	statistic_t *WeightedVariance = statistic((ml_value_t *)VarianceFunc, 3, SumWX2, SumWX, SumW);
	statistic_t *Covariance = statistic(CovarianceFunc, 3, SumXY, SumX, Count);
	Slot[0] = ml_module("stat",
		"mean", statistic(DivMethod, 2, SumX, Count),
		"variance", Variance,
		"stddev", statistic(SqrtMethod, 1, Variance),
		"min", statistic(ml_integer(1), 1, Min),
		"max", statistic(ml_integer(1), 1, Max),
		"weighted_mean", statistic(DivMethod, 2, SumWX, SumW),
		"weighted_variance", WeightedVariance,
		"weighted_stddev", statistic(SqrtMethod, 1, WeightedVariance),
		"harmonic_mean", statistic(MulMethod, 2, Count, SumIX),
		"geometric_mean", statistic(ml_chainedv(2, DivMethod, ExpMethod), 2, SumLogX, Count),
		"p", Percentile,
		"median", statistic(ml_cfunctionx(ml_real(50.0), percentile), 1, AllX),
		"covariance", Covariance,
		"correlation", statistic(CorrelationFunc, 4, SumXY, SumX, Count, Covariance),
		"meanxy", statistic(DivMethod, 2, SumXY, Count),
	NULL);
}
