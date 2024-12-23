#include <minilang/ml_library.h>
#include <minilang/ml_macros.h>
#include <minilang/ml_stream.h>
#include <minilang/ml_object.h>
#include <fluidsynth.h>

#undef ML_CATEGORY
#define ML_CATEGORY "snd/fluidsynth"

typedef struct {
	ml_type_t *Type;
	fluid_settings_t *Handle;
} settings_t;

extern ml_cfunction_t Settings[];

ML_TYPE(SettingsT, (), "fluidsynth::settings",
	.Constructor = (ml_value_t *)Settings
);

typedef struct {
	ml_type_t *Type;
	fluid_synth_t *Handle;
} synth_t;

extern ml_cfunction_t Synth[];

ML_TYPE(SynthT, (), "fluidsynth::synth",
	.Constructor = (ml_value_t *)Synth
);

typedef struct {
	ml_type_t *Type;
	fluid_sequencer_t *Handle;
} sequencer_t;

extern ml_cfunction_t Sequencer[];

ML_TYPE(SequencerT, (), "fluidsynth::sequencer",
	.Constructor = (ml_value_t *)Sequencer
);

typedef struct {
	ml_type_t *Type;
	fluid_event_t *Handle;
} event_t;

extern ml_cfunction_t Event[];

ML_TYPE(EventT, (), "fluidsynth::event",
	.Constructor = (ml_value_t *)Event
);

typedef struct {
	ml_type_t *Type;
	fluid_audio_driver_t *Handle;
} audio_driver_t;

extern ml_cfunction_t AudioDriver[];

ML_TYPE(AudioDriverT, (), "fluidsynth::driver",
	.Constructor = (ml_value_t *)AudioDriver
);

typedef struct {
	ml_type_t *Type;
	fluid_sfont_t *Handle;
} sound_font_t;

ML_TYPE(SoundFontT, (), "fluidsynth::soundfont");

typedef struct {
	ml_type_t *Type;
	int Len;
	void *Lout, *Rout;
	int Loff, Roff, Lincr, Rincr;
} float_block_t;

ML_TYPE(FloatBlockT, (), "fluidsynth::block");

static void settings_finalize(settings_t *Settings, void *Data) {
	delete_fluid_settings(Settings->Handle);
}

ML_FUNCTION(Settings) {
//>settings
	settings_t *Settings = new(settings_t);
	Settings->Type = SettingsT;
	Settings->Handle = new_fluid_settings();
	GC_register_finalizer(Settings->Handle, (void *)settings_finalize, NULL, NULL, NULL);
	return (ml_value_t *)Settings;
}

ML_METHOD("get", SettingsT, MLStringT) {
	fluid_settings_t *Handle = ((settings_t *)Args[0])->Handle;
	const char *Name = ml_string_value(Args[1]);
	switch (fluid_settings_get_type(Handle, Name)) {
	case FLUID_NO_TYPE: return ml_error("FluidSynthError", "Unknown setting %s", Name);
	case FLUID_NUM_TYPE: {
		double Value;
		if (fluid_settings_getnum(Handle, Name, &Value) == FLUID_OK) {
			return ml_real(Value);
		} else {
			return ml_error("FluidSynthError", "Error getting setting %s", Name);
		}
	}
	case FLUID_INT_TYPE: {
		int Value;
		if (fluid_settings_getint(Handle, Name, &Value) == FLUID_OK) {
			return ml_integer(Value);
		} else {
			return ml_error("FluidSynthError", "Error getting setting %s", Name);
		}
	}
	case FLUID_STR_TYPE: {
		char Value[256];
		if (fluid_settings_copystr(Handle, Name, Value, 256) == FLUID_OK) {
			return ml_string_copy(Value, -1);
		} else {
			return ml_error("FluidSynthError", "Error getting %s", Name);
		}
	}
	case FLUID_SET_TYPE: {
		return ml_error("FluidSynthError", "Error getting %s", Name);
	}
	}
	return ml_error("FluidSynthError", "Error getting %s", Name);
}

