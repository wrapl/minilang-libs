#include <minilang/ml_library.h>
#include <minilang/ml_macros.h>
#include <minilang/ml_stream.h>
#include <minilang/ml_object.h>
#include <sox.h>

#undef ML_CATEGORY
#define ML_CATEGORY "snd/sox"

typedef struct {
	ml_type_t *Type;
	sox_signalinfo_t Value[1];
} signal_info_t;

extern ml_cfunction_t SignalInfo[1];

ML_TYPE(SignalInfoT, (), "sox::signalinfo",
	.Constructor = (ml_value_t *)SignalInfo
);

ML_FUNCTION(SignalInfo) {
	signal_info_t *SignalInfo = new(signal_info_t);
	SignalInfo->Type = SignalInfoT;
	if (Count > 0) SignalInfo->Value->rate = ml_real_value(Args[0]);
	if (Count > 1) SignalInfo->Value->channels = ml_integer_value(Args[1]);
	if (Count > 2) SignalInfo->Value->precision = ml_integer_value(Args[2]);
	if (Count > 3) SignalInfo->Value->precision = ml_integer_value(Args[3]);
	return (ml_value_t *)SignalInfo;
}

typedef struct {
	ml_type_t *Type;
	sox_format_t *Handle;
} format_t;

ML_TYPE(FormatT, (), "sox::format");

ML_METHOD_ANON(OpenRead, "sox::openread");

ML_METHOD(OpenRead, MLStringT) {
	format_t *Format = new(format_t);
	Format->Type = FormatT;
	const char *FileName = ml_string_value(Args[0]);
	// TODO: Support optional parameters
	sox_signalinfo_t *Signal = 0;
	sox_encodinginfo_t *Encoding = 0;
	char const *FileType = 0;
	Format->Handle = sox_open_read(FileName, Signal, Encoding, FileType);
	if (!Format->Handle) return ml_error("SoxError", "Error opening sox stream");
	return (ml_value_t *)Format;
}

ML_METHOD(OpenRead, MLAddressT) {
	format_t *Format = new(format_t);
	Format->Type = FormatT;
	const void *Buffer = ml_address_value(Args[0]);
	size_t Length = ml_address_length(Args[0]);
	// TODO: Support optional parameters
	sox_signalinfo_t *Signal = 0;
	sox_encodinginfo_t *Encoding = 0;
	char const *FileType = 0;
	Format->Handle = sox_open_mem_read((void *)Buffer, Length, Signal, Encoding, FileType);
	if (!Format->Handle) return ml_error("SoxError", "Error opening sox stream");
	return (ml_value_t *)Format;
}

ML_METHOD_ANON(OpenWrite, "sox::openwrite");

ML_METHOD(OpenWrite, MLStringT, SignalInfoT) {
	format_t *Format = new(format_t);
	Format->Type = FormatT;
	const char *FileName = ml_string_value(Args[0]);
	sox_signalinfo_t *Signal = ((signal_info_t *)Args[1])->Value;
	// TODO: Support optional parameters
	sox_encodinginfo_t *Encoding = 0;
	char const *FileType = 0;
	sox_oob_t *OOB = 0;
	void *OverwritePermitted = 0;
	Format->Handle = sox_open_write(FileName, Signal, Encoding, FileType, OOB, OverwritePermitted);
	if (!Format->Handle) return ml_error("SoxError", "Error opening sox stream");
	return (ml_value_t *)Format;
}

ML_METHOD(OpenWrite, MLBufferT, SignalInfoT) {
	format_t *Format = new(format_t);
	Format->Type = FormatT;
	void *Buffer = ml_buffer_value(Args[0]);
	size_t Length = ml_address_length(Args[0]);
	sox_signalinfo_t *Signal = ((signal_info_t *)Args[1])->Value;
	// TODO: Support optional parameters
	sox_encodinginfo_t *Encoding = 0;
	char const *FileType = 0;
	sox_oob_t *OOB = 0;
	Format->Handle = sox_open_mem_write(Buffer, Length, Signal, Encoding, FileType, OOB);
	if (!Format->Handle) return ml_error("SoxError", "Error opening sox stream");
	return (ml_value_t *)Format;
}

ML_METHOD("close", FormatT) {
	format_t *Format = (format_t *)Args[0];
	sox_close(Format->Handle);
	return Args[0];
}

typedef struct {
	ml_type_t *Type;
	sox_effects_chain_t *Handle;
} effects_chain_t;

extern ml_cfunction_t Sox[1];

ML_TYPE(SoxT, (), "sox",
	.Constructor = (ml_value_t *)Sox
);

ML_FUNCTION(Sox) {
	sox_encodinginfo_t *InEncoding = 0;
	sox_encodinginfo_t *OutEncoding = 0;
	effects_chain_t *Chain = new(effects_chain_t);
	Chain->Type = SoxT;
	Chain->Handle = sox_create_effects_chain(InEncoding, OutEncoding);
	return (ml_value_t *)Chain;
}

