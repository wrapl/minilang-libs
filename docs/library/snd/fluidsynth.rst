.. include:: <isonum.txt>

.. include:: <isoamsa.txt>

.. include:: <isotech.txt>

snd/fluidsynth
==============

.. rst-class:: mini-api

:mini:`type audiodriver`
   *TBD*


:mini:`fun audiodriver(Settings: fluidsettings, Synth: fluidsynth): audiodriver`
   *TBD*


:mini:`fun event(): event`
   *TBD*


:mini:`type floatblock`
   *TBD*


:mini:`type fluidevent`
   *TBD*


:mini:`meth (Arg₁: fluidevent):all_notes_off(Arg₂: integer)`
   *TBD*


:mini:`meth (Arg₁: fluidevent):all_sounds_off(Arg₂: integer)`
   *TBD*


:mini:`meth (Arg₁: fluidevent):chorus(Arg₂: integer, Arg₃: integer)`
   *TBD*


:mini:`meth (Arg₁: fluidevent):data`
   *TBD*


:mini:`meth (Arg₁: fluidevent):dest(Arg₂: integer)`
   *TBD*


:mini:`meth (Arg₁: fluidevent):modulation(Arg₂: integer, Arg₃: integer)`
   *TBD*


:mini:`meth (Arg₁: fluidevent):note(Arg₂: integer, Arg₃: integer, Arg₄: integer, Arg₅: integer)`
   *TBD*


:mini:`meth (Arg₁: fluidevent):noteoff(Arg₂: integer, Arg₃: integer)`
   *TBD*


:mini:`meth (Arg₁: fluidevent):noteon(Arg₂: integer, Arg₃: integer, Arg₄: integer)`
   *TBD*


:mini:`meth (Arg₁: fluidevent):pan(Arg₂: integer, Arg₃: integer)`
   *TBD*


:mini:`meth (Arg₁: fluidevent):pitch_bend(Arg₂: integer, Arg₃: integer)`
   *TBD*


:mini:`meth (Arg₁: fluidevent):pitch_wheelsens(Arg₂: integer, Arg₃: integer)`
   *TBD*


:mini:`meth (Arg₁: fluidevent):pressure(Arg₂: integer, Arg₃: integer)`
   *TBD*


:mini:`meth (Arg₁: fluidevent):reverb(Arg₂: integer, Arg₃: integer)`
   *TBD*


:mini:`meth (Arg₁: fluidevent):source(Arg₂: integer)`
   *TBD*


:mini:`meth (Arg₁: fluidevent):sustain(Arg₂: integer, Arg₃: integer)`
   *TBD*


:mini:`meth (Arg₁: fluidevent):system_reset`
   *TBD*


:mini:`meth (Arg₁: fluidevent):timer`
   *TBD*


:mini:`meth (Arg₁: fluidevent):timer(Arg₂: any)`
   *TBD*


:mini:`meth (Arg₁: fluidevent):volume(Arg₂: integer, Arg₃: integer)`
   *TBD*


:mini:`type fluidsequencer`
   *TBD*


:mini:`meth (Arg₁: fluidsequencer):register(Arg₂: fluidsynth)`
   *TBD*


:mini:`meth (Arg₁: fluidsequencer):register(Arg₂: string)`
   *TBD*


:mini:`meth (Arg₁: fluidsequencer):register(Arg₂: string, Arg₃: function)`
   *TBD*


:mini:`meth (Arg₁: fluidsequencer):send_at(Arg₂: fluidevent, Arg₃: integer, Arg₄: boolean)`
   *TBD*


:mini:`meth (Arg₁: fluidsequencer):send_now(Arg₂: fluidevent)`
   *TBD*


:mini:`meth (Arg₁: fluidsequencer):tick`
   *TBD*


:mini:`meth (Arg₁: fluidsequencer):time_scale`
   *TBD*