ML_METHOD("set", SettingsT, MLStringT, MLAnyT) {
	fluid_settings_t *Handle = ((settings_t *)Args[0])->Handle;
	const char *Name = ml_string_value(Args[1]);
	int Result;
	if (Args[2]->Type == MLStringT) {
		Result = fluid_settings_setstr(Handle, Name, ml_string_value(Args[2]));
	} else if (Args[2]->Type == MLRealT) {
		Result = fluid_settings_setnum(Handle, Name, ml_real_value(Args[2]));
	} else if (Args[2]->Type == MLIntegerT) {
		Result = fluid_settings_setint(Handle, Name, ml_integer_value(Args[2]));
	} else {
		Result = FLUID_FAILED;
	}
	if (Result == FLUID_OK) return Args[0];
	return ml_error("FluidSynthError", "Error setting %s", Name);
}

static void synth_finalize(synth_t *Synth, void *Data) {
	delete_fluid_synth(Synth->Handle);
}

ML_FUNCTION(Synth) {
	ML_CHECK_ARG_COUNT(1);
	ML_CHECK_ARG_TYPE(0, SettingsT);
	settings_t *Settings = (settings_t *)Args[0];
	synth_t *Synth = new(synth_t);
	Synth->Type = SynthT;
	Synth->Handle = new_fluid_synth(Settings->Handle);
	GC_register_finalizer(Synth->Handle, (void *)synth_finalize, NULL, NULL, NULL);
	return (ml_value_t *)Synth;
}

ML_METHOD("bank_select", SynthT, MLIntegerT, MLIntegerT) {
	fluid_synth_t *Handle = ((synth_t *)Args[0])->Handle;
	int Chan = ml_integer_value(Args[1]);
	unsigned int Bank = ml_integer_value(Args[2]);
	if (fluid_synth_bank_select(Handle, Chan, Bank) == FLUID_OK) return Args[0];
	return ml_error("FluidSynthError", "Error selecting bank");
}

ML_METHOD("sfont_select", SynthT, MLIntegerT, MLIntegerT) {
	fluid_synth_t *Handle = ((synth_t *)Args[0])->Handle;
	int Chan = ml_integer_value(Args[1]);
	unsigned int SFontID = ml_integer_value(Args[2]);
	if (fluid_synth_sfont_select(Handle, Chan, SFontID) == FLUID_OK) return Args[0];
	return ml_error("FluidSynthError", "Error selecting font");
}

ML_METHOD("program_select", SynthT, MLIntegerT, MLIntegerT, MLIntegerT, MLIntegerT) {
	fluid_synth_t *Handle = ((synth_t *)Args[0])->Handle;
	int Chan = ml_integer_value(Args[1]);
	unsigned int SFontID = ml_integer_value(Args[2]);
	unsigned int BankNum = ml_integer_value(Args[3]);
	unsigned int PresetNum = ml_integer_value(Args[4]);
	if (fluid_synth_program_select(Handle, Chan, SFontID, BankNum, PresetNum) == FLUID_OK) return Args[0];
	return ml_error("FluidSynthError", "Error selecting program");
}

ML_METHOD("unset_program", SynthT, MLIntegerT) {
	fluid_synth_t *Handle = ((synth_t *)Args[0])->Handle;
	int Chan = ml_integer_value(Args[1]);
	if (fluid_synth_unset_program(Handle, Chan) == FLUID_OK) return Args[0];
	return ml_error("FluidSynthError", "Error unsetting program");
}

ML_METHOD("program_reset", SynthT) {
	fluid_synth_t *Handle = ((synth_t *)Args[0])->Handle;
	if (fluid_synth_program_reset(Handle) == FLUID_OK) return Args[0];
	return ml_error("FluidSynthError", "Error resetting program");
}

ML_METHOD("system_reset", SynthT) {
	fluid_synth_t *Handle = ((synth_t *)Args[0])->Handle;
	if (fluid_synth_system_reset(Handle) == FLUID_OK) return Args[0];
	return ml_error("FluidSynthError", "Error resetting system");
}

ML_METHOD("sfload", SynthT, MLStringT, MLBooleanT) {
	fluid_synth_t *Handle = ((synth_t *)Args[0])->Handle;
	const char *FileName = ml_string_value(Args[1]);
	int ResetPresets = Args[2] == (ml_value_t *)MLTrue;
	int SFontID = fluid_synth_sfload(Handle, FileName, ResetPresets);
	if (SFontID == FLUID_FAILED) return ml_error("FluidSynthError", "Error loading font");
	return ml_integer(SFontID);
}