static int flow_callback(sox_bool AllDone, effects_chain_t *Sox) {
	return 0;
}

ML_METHOD("flow", SoxT) {
	effects_chain_t *Chain = (effects_chain_t *)Args[0];
	if (sox_flow_effects(Chain->Handle, (void *)flow_callback, Chain) == SOX_SUCCESS) {
		return Args[0];
	} else {
		return ml_error("SoxError", "Error running sox flow");
	}
}

typedef struct {
	ml_type_t *Type;
	sox_effect_t *Handle;
} effect_t;

ML_TYPE(EffectT, (), "sox::effect");

ML_METHOD(Effect, MLStringT) {
	effect_t *Effect = new(effect_t);
	Effect->Type = EffectT;
	Effect->Handle = sox_create_effect(sox_find_effect(ml_string_value(Args[0])));
	return (ml_value_t *)Effect;
}

typedef struct {
	ml_state_t Base;
	ml_value_t *Result;
	sox_effect_t *Handle;
	ml_value_t *GetOpts;
	ml_value_t *Start;
	ml_value_t *Flow;
	ml_value_t *Drain;
	ml_value_t *Stop;
	ml_value_t *Kill;
	sox_effect_handler_t Handler[1];
} ml_effect_t;

static void ml_effect_run(ml_effect_t *Effect, ml_value_t *Value) {
	Effect->Result = Value;
}

static int ml_effect_getopts(sox_effect_t *E, int Argc, char *Argv[]) {
	ml_effect_t *Effect = E->priv;
	ml_value_t *Opts = ml_list();
	for (int I = 0; I < Argc; ++I) ml_list_put(Opts, ml_string_copy(Argv[I], -1));
	ml_value_t **Args = ml_alloc_args(2);
	Args[0] = (ml_value_t *)Effect;
	Args[1] = Opts;
	Effect->Result = NULL;
	ml_call((ml_state_t *)Effect, Effect->GetOpts, 2, Args);
	ml_scheduler_t *Scheduler = ml_context_get_static(Effect->Base.Context, ML_SCHEDULER_INDEX);
	while (!Effect->Result) Scheduler->run(Scheduler);
	if (ml_is_error(Effect->Result)) return SOX_EINVAL;
	return SOX_SUCCESS;
}

static int ml_effect_start(sox_effect_t *E) {
	ml_effect_t *Effect = E->priv;
	ml_value_t **Args = ml_alloc_args(1);
	Args[0] = (ml_value_t *)Effect;
	Effect->Result = NULL;
	ml_call((ml_state_t *)Effect, Effect->Start, 1, Args);
	ml_scheduler_t *Scheduler = ml_context_get_static(Effect->Base.Context, ML_SCHEDULER_INDEX);
	while (!Effect->Result) Scheduler->run(Scheduler);
	if (ml_is_error(Effect->Result)) return SOX_EINVAL;
	return SOX_SUCCESS;
}

static int ml_effect_flow(sox_effect_t *E, const sox_sample_t *IBuf, sox_sample_t *OBuf, size_t *ISamp, size_t *OSamp) {
	ml_effect_t *Effect = E->priv;
	ml_value_t **Args = ml_alloc_args(3);
	Args[0] = (ml_value_t *)Effect;
	Args[1] = ml_address((void *)IBuf, ISamp[0] * sizeof(sox_sample_t));
	Args[2] = ml_buffer((void *)OBuf, OSamp[0] * sizeof(sox_sample_t));
	Effect->Result = NULL;
	ml_call((ml_state_t *)Effect, Effect->Flow, 5, Args);
	ml_scheduler_t *Scheduler = ml_context_get_static(Effect->Base.Context, ML_SCHEDULER_INDEX);
	while (!Effect->Result) Scheduler->run(Scheduler);
	if (ml_is_error(Effect->Result)) return SOX_EINVAL;
	if (!ml_is(Effect->Result, MLTupleT)) return SOX_EINVAL;
	ISamp[0] = ml_integer_value(ml_tuple_get(Effect->Result, 1));
	OSamp[0] = ml_integer_value(ml_tuple_get(Effect->Result, 2));
	return SOX_SUCCESS;
}

static int ml_effect_drain(sox_effect_t *E, sox_sample_t *OBuf, size_t *OSamp) {
	ml_effect_t *Effect = E->priv;
	ml_value_t **Args = ml_alloc_args(2);
	Args[0] = (ml_value_t *)Effect;
	Args[1] = ml_buffer((void *)OBuf, OSamp[0] * sizeof(sox_sample_t));
	Effect->Result = NULL;
	ml_call((ml_state_t *)Effect, Effect->Drain, 2, Args);
	ml_scheduler_t *Scheduler = ml_context_get_static(Effect->Base.Context, ML_SCHEDULER_INDEX);
	while (!Effect->Result) Scheduler->run(Scheduler);
	if (ml_is_error(Effect->Result)) return SOX_EINVAL;
	OSamp[0] = ml_integer_value(Effect->Result);
	return SOX_SUCCESS;
}

