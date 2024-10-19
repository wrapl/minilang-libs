.. include:: <isonum.txt>

.. include:: <isoamsa.txt>

.. include:: <isotech.txt>

snd/fluidsynth
==============

.. rst-class:: mini-api

:mini:`type audiodriver`
   *TBD*


:mini:`fun audiodriver(Settings: settings, Synth: synth): audiodriver`
   *TBD*


:mini:`type event`
   *TBD*


:mini:`fun event(): event`
   *TBD*


:mini:`meth (Arg₁: event):all_notes_off(Arg₂: integer)`
   *TBD*


:mini:`meth (Arg₁: event):all_sounds_off(Arg₂: integer)`
   *TBD*


:mini:`meth (Arg₁: event):chorus(Arg₂: integer, Arg₃: integer)`
   *TBD*


:mini:`meth (Arg₁: event):data`
   *TBD*


:mini:`meth (Arg₁: event):dest(Arg₂: integer)`
   *TBD*


:mini:`meth (Arg₁: event):modulation(Arg₂: integer, Arg₃: integer)`
   *TBD*


:mini:`meth (Arg₁: event):note(Arg₂: integer, Arg₃: integer, Arg₄: integer, Arg₅: integer)`
   *TBD*


:mini:`meth (Arg₁: event):noteoff(Arg₂: integer, Arg₃: integer)`
   *TBD*


:mini:`meth (Arg₁: event):noteon(Arg₂: integer, Arg₃: integer, Arg₄: integer)`
   *TBD*


:mini:`meth (Arg₁: event):pan(Arg₂: integer, Arg₃: integer)`
   *TBD*


:mini:`meth (Arg₁: event):pitch_bend(Arg₂: integer, Arg₃: integer)`
   *TBD*


:mini:`meth (Arg₁: event):pitch_wheelsens(Arg₂: integer, Arg₃: integer)`
   *TBD*


:mini:`meth (Arg₁: event):pressure(Arg₂: integer, Arg₃: integer)`
   *TBD*


:mini:`meth (Arg₁: event):reverb(Arg₂: integer, Arg₃: integer)`
   *TBD*


:mini:`meth (Arg₁: event):source(Arg₂: integer)`
   *TBD*


:mini:`meth (Arg₁: event):sustain(Arg₂: integer, Arg₃: integer)`
   *TBD*


:mini:`meth (Arg₁: event):system_reset`
   *TBD*


:mini:`meth (Arg₁: event):timer`
   *TBD*


:mini:`meth (Arg₁: event):timer(Arg₂: any)`
   *TBD*


:mini:`meth (Arg₁: event):volume(Arg₂: integer, Arg₃: integer)`
   *TBD*


:mini:`type floatblock`
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


:mini:`type sequencer`
   *TBD*


:mini:`fun sequencer(UseSystemTimer?: boolean): sequencer`
   *TBD*


:mini:`meth (Arg₁: sequencer):register(Arg₂: string)`
   *TBD*


:mini:`meth (Arg₁: sequencer):register(Arg₂: string, Arg₃: function)`
   *TBD*


:mini:`meth (Arg₁: sequencer):register(Arg₂: synth)`
   *TBD*


:mini:`meth (Arg₁: sequencer):send_at(Arg₂: event, Arg₃: integer, Arg₄: boolean)`
   *TBD*


:mini:`meth (Arg₁: sequencer):send_now(Arg₂: event)`
   *TBD*


:mini:`meth (Arg₁: sequencer):tick`
   *TBD*


:mini:`meth (Arg₁: sequencer):time_scale`
   *TBD*


:mini:`meth (Arg₁: sequencer):time_scale(Arg₂: real)`
   *TBD*


:mini:`type settings`
   *TBD*


:mini:`fun settings(): settings`
   *TBD*


:mini:`fun synth(Arg₁: settings)`
   *TBD*


:mini:`meth (Arg₁: settings):get(Arg₂: string)`
   *TBD*


:mini:`meth (Arg₁: settings):set(Arg₂: string, Arg₃: any)`
   *TBD*


:mini:`type soundfont`
   *TBD*


:mini:`meth (Arg₁: soundfont):presets`
   *TBD*


:mini:`type synth`
   *TBD*


:mini:`meth (Arg₁: synth):add_sfont(Arg₂: soundfont)`
   *TBD*


:mini:`meth (Arg₁: synth):bank_select(Arg₂: integer, Arg₃: integer)`
   *TBD*


:mini:`meth (Arg₁: synth):chorus(Arg₂: integer, Arg₃: real, Arg₄: real, Arg₅: real, Arg₆: integer)`
   *TBD*


:mini:`meth (Arg₁: synth):chorus_on(Arg₂: boolean)`
   *TBD*


:mini:`meth (Arg₁: synth):gain(Arg₂: real)`
   *TBD*


:mini:`meth (Arg₁: synth):get_sfont(Arg₂: integer)`
   *TBD*


:mini:`meth (Arg₁: synth):polyphony(Arg₂: integer)`
   *TBD*


:mini:`meth (Arg₁: synth):program_reset`
   *TBD*


:mini:`meth (Arg₁: synth):program_select(Arg₂: integer, Arg₃: integer, Arg₄: integer, Arg₅: integer)`
   *TBD*


:mini:`meth (Arg₁: synth):reverb(Arg₂: real, Arg₃: real, Arg₄: real, Arg₅: real)`
   *TBD*


:mini:`meth (Arg₁: synth):reverb_on(Arg₂: boolean)`
   *TBD*


:mini:`meth (Arg₁: synth):sample_rate(Arg₂: real)`
   *TBD*


:mini:`meth (Arg₁: synth):sfload(Arg₂: string, Arg₃: boolean)`
   *TBD*


:mini:`meth (Arg₁: synth):sfont_select(Arg₂: integer, Arg₃: integer)`
   *TBD*


:mini:`meth (Arg₁: synth):sfreload(Arg₂: string, Arg₃: boolean)`
   *TBD*


:mini:`meth (Arg₁: synth):sfunload(Arg₂: string, Arg₃: boolean)`
   *TBD*


:mini:`meth (Arg₁: synth):system_reset`
   *TBD*


:mini:`meth (Arg₁: synth):unset_program(Arg₂: integer)`
   *TBD*


:mini:`meth (Arg₁: synth):write_float(Arg₂: floatblock)`
   *TBD*


:mini:`meth (Arg₁: synth):write_float(Arg₂: integer, Arg₃: buffer, Arg₄: integer, Arg₅: integer, Arg₆: buffer, Arg₇: integer, Arg₈: integer)`
   *TBD*