ML_METHOD("add_sfont", SynthT, SoundFontT) {
	fluid_synth_t *Synth = ((synth_t *)Args[0])->Handle;
	fluid_sfont_t *SFont = ((sound_font_t *)Args[1])->Handle;
	int SFontID = fluid_synth_add_sfont(Synth, SFont);
	if (SFontID == FLUID_FAILED) return ml_error("FluidSynthError", "Error adding font");
	return ml_integer(SFontID);
}

ML_METHOD("sfreload", SynthT, MLStringT, MLBooleanT) {
	fluid_synth_t *Handle = ((synth_t *)Args[0])->Handle;
	int SFontID = ml_integer_value(Args[1]);
	if (fluid_synth_sfreload(Handle, SFontID) == FLUID_OK) return Args[0];
	return ml_error("FluidSynthError", "Error reloading font");
}

ML_METHOD("sfunload", SynthT, MLStringT, MLBooleanT) {
	fluid_synth_t *Handle = ((synth_t *)Args[0])->Handle;
	int SFontID = ml_integer_value(Args[1]);
	int ResetPresets = Args[2] == (ml_value_t *)MLTrue;
	if (fluid_synth_sfunload(Handle, SFontID, ResetPresets) == FLUID_OK) return Args[0];
	return ml_error("FluidSynthError", "Error unloading font");
}

ML_METHOD("get_sfont", SynthT, MLIntegerT) {
	fluid_synth_t *Synth = ((synth_t *)Args[0])->Handle;
	int SFontID = ml_integer_value(Args[1]);
	sound_font_t *SFont = new(sound_font_t);
	SFont->Type = SoundFontT;
	SFont->Handle = fluid_synth_get_sfont_by_id(Synth, SFontID);
	return (ml_value_t *)SFont;
}

ML_METHOD("reverb", SynthT, MLRealT, MLRealT, MLRealT, MLRealT) {
	fluid_synth_set_reverb(
		((synth_t *)Args[0])->Handle,
		ml_real_value(Args[1]),
		ml_real_value(Args[2]),
		ml_real_value(Args[3]),
		ml_real_value(Args[4])
	);
	return Args[0];
}

ML_METHOD("reverb_on", SynthT, MLBooleanT) {
	fluid_synth_set_reverb_on(((synth_t *)Args[0])->Handle, Args[1] == (ml_value_t *)MLTrue);
	return Args[0];
}

ML_METHOD("chorus", SynthT, MLIntegerT, MLRealT, MLRealT, MLRealT, MLIntegerT) {
	fluid_synth_set_chorus(
		((synth_t *)Args[0])->Handle,
		ml_integer_value(Args[1]),
		ml_real_value(Args[2]),
		ml_real_value(Args[3]),
		ml_real_value(Args[4]),
		ml_integer_value(Args[5])
	);
	return Args[0];
}

ML_METHOD("chorus_on", SynthT, MLBooleanT) {
	fluid_synth_set_chorus_on(((synth_t *)Args[0])->Handle, Args[1] == (ml_value_t *)MLTrue);
	return Args[0];
}

ML_METHOD("sample_rate", SynthT, MLRealT) {
	fluid_synth_set_sample_rate(((synth_t *)Args[0])->Handle, ml_real_value(Args[1]));
	return Args[0];
}

ML_METHOD("gain", SynthT, MLRealT) {
	fluid_synth_set_gain(((synth_t *)Args[0])->Handle, ml_real_value(Args[1]));
	return Args[0];
}

ML_METHOD("polyphony", SynthT, MLIntegerT) {
	fluid_synth_set_polyphony(((synth_t *)Args[0])->Handle, ml_integer_value(Args[1]));
	return Args[0];
}

