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

static calculator_t X[1] = {{CalculatorT, MLNil, 0, 0}};
static calculator_t W[1] = {{CalculatorT, MLNil, 0, 0}};

struct accumulator_t {
	ml_type_t *Type;
	ml_value_t *Init, *Update, *Calc;
	int NumCalcs;
	calculator_t *Calcs[];
};

ML_TYPE(AccumulatorT, (), "accumulator");

struct statistic_t {
	ml_type_t *Type;
	ml_value_t *Calc;
	calculator_t **Calcs;
	int NumAccs, NumCalcs, ConfigSize;
	accumulator_t *Accs[];
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

static accumulator_t *accumulator(ml_value_t *Init, ml_value_t *Update, ml_value_t *Calc, int Count, ...) {
	accumulator_t *Acc = xnew(accumulator_t, Count, accumulator_t *);
	Acc->Type = AccumulatorT;
	Acc->Init = Init;
	Acc->Update = Update;
	Acc->Calc = Calc;
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
		calculator_t **Calcs2 = anew(calculator_t *, Calcs->Max+ 8);
		memcpy(Calcs2, Calcs->Calcs, Calcs->Max * sizeof(calculator_t *));
		Calcs->Calcs = Calcs2;
		Calcs->Max += 8;
	}
	Calcs->Calcs[Calcs->Num++] = Calc;
	Calcs->ConfigSize += 1 + Calc->NumDepends;
	for (int I = 0; I < Calc->NumDepends; ++I) calculators_add(Calcs, Calc->Depends[I]);
}

static statistic_t *statistic(ml_value_t *Fn, int Count, ...) {
	statistic_t *Stat = xnew(statistic_t, Count, accumulator_t *);
	Stat->Type = StatisticT;
	Stat->Calc = Fn;
	Stat->NumAccs = Count;
	calculators_t Calcs[1] = {{anew(calculator_t *, 4), 8, 0, 1}};
	va_list Args;
	va_start(Args, Count);
	for (int I = 0; I < Count; ++I) {
		accumulator_t *Acc = va_arg(Args, accumulator_t *);
		Stat->Accs[I] = Acc;
		Calcs->ConfigSize += 1 + Acc->NumCalcs;
		for (int J = 0; J < Acc->NumCalcs; ++J) calculators_add(Calcs, Acc->Calcs[J]);
	}
	va_end(Args);
	Stat->Calcs = Calcs->Calcs;
	Stat->NumCalcs = Calcs->Num;
	Stat->ConfigSize = Calcs->ConfigSize;
	return Stat;
}

ML_GENERIC_TYPE(StatisticsT, MLListT, StatisticT);

typedef struct {
	ml_state_t Base;
	statistic_t **Stats;
	calculator_t **Calcs;
	accumulator_t **Accs;
	ml_value_t **CalcValues, **AccValues, **StatValues;
	ml_value_t *Iter;
	int *StatConfigs, *AccConfigs, *CalcConfigs, *Configs;
	int NumStats, NumAccs, NumCalcs;
	int Index, Single;
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
		for (int I = 0; I < Stat->NumAccs; ++I) {
			State->Args[I] = State->AccValues[Config[I]];
		}
		return ml_call(State, Stat->Calc, Stat->NumAccs, State->Args);
	}
	if (State->Single) ML_CONTINUE(State->Base.Caller, State->StatValues[0]);
	ml_value_t *Result = ml_list();
	for (int I = 0; I < State->NumStats; ++I) ml_list_put(Result, State->StatValues[I]);
	ML_CONTINUE(State->Base.Caller, Result);
}

