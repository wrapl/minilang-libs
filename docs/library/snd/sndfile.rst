.. include:: <isonum.txt>

.. include:: <isoamsa.txt>

.. include:: <isotech.txt>

snd/sndfile
===========

.. rst-class:: mini-api

:mini:`type sndfile < stream`
   *TBD*


:mini:`meth sndfile(Arg₁: stream, Arg₂: string, ...): sndfile`
   *TBD*


:mini:`meth sndfile(Arg₁: stream, Arg₂: string, Arg₃₁ is Value₁, ...): sndfile`
   *TBD*


:mini:`meth (Arg₁: sndfile):channels`
   *TBD*


:mini:`meth (Arg₁: sndfile):format`
   *TBD*


:mini:`meth (SndFile: sndfile):get(Name: sndfile::string): string`
   *TBD*


:mini:`meth (Arg₁: sndfile):rate`
   *TBD*


:mini:`meth (SndFile: sndfile):set(Name: sndfile::string, Value: string)`
   *TBD*


:mini:`meth (Arg₁: sndfile):strerror`
   *TBD*


:mini:`type sndfile::format < flags`
   * :mini:`::WAV`
   * :mini:`::AIFF`
   * :mini:`::AU`
   * :mini:`::RAW`
   * :mini:`::PAF`
   * :mini:`::SVX`
   * :mini:`::NIST`
   * :mini:`::VOC`
   * :mini:`::IRCAM`
   * :mini:`::W64`
   * :mini:`::MAT4`
   * :mini:`::MAT5`
   * :mini:`::PVF`
   * :mini:`::XI`
   * :mini:`::HTK`
   * :mini:`::SDS`
   * :mini:`::AVR`
   * :mini:`::WAVEX`
   * :mini:`::SD2`
   * :mini:`::FLAC`
   * :mini:`::CAF`
   * :mini:`::WVE`
   * :mini:`::Ogg`
   * :mini:`::MPC2K`
   * :mini:`::RF64`
   * :mini:`::PCM_S8`
   * :mini:`::PCM_16`
   * :mini:`::PCM_24`
   * :mini:`::PCM_32`
   * :mini:`::PCM_U8`
   * :mini:`::Float`
   * :mini:`::Double`
   * :mini:`::ULAW`
   * :mini:`::ALAW`
   * :mini:`::IMA_ADPCM`
   * :mini:`::MS_ADPCM`
   * :mini:`::GSM610`
   * :mini:`::VOX_ADPCM`
   * :mini:`::G721_32`
   * :mini:`::G723_24`
   * :mini:`::G723_40`
   * :mini:`::DWVW_12`
   * :mini:`::DWVW_16`
   * :mini:`::DWVW_24`
   * :mini:`::DWVW_N`
   * :mini:`::DPCM_8`
   * :mini:`::DPCM_16`
   * :mini:`::Vorbis`
   * :mini:`::SubMask`
   * :mini:`::TypeMask`
   * :mini:`::EndMask`


:mini:`type sndfile::string < enum`
   * :mini:`::Title`
   * :mini:`::Copyright`
   * :mini:`::Software`
   * :mini:`::Artist`
   * :mini:`::Comment`
   * :mini:`::Date`
   * :mini:`::Album`
   * :mini:`::License`
   * :mini:`::TrackNumber`
   * :mini:`::Genre`