ML_METHOD("write_float", SynthT, MLIntegerT, MLBufferT, MLIntegerT, MLIntegerT, MLBufferT, MLIntegerT, MLIntegerT) {
	fluid_synth_t *Synth = ((synth_t *)Args[0])->Handle;
	int Len = ml_integer_value(Args[1]);
	void *Lout = ml_buffer_value(Args[2]);
	int Loff = ml_integer_value(Args[3]);
	int Lincr = ml_integer_value(Args[4]);
	void *Rout = ml_buffer_value(Args[5]);
	int Roff = ml_integer_value(Args[6]);
	int Rincr = ml_integer_value(Args[7]);
	if (fluid_synth_write_float(Synth, Len, Lout, Loff, Lincr, Rout, Roff, Rincr) == FLUID_OK) return Args[0];
	return ml_error("FluidSynthError", "Error writing floats");
}

ML_FUNCTION(FloatBlock) {
	ML_CHECK_ARG_COUNT(7);
	ML_CHECK_ARG_TYPE(0, MLIntegerT);
	ML_CHECK_ARG_TYPE(1, MLBufferT);
	ML_CHECK_ARG_TYPE(2, MLIntegerT);
	ML_CHECK_ARG_TYPE(3, MLIntegerT);
	ML_CHECK_ARG_TYPE(4, MLBufferT);
	ML_CHECK_ARG_TYPE(5, MLIntegerT);
	ML_CHECK_ARG_TYPE(6, MLIntegerT);
	float_block_t *Block = new(float_block_t);
	Block->Type = FloatBlockT;
	Block->Len = ml_integer_value(Args[0]);
	Block->Lout = ml_buffer_value(Args[1]);
	Block->Loff = ml_integer_value(Args[2]);
	Block->Lincr = ml_integer_value(Args[3]);
	Block->Rout = ml_buffer_value(Args[4]);
	Block->Roff = ml_integer_value(Args[5]);
	Block->Rincr = ml_integer_value(Args[6]);
	return (ml_value_t *)Block;
}

ML_METHOD("write_float", SynthT, FloatBlockT) {
	fluid_synth_t *Synth = ((synth_t *)Args[0])->Handle;
	float_block_t *Block = (float_block_t *)Args[1];
	if (fluid_synth_write_float(Synth, Block->Len, Block->Lout, Block->Loff, Block->Lincr, Block->Rout, Block->Roff, Block->Rincr) == FLUID_OK) return Args[0];
	return ml_error("FluidSynthError", "Error writing floats");
}

typedef struct {
	ml_type_t *Type;
	ml_value_t *Name, *Bank, *Program;
} preset_t;

ML_TYPE(PresetT, (), "fluidsynth::preset");

ML_METHOD("name", PresetT) {
	preset_t *Preset = (preset_t *)Args[0];
	return Preset->Name;
}

ML_METHOD("bank", PresetT) {
	preset_t *Preset = (preset_t *)Args[0];
	return Preset->Bank;
}

ML_METHOD("program", PresetT) {
	preset_t *Preset = (preset_t *)Args[0];
	return Preset->Program;
}

ML_METHOD("presets", SoundFontT) {
	fluid_sfont_t *SFont = ((sound_font_t *)Args[0])->Handle;
	ml_value_t *Result = ml_list();
	fluid_sfont_iteration_start(SFont);
	fluid_preset_t *Preset = NULL;
	while ((Preset = fluid_sfont_iteration_next(SFont))) {
		preset_t *Value = new(preset_t);
		Value->Type = PresetT;
		Value->Name = ml_string_copy(fluid_preset_get_name(Preset), -1);
		Value->Bank = ml_integer(fluid_preset_get_banknum(Preset));
		Value->Program = ml_integer(fluid_preset_get_num(Preset));
		ml_list_put(Result, (ml_value_t *)Value);
	}
	return Result;
}

static void sequencer_finalize(sequencer_t *Sequencer, void *Data) {
	delete_fluid_sequencer(Sequencer->Handle);
}

ML_FUNCTION(Sequencer) {
//<UseSystemTimer?:boolean
//>sequencer
	sequencer_t *Sequencer = new(sequencer_t);
	Sequencer->Type = SequencerT;
	if (Count > 0) {
		Sequencer->Handle = new_fluid_sequencer2(Args[0] == (ml_value_t *)MLTrue);
	} else {
		Sequencer->Handle = new_fluid_sequencer();
	}
	GC_register_finalizer((char *)Sequencer->Handle, (void *)sequencer_finalize, NULL, NULL, NULL);
	return (ml_value_t *)Sequencer;
}