static void statistics_accumulator_calc(statistics_state_t *State, ml_value_t *Value) {
	if (ml_is_error(Value)) ML_CONTINUE(State->Base.Caller, Value);
	int Index = State->Index;
	State->AccValues[Index] = Value;
	if (Index) {
		State->Index = --Index;
		State->Args[0] = State->AccValues[Index];
		return ml_call(State, State->Accs[Index]->Calc, 1, State->Args);
	}
	Index = State->Index = State->NumStats - 1;
	statistic_t *Stat = State->Stats[Index];
	int *Config = State->Configs + State->StatConfigs[Index];
	for (int I = 0; I < Stat->NumAccs; ++I) {
		State->Args[I] = State->AccValues[Config[I]];
	}
	State->Base.run = (ml_state_fn)statistics_statistic;
	return ml_call(State, Stat->Calc, Stat->NumAccs, State->Args);
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
	if (Index > 2) {
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

static void statistics_value(statistics_state_t *State, ml_value_t *Value) {
	if (ml_is_error(Value)) ML_CONTINUE(State->Base.Caller, Value);
	State->CalcValues[0] = Value;
	int Index = State->Index = State->NumCalcs - 1;
	if (Index > 1) {
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

static void statistics_key(statistics_state_t *State, ml_value_t *Value) {
	if (ml_is_error(Value)) ML_CONTINUE(State->Base.Caller, Value);
	State->CalcValues[1] = Value;
	State->Base.run = (ml_state_fn)statistics_value;
	return ml_iter_value((ml_state_t *)State, State->Iter);
}

static void statistics_iterate(statistics_state_t *State, ml_value_t *Value) {
	if (ml_is_error(Value)) ML_CONTINUE(State->Base.Caller, Value);
	if (Value == MLNil) {
		int Index = State->Index = State->NumAccs - 1;
		State->Base.run = (ml_state_fn)statistics_accumulator_calc;
		State->Args[0] = State->AccValues[Index];
		return ml_call(State, State->Accs[Index]->Calc, 1, State->Args);
	}
	State->Base.run = (ml_state_fn)statistics_key;
	return ml_iter_key((ml_state_t *)State, State->Iter = Value);
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

static __attribute__ ((noinline)) statistics_state_t *statistics_prepare(ml_value_t *Arg) {
	int NumStats = ml_list_length(Arg);
	if (!NumStats) return NULL;
	statistic_t **Stats = anew(statistic_t *, NumStats), **StatSlot = Stats;
	int MaxAccs = 0, MaxCalcs = 2;
	ML_LIST_FOREACH(Arg, Iter) {
		statistic_t *Stat = (statistic_t *)Iter->Value;
		*StatSlot++ = Stat;
		MaxAccs += Stat->NumAccs;
		MaxCalcs += Stat->NumCalcs;
	}
	accumulator_t **Accs = anew(accumulator_t *, MaxAccs);
	calculator_t **Calcs = anew(calculator_t *, MaxCalcs);
	Calcs[0] = X;
	Calcs[1] = W;
	int NumAccs = 0, NumCalcs = 2, MaxArgs = 1, ConfigSize = 1;
	for (int I = 0; I < NumStats; ++I) {
		statistic_t *Stat = Stats[I];
		ConfigSize += 1 + Stat->NumAccs;
		if (MaxArgs < Stat->NumAccs) MaxArgs = Stat->NumAccs;
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
	qsort(Calcs + 2, NumCalcs - 2, sizeof(calculator_t *), calculators_compare);
	int *Configs = anew(int, ConfigSize), *Config0 = Configs;
	statistics_state_t *State = xnew(statistics_state_t, MaxArgs, ml_value_t *);
	State->CalcConfigs = Config0;
	int *Config1 = Configs + (NumCalcs + NumAccs + NumStats);
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
		for (int J = 0; J < Stat->NumAccs; ++J) {
			accumulator_t *Acc = Stat->Accs[J];
			for (int K = 0; K < NumAccs; ++K) {
				if (Accs[K] == Acc) {
					*Config1++ = K;
					break;
				}
			}
		}
	}
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

static __attribute__ ((noinline)) statistics_state_t *statistics_prepare1(statistic_t *Stat) {
	statistic_t **Stats = anew(statistic_t *, 1);
	int MaxAccs = 0, MaxCalcs = 2;
	Stats[0] = Stat;
	MaxAccs += Stat->NumAccs;
	MaxCalcs += Stat->NumCalcs;
	accumulator_t **Accs = anew(accumulator_t *, MaxAccs);
	calculator_t **Calcs = anew(calculator_t *, MaxCalcs);
	Calcs[0] = X;
	Calcs[1] = W;
	int NumAccs = 0, NumCalcs = 2, MaxArgs = 1, ConfigSize = 1;
	ConfigSize += 1 + Stat->NumAccs;
	if (MaxArgs < Stat->NumAccs) MaxArgs = Stat->NumAccs;
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
	qsort(Calcs + 2, NumCalcs - 2, sizeof(calculator_t *), calculators_compare);
	int *Configs = anew(int, ConfigSize), *Config0 = Configs;
	statistics_state_t *State = xnew(statistics_state_t, MaxArgs, ml_value_t *);
	State->CalcConfigs = Config0;
	int *Config1 = Configs + (NumCalcs + NumAccs + 1);
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
	*Config0++ = Config1 - Configs;
	for (int J = 0; J < Stat->NumAccs; ++J) {
		accumulator_t *Acc = Stat->Accs[J];
		for (int K = 0; K < NumAccs; ++K) {
			if (Accs[K] == Acc) {
				*Config1++ = K;
				break;
			}
		}
	}
	State->Stats = Stats;
	State->Accs = Accs;
	State->Calcs = Calcs;
	State->NumStats = 1;
	State->NumAccs = NumAccs;
	State->NumCalcs = NumCalcs;
	State->Configs = Configs;
	State->CalcValues = anew(ml_value_t *, NumCalcs + NumAccs + 1);
	State->AccValues = State->CalcValues + NumCalcs;
	State->StatValues = State->AccValues + NumAccs;
	return State;
}

static void statistic_call(ml_state_t *Caller, statistic_t *Stat, int Count, ml_value_t **Args) {
	for (int I = 0; I < Count; ++I) Args[I] = ml_deref(Args[I]);
	ML_CHECKX_ARG_COUNT(1);
	ML_CHECKX_ARG_TYPE(0, MLSequenceT);
	statistics_state_t *State = statistics_prepare1(Stat);
	State->Base.Caller = Caller;
	State->Base.Context = Caller->Context;
	State->Base.run = (ml_state_fn)statistics_accumulator_init;
	State->Iter = ml_chained(Count, Args);
	State->Single = 1;
	int Index = State->Index = State->NumAccs - 1;
	return ml_call(State, State->Accs[Index]->Init, 0, NULL);
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

typedef struct {
	ml_state_t Base;
	union { ml_value_t *SumX2; ml_value_t *MeanX2; };
	union { ml_value_t *SumX; ml_value_t *Mean2X; };
	ml_value_t *Count;
	ml_value_t *Args[2];
	int Sqrt;
} stddev_state_t;

static void stddev_variance(stddev_state_t *State, ml_value_t *Value) {
	if (ml_is_error(Value)) ML_CONTINUE(State->Base.Caller, Value);
	State->Args[0] = Value;
	return ml_call(State->Base.Caller, SqrtMethod, 1, State->Args);
}

static void stddev_meanx2(stddev_state_t *State, ml_value_t *Value) {
	if (ml_is_error(Value)) ML_CONTINUE(State->Base.Caller, Value);
	State->Base.run = (ml_state_fn)stddev_variance;
	State->Args[0] = Value;
	State->Args[1] = State->Mean2X;
	if (State->Sqrt) {
		return ml_call(State, SubMethod, 2, State->Args);
	} else {
		return ml_call(State->Base.Caller, SubMethod, 2, State->Args);
	}
}

static void stddev_mean2x(stddev_state_t *State, ml_value_t *Value) {
	if (ml_is_error(Value)) ML_CONTINUE(State->Base.Caller, Value);
	State->Mean2X = Value;
	State->Base.run = (ml_state_fn)stddev_meanx2;
	State->Args[0] = State->SumX2;
	State->Args[1] = State->Count;
	return ml_call(State, DivMethod, 2, State->Args);
}

static void stddev_meanx(stddev_state_t *State, ml_value_t *Value) {
	if (ml_is_error(Value)) ML_CONTINUE(State->Base.Caller, Value);
	State->Base.run = (ml_state_fn)stddev_mean2x;
	State->Args[0] = Value;
	State->Args[1] = Value;
	return ml_call(State, MulMethod, 2, State->Args);
}

ML_FUNCTIONX(StdDev) {
	ML_CHECKX_ARG_COUNT(3);
	stddev_state_t *State = new(stddev_state_t);
	State->Base.Caller = Caller;
	State->Base.Context = Caller->Context;
	State->Base.run = (ml_state_fn)stddev_meanx;
	State->Sqrt = 1;
	State->SumX2 = Args[0];
	State->SumX = Args[1];
	State->Count = Args[2];
	State->Args[0] = State->SumX;
	State->Args[1] = State->Count;
	return ml_call(State, DivMethod, 2, State->Args);
}

ML_FUNCTIONX(Variance) {
	ML_CHECKX_ARG_COUNT(3);
	stddev_state_t *State = new(stddev_state_t);
	State->Base.Caller = Caller;
	State->Base.Context = Caller->Context;
	State->Base.run = (ml_state_fn)stddev_meanx;
	State->SumX2 = Args[0];
	State->SumX = Args[1];
	State->Count = Args[2];
	State->Args[0] = State->SumX;
	State->Args[1] = State->Count;
	return ml_call(State, DivMethod, 2, State->Args);
}

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

ML_LIBRARY_ENTRY0(math_stat) {
#include "stat_init.c"
	calculator_t *X2 = calculator(MulMethod, 2, X, X);
	calculator_t *X3 = calculator(MulMethod, 2, X, X2);
	calculator_t *X4 = calculator(MulMethod, 2, X, X3);
	accumulator_t *Count = accumulator((ml_value_t *)CountInit, (ml_value_t *)CountUpdate, ml_integer(1), 0);
	accumulator_t *SumX = accumulator(ml_integer(0), (ml_value_t *)SumUpdate, ml_integer(1), 1, X);
	accumulator_t *SumX2 = accumulator(ml_integer(0), (ml_value_t *)SumUpdate, ml_integer(1), 1, X2);
	accumulator_t *Min = accumulator(ml_integer(0), MinMethod, ml_integer(1), 1, X);
	accumulator_t *Max = accumulator(ml_integer(0), MaxMethod, ml_integer(1), 1, X);
	calculator_t *WX = calculator(MulMethod, 2, X, W);
	calculator_t *WX2 = calculator(MulMethod, 2, X, WX);
	calculator_t *WX3 = calculator(MulMethod, 2, X, WX2);
	calculator_t *WX4 = calculator(MulMethod, 2, X, WX3);
	accumulator_t *SumW = accumulator(ml_integer(0), (ml_value_t *)SumUpdate, ml_integer(1), 1, W);
	accumulator_t *SumWX = accumulator(ml_integer(0), (ml_value_t *)SumUpdate, ml_integer(1), 1, WX);
	accumulator_t *SumWX2 = accumulator(ml_integer(0), (ml_value_t *)SumUpdate, ml_integer(1), 1, WX2);
	calculator_t *IX = calculator((ml_value_t *)Inverse, 1, X);
	accumulator_t *SumIX = accumulator(ml_integer(0), (ml_value_t *)SumUpdate, (ml_value_t *)Inverse, 1, IX);
	calculator_t *LogX = calculator(LogMethod, 1, X);
	accumulator_t *SumLogX = accumulator(ml_integer(0), (ml_value_t *)SumUpdate, ml_integer(1), 1, LogX);
	AllX = accumulator((ml_value_t *)MLSliceT, PutMethod, SortMethod, 1, X);
	Slot[0] = ml_module("stat",
		"mean", statistic(DivMethod, 2, SumX, Count),
		"stddev", statistic((ml_value_t *)StdDev, 3, SumX2, SumX, Count),
		"variance", statistic((ml_value_t *)Variance, 3, SumX2, SumX, Count),
		"min", statistic(ml_integer(1), 1, Min),
		"max", statistic(ml_integer(1), 1, Max),
		"weighted_mean", statistic(DivMethod, 2, SumWX, SumW),
		"weighted_stddev", statistic((ml_value_t *)StdDev, 3, SumWX2, SumWX, SumW),
		"weighted_variance", statistic((ml_value_t *)Variance, 3, SumWX2, SumWX, SumW),
		"harmonic_mean", statistic(MulMethod, 2, Count, SumIX),
		"geometric_mean", statistic(ml_chainedv(2, DivMethod, ExpMethod), 2, SumLogX, Count),
		"p", Percentile,
		"median", statistic(ml_cfunctionx(ml_real(50.0), percentile), 1, AllX),
	NULL);
}