:mini:`meth (Arg₁: fluidsequencer):time_scale(Arg₂: real)`
   *TBD*


:mini:`type fluidsettings`
   *TBD*


:mini:`fun fluidsynth(Arg₁: fluidsettings)`
   *TBD*


:mini:`meth (Arg₁: fluidsettings):get(Arg₂: string)`
   *TBD*


:mini:`meth (Arg₁: fluidsettings):set(Arg₂: string, Arg₃: any)`
   *TBD*


:mini:`type fluidsynth`
   *TBD*


:mini:`meth (Arg₁: fluidsynth):add_sfont(Arg₂: soundfont)`
   *TBD*


:mini:`meth (Arg₁: fluidsynth):bank_select(Arg₂: integer, Arg₃: integer)`
   *TBD*


:mini:`meth (Arg₁: fluidsynth):chorus(Arg₂: integer, Arg₃: real, Arg₄: real, Arg₅: real, Arg₆: integer)`
   *TBD*


:mini:`meth (Arg₁: fluidsynth):chorus_on(Arg₂: boolean)`
   *TBD*


:mini:`meth (Arg₁: fluidsynth):gain(Arg₂: real)`
   *TBD*


:mini:`meth (Arg₁: fluidsynth):get_sfont(Arg₂: integer)`
   *TBD*


:mini:`meth (Arg₁: fluidsynth):polyphony(Arg₂: integer)`
   *TBD*


:mini:`meth (Arg₁: fluidsynth):program_reset`
   *TBD*


:mini:`meth (Arg₁: fluidsynth):program_select(Arg₂: integer, Arg₃: integer, Arg₄: integer, Arg₅: integer)`
   *TBD*


:mini:`meth (Arg₁: fluidsynth):reverb(Arg₂: real, Arg₃: real, Arg₄: real, Arg₅: real)`
   *TBD*


:mini:`meth (Arg₁: fluidsynth):reverb_on(Arg₂: boolean)`
   *TBD*


:mini:`meth (Arg₁: fluidsynth):sample_rate(Arg₂: real)`
   *TBD*


:mini:`meth (Arg₁: fluidsynth):sfload(Arg₂: string, Arg₃: boolean)`
   *TBD*


:mini:`meth (Arg₁: fluidsynth):sfont_select(Arg₂: integer, Arg₃: integer)`
   *TBD*


:mini:`meth (Arg₁: fluidsynth):sfreload(Arg₂: string, Arg₃: boolean)`
   *TBD*


:mini:`meth (Arg₁: fluidsynth):sfunload(Arg₂: string, Arg₃: boolean)`
   *TBD*


:mini:`meth (Arg₁: fluidsynth):system_reset`
   *TBD*


:mini:`meth (Arg₁: fluidsynth):unset_program(Arg₂: integer)`
   *TBD*


:mini:`meth (Arg₁: fluidsynth):write_float(Arg₂: floatblock)`
   *TBD*


:mini:`meth (Arg₁: fluidsynth):write_float(Arg₂: integer, Arg₃: buffer, Arg₄: integer, Arg₅: integer, Arg₆: buffer, Arg₇: integer, Arg₈: integer)`
   *TBD*


:mini:`fun floatblock(Arg₁: integer, Arg₂: buffer, Arg₃: integer, Arg₄: integer, Arg₅: buffer, Arg₆: integer, Arg₇: integer)`
   *TBD*


:mini:`type preset`
   *TBD*


:mini:`meth (Arg₁: preset):bank`
   *TBD*


:mini:`meth (Arg₁: preset):name`
   *TBD*


:mini:`meth (Arg₁: preset):program`
   *TBD*


:mini:`fun sequencer(UseSystemTimer?: boolean): sequencer`
   *TBD*


:mini:`fun settings(): settings`
   *TBD*


:mini:`type soundfont`
   *TBD*


:mini:`meth (Arg₁: soundfont):presets`
   *TBD*