ML_METHOD("tick", SequencerT) {
	fluid_sequencer_t *Sequencer = ((sequencer_t *)Args[0])->Handle;
	return ml_integer(fluid_sequencer_get_tick(Sequencer));
}

ML_METHOD("time_scale", SequencerT) {
	fluid_sequencer_t *Sequencer = ((sequencer_t *)Args[0])->Handle;
	return ml_real(fluid_sequencer_get_time_scale(Sequencer));
}

ML_METHOD("time_scale", SequencerT, MLRealT) {
	fluid_sequencer_t *Sequencer = ((sequencer_t *)Args[0])->Handle;
	double Scale = ml_real_value(Args[1]);
	fluid_sequencer_set_time_scale(Sequencer, Scale);
	return Args[0];
}

ML_METHOD("send_now", SequencerT, EventT) {
	fluid_sequencer_t *Sequencer = ((sequencer_t *)Args[0])->Handle;
	fluid_event_t *Event = ((event_t *)Args[1])->Handle;
	fluid_sequencer_send_now(Sequencer, Event);
	return Args[0];
}

ML_METHOD("send_at", SequencerT, EventT, MLIntegerT, MLBooleanT) {
	fluid_sequencer_t *Sequencer = ((sequencer_t *)Args[0])->Handle;
	fluid_event_t *Event = ((event_t *)Args[1])->Handle;
	unsigned int Time = ml_integer_value(Args[2]);
	int Absolute = Args[3] == (ml_value_t *)MLTrue;
	fluid_sequencer_send_at(Sequencer, Event, Time, Absolute);
	return Args[0];
}

ML_METHOD("register", SequencerT, SynthT) {
	fluid_sequencer_t *Sequencer = ((sequencer_t *)Args[0])->Handle;
	fluid_synth_t *Synth = ((synth_t *)Args[1])->Handle;
	short ClientID = fluid_sequencer_register_fluidsynth(Sequencer, Synth);
	if (ClientID == FLUID_FAILED) return ml_error("FluidSynthError", "Error registering synth");
	return ml_integer(ClientID);
}

ML_METHODX("register", SequencerT, MLStringT) {
	fluid_sequencer_t *Sequencer = ((sequencer_t *)Args[0])->Handle;
	const char *Name = ml_string_value(Args[1]);
	short ClientID;
	ClientID = fluid_sequencer_register_client(Sequencer, Name, 0, 0);
	if (ClientID == FLUID_FAILED) ML_ERROR("FluidSynthError", "Error registering sequencer");
	ML_RETURN(ml_integer(ClientID));
}

typedef struct {
	ml_state_t Base;
	ml_value_t *Function;
	ml_value_t *Args[3];
} event_callback_t;

static void event_callback_run(event_callback_t *Callback, ml_value_t *Value) {
}

static void event_callback(unsigned int Time, fluid_event_t *Event, fluid_sequencer_t *Sequencer, event_callback_t *Callback) {
	event_t *EventArg = new(event_t);
	EventArg->Type = EventT;
	EventArg->Handle = Event;
	sequencer_t *SequencerArg = new(sequencer_t);
	SequencerArg->Type = SequencerT;
	SequencerArg->Handle = Sequencer;
	Callback->Args[1] = ml_integer(Time);
	Callback->Args[2] = (ml_value_t *)EventArg;
	ml_call((ml_state_t *)Callback, Callback->Function, 3, Callback->Args);
}

ML_METHODX("register", SequencerT, MLStringT, MLFunctionT) {
	fluid_sequencer_t *Sequencer = ((sequencer_t *)Args[0])->Handle;
	const char *Name = ml_string_value(Args[1]);
	short ClientID;
	event_callback_t *Callback = new(event_callback_t);
	Callback->Base.Caller = Caller;
	Callback->Base.Context = Caller->Context;
	Callback->Base.run = (ml_state_fn)event_callback_run;
	Callback->Function = Args[2];
	Callback->Args[0] = Args[0];
	ClientID = fluid_sequencer_register_client(Sequencer, Name, (fluid_event_callback_t)event_callback, Args[2]);
	if (ClientID == FLUID_FAILED) ML_ERROR("FluidSynthError", "Error registering sequencer");
	ML_RETURN(ml_integer(ClientID));
}