static int ml_effect_stop(sox_effect_t *E) {
	ml_effect_t *Effect = E->priv;
	ml_value_t **Args = ml_alloc_args(1);
	Args[0] = (ml_value_t *)Effect;
	Effect->Result = NULL;
	ml_call((ml_state_t *)Effect, Effect->Stop, 1, Args);
	ml_scheduler_t *Scheduler = ml_context_get_static(Effect->Base.Context, ML_SCHEDULER_INDEX);
	while (!Effect->Result) Scheduler->run(Scheduler);
	if (ml_is_error(Effect->Result)) return SOX_EINVAL;
	return SOX_SUCCESS;
}

static int ml_effect_kill(sox_effect_t *E) {
	ml_effect_t *Effect = E->priv;
	ml_value_t **Args = ml_alloc_args(1);
	Args[0] = (ml_value_t *)Effect;
	Effect->Result = NULL;
	ml_call((ml_state_t *)Effect, Effect->Kill, 1, Args);
	ml_scheduler_t *Scheduler = ml_context_get_static(Effect->Base.Context, ML_SCHEDULER_INDEX);
	while (!Effect->Result) Scheduler->run(Scheduler);
	if (ml_is_error(Effect->Result)) return SOX_EINVAL;
	return SOX_SUCCESS;
}

extern ml_cfunctionx_t Effect[1];

ML_TYPE(MLEffectT, (EffectT), "sox::effect");

ML_FLAGS2(EffectFlagT, "sox::effect::flag",
	"Chan", SOX_EFF_CHAN,
	"Rate", SOX_EFF_RATE,
	"Prec", SOX_EFF_PREC,
	"Length", SOX_EFF_LENGTH,
	"MChan", SOX_EFF_MCHAN,
	"Null", SOX_EFF_NULL,
	"Deprecated", SOX_EFF_DEPRECATED,
	"Gain", SOX_EFF_GAIN,
	"Modify", SOX_EFF_MODIFY,
	"Alpha", SOX_EFF_ALPHA,
	"Internal", SOX_EFF_INTERNAL
);

ML_METHODVX(Effect, MLNamesT) {
	ml_effect_t *Effect = new(ml_effect_t);
	Effect->Base.Type = MLEffectT;
	Effect->Base.Context = Caller->Context;
	Effect->Base.run = (ml_state_fn)ml_effect_run;
	int I = 0;
	ML_NAMES_FOREACH(Args[0], Iter) {
		const char *Option = ml_string_value(Iter->Value);
		ml_value_t *Value = Args[++I];
		if (!strcmp(Option, "name")) {
			ML_CHECKX_ARG_TYPE(I, MLStringT);
			Effect->Handler->name = ml_string_value(Value);
		} else if (!strcmp(Option, "usage")) {
			ML_CHECKX_ARG_TYPE(I, MLStringT);
			Effect->Handler->usage = ml_string_value(Value);
		} else if (!strcmp(Option, "flags")) {
			ML_CHECKX_ARG_TYPE(I, EffectFlagT);
			Effect->Handler->flags = ml_flags_value_value(Value);
		} else if (!strcmp(Option, "getopts")) {
			Effect->Handler->getopts = ml_effect_getopts;
			Effect->GetOpts = Value;
		} else if (!strcmp(Option, "start")) {
			Effect->Handler->start = ml_effect_start;
			Effect->Start = Value;
		} else if (!strcmp(Option, "flow")) {
			Effect->Handler->flow = ml_effect_flow;
			Effect->Flow = Value;
		} else if (!strcmp(Option, "drain")) {
			Effect->Handler->drain = ml_effect_drain;
			Effect->Drain = Value;
		} else if (!strcmp(Option, "stop")) {
			Effect->Handler->stop = ml_effect_stop;
			Effect->Stop = Value;
		} else if (!strcmp(Option, "kill")) {
			Effect->Handler->kill = ml_effect_kill;
			Effect->Kill = Value;
		}
	}
	sox_effect_t *Handle = Effect->Handle = sox_create_effect(Effect->Handler);
	Handle->priv = Effect;
	ML_RETURN(Effect);
}

ML_METHOD("add", SoxT, EffectT) {
	effects_chain_t *Chain = (effects_chain_t *)Args[0];
	effect_t *Effect = (effect_t *)Args[1];
	sox_add_effect(Chain->Handle, Effect->Handle, 0, 0);
	return Args[0];
}

ML_LIBRARY_ENTRY0(snd_sox) {
	sox_init();
	sox_format_init();
#include "sox_init.c"
	stringmap_insert(SoxT->Exports, "effect", EffectT);
	Slot[0] = (ml_value_t *)SoxT;
}