static void event_finalize(event_t *Event, void *Data) {
	delete_fluid_event(Event->Handle);
}

ML_FUNCTION(Event) {
//>event
	event_t *Event = new(event_t);
	Event->Type = EventT;
	Event->Handle = new_fluid_event();
	GC_register_finalizer((char *)Event->Handle, (void *)event_finalize, NULL, NULL, NULL);
	return (ml_value_t *)Event;
}

ML_METHOD("data", EventT) {
	fluid_event_t *Event = ((event_t *)Args[0])->Handle;
	return (ml_value_t *)fluid_event_get_data(Event) ?: MLNil;
}

ML_METHOD("source", EventT, MLIntegerT) {
	fluid_event_t *Event = ((event_t *)Args[0])->Handle;
	short Src = ml_integer_value(Args[1]);
	fluid_event_set_source(Event, Src);
	return Args[0];
}

ML_METHOD("dest", EventT, MLIntegerT) {
	fluid_event_t *Event = ((event_t *)Args[0])->Handle;
	short Dest = ml_integer_value(Args[1]);
	fluid_event_set_dest(Event, Dest);
	return Args[0];
}

ML_METHOD("timer", EventT) {
	fluid_event_t *Event = ((event_t *)Args[0])->Handle;
	fluid_event_timer(Event, MLNil);
	return Args[0];
}

ML_METHOD("timer", EventT, MLAnyT) {
	fluid_event_t *Event = ((event_t *)Args[0])->Handle;
	fluid_event_timer(Event, Args[1]);
	return Args[0];
}

ML_METHOD("note", EventT, MLIntegerT, MLIntegerT, MLIntegerT, MLIntegerT) {
	fluid_event_t *Event = ((event_t *)Args[0])->Handle;
	int Channel = ml_integer_value(Args[1]);
	short Key = ml_integer_value(Args[2]);
	short Vel = ml_integer_value(Args[3]);
	unsigned int Duration = ml_integer_value(Args[4]);
	fluid_event_note(Event, Channel, Key, Vel, Duration);
	return Args[0];
}

ML_METHOD("noteon", EventT, MLIntegerT, MLIntegerT, MLIntegerT) {
	fluid_event_t *Event = ((event_t *)Args[0])->Handle;
	int Channel = ml_integer_value(Args[1]);
	short Key = ml_integer_value(Args[2]);
	short Vel = ml_integer_value(Args[3]);
	fluid_event_noteon(Event, Channel, Key, Vel);
	return Args[0];
}

ML_METHOD("noteoff", EventT, MLIntegerT, MLIntegerT) {
	fluid_event_t *Event = ((event_t *)Args[0])->Handle;
	int Channel = ml_integer_value(Args[1]);
	short Key = ml_integer_value(Args[2]);
	fluid_event_noteoff(Event, Channel, Key);
	return Args[0];
}

ML_METHOD("all_notes_off", EventT, MLIntegerT) {
	fluid_event_t *Event = ((event_t *)Args[0])->Handle;
	int Channel = ml_integer_value(Args[1]);
	fluid_event_all_notes_off(Event, Channel);
	return Args[0];
}

ML_METHOD("all_sounds_off", EventT, MLIntegerT) {
	fluid_event_t *Event = ((event_t *)Args[0])->Handle;
	int Channel = ml_integer_value(Args[1]);
	fluid_event_all_sounds_off(Event, Channel);
	return Args[0];
}

ML_METHOD("pitch_bend", EventT, MLIntegerT, MLIntegerT) {
	fluid_event_t *Event = ((event_t *)Args[0])->Handle;
	int Channel = ml_integer_value(Args[1]);
	int Pitch = ml_integer_value(Args[2]);
	fluid_event_pitch_bend(Event, Channel, Pitch);
	return Args[0];
}

ML_METHOD("pitch_wheelsens", EventT, MLIntegerT, MLIntegerT) {
	fluid_event_t *Event = ((event_t *)Args[0])->Handle;
	int Channel = ml_integer_value(Args[1]);
	short Val = ml_integer_value(Args[2]);
	fluid_event_pitch_wheelsens(Event, Channel, Val);
	return Args[0];
}

ML_METHOD("modulation", EventT, MLIntegerT, MLIntegerT) {
	fluid_event_t *Event = ((event_t *)Args[0])->Handle;
	int Channel = ml_integer_value(Args[1]);
	short Val = ml_integer_value(Args[2]);
	fluid_event_modulation(Event, Channel, Val);
	return Args[0];
}

ML_METHOD("sustain", EventT, MLIntegerT, MLIntegerT) {
	fluid_event_t *Event = ((event_t *)Args[0])->Handle;
	int Channel = ml_integer_value(Args[1]);
	short Val = ml_integer_value(Args[2]);
	fluid_event_sustain(Event, Channel, Val);
	return Args[0];
}

ML_METHOD("volume", EventT, MLIntegerT, MLIntegerT) {
	fluid_event_t *Event = ((event_t *)Args[0])->Handle;
	int Channel = ml_integer_value(Args[1]);
	short Val = ml_integer_value(Args[2]);
	fluid_event_volume(Event, Channel, Val);
	return Args[0];
}

ML_METHOD("pan", EventT, MLIntegerT, MLIntegerT) {
	fluid_event_t *Event = ((event_t *)Args[0])->Handle;
	int Channel = ml_integer_value(Args[1]);
	short Val = ml_integer_value(Args[2]);
	fluid_event_pan(Event, Channel, Val);
	return Args[0];
}

ML_METHOD("reverb", EventT, MLIntegerT, MLIntegerT) {
	fluid_event_t *Event = ((event_t *)Args[0])->Handle;
	int Channel = ml_integer_value(Args[1]);
	short Val = ml_integer_value(Args[2]);
	fluid_event_reverb_send(Event, Channel, Val);
	return Args[0];
}

ML_METHOD("chorus", EventT, MLIntegerT, MLIntegerT) {
	fluid_event_t *Event = ((event_t *)Args[0])->Handle;
	int Channel = ml_integer_value(Args[1]);
	short Val = ml_integer_value(Args[2]);
	fluid_event_chorus_send(Event, Channel, Val);
	return Args[0];
}

ML_METHOD("pressure", EventT, MLIntegerT, MLIntegerT) {
	fluid_event_t *Event = ((event_t *)Args[0])->Handle;
	int Channel = ml_integer_value(Args[1]);
	short Val = ml_integer_value(Args[2]);
	fluid_event_channel_pressure(Event, Channel, Val);
	return Args[0];
}

ML_METHOD("system_reset", EventT) {
	fluid_event_t *Event = ((event_t *)Args[0])->Handle;
	fluid_event_system_reset(Event);
	return Args[0];
}

static void audio_driver_finalize(audio_driver_t *AudioDriver, void *Data) {
	delete_fluid_audio_driver(AudioDriver->Handle);
}

ML_FUNCTION(AudioDriver) {
//<Settings
//<Synth
//>audiodriver
	ML_CHECK_ARG_COUNT(2);
	ML_CHECK_ARG_TYPE(0, SettingsT);
	ML_CHECK_ARG_TYPE(1, SynthT);
	settings_t *Settings = (settings_t *)Args[0];
	synth_t *Synth = (synth_t *)Args[1];
	audio_driver_t *AudioDriver = new(audio_driver_t);
	AudioDriver->Type = AudioDriverT;
	AudioDriver->Handle = new_fluid_audio_driver(Settings->Handle, Synth->Handle);
	GC_register_finalizer((char *)AudioDriver->Handle, (void *)audio_driver_finalize, NULL, NULL, NULL);
	return (ml_value_t *)AudioDriver;
}

ML_LIBRARY_ENTRY0(snd_fluidsynth) {
#include "fluidsynth_init.c"
	Slot[0] = ml_module("fluidsynth",
		"settings", SettingsT,
		"synth", SynthT,
		"sequencer", SequencerT,
		"event", EventT,
		"audiodriver", AudioDriverT,
		"soundfont", SoundFontT,
		"floatblock", FloatBlockT,
	NULL);
}
