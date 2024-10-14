#include <minilang/ml_library.h>
#include <minilang/ml_macros.h>
#include <minilang/ml_stream.h>
#include <minilang/ml_object.h>
#include <sndfile.h>

typedef struct {
	ml_state_t Base;
	SNDFILE *Handle;
	ml_value_t *Stream;
	ml_value_t *SampleRate, *Channels, *Format;
	ml_value_t *Result;
	void (*read)(ml_state_t *, ml_value_t *, void *, int );
	void (*write)(ml_state_t *, ml_value_t *, const void *, int );
	void (*seek)(ml_state_t *, ml_value_t *, int64_t Offset, int Mode);
	void (*tell)(ml_state_t *, ml_value_t *);
} sndfile_t;

ML_TYPE(SndFileT, (MLStreamT), "sndfile");

static sf_count_t sndfile_seek(sf_count_t Offset, int Whence, sndfile_t *SndFile) {
	SndFile->Result = NULL;
	SndFile->seek((ml_state_t *)SndFile, SndFile->Stream, Offset, Whence);
	ml_scheduler_t *Scheduler = ml_context_get_static(SndFile->Base.Context, ML_SCHEDULER_INDEX);
	while (!SndFile->Result) Scheduler->run(Scheduler);
	return ml_integer_value(SndFile->Result);
}

static sf_count_t sndfile_read(void *Buffer, sf_count_t Count, sndfile_t *SndFile) {
	SndFile->Result = NULL;
	SndFile->read((ml_state_t *)SndFile, SndFile->Stream, Buffer, Count);
	ml_scheduler_t *Scheduler = ml_context_get_static(SndFile->Base.Context, ML_SCHEDULER_INDEX);
	while (!SndFile->Result) Scheduler->run(Scheduler);
	return ml_integer_value(SndFile->Result);
}

static sf_count_t sndfile_write(void *Buffer, sf_count_t Count, sndfile_t *SndFile) {
	SndFile->Result = NULL;
	SndFile->write((ml_state_t *)SndFile, SndFile->Stream, Buffer, Count);
	ml_scheduler_t *Scheduler = ml_context_get_static(SndFile->Base.Context, ML_SCHEDULER_INDEX);
	while (!SndFile->Result) Scheduler->run(Scheduler);
	return ml_integer_value(SndFile->Result);
}

static sf_count_t sndfile_tell(sndfile_t *SndFile) {
	SndFile->Result = NULL;
	SndFile->tell((ml_state_t *)SndFile, SndFile->Stream);
	ml_scheduler_t *Scheduler = ml_context_get_static(SndFile->Base.Context, ML_SCHEDULER_INDEX);
	while (!SndFile->Result) Scheduler->run(Scheduler);
	return ml_integer_value(SndFile->Result);
}

static sf_count_t sndfile_get_filelen(sndfile_t *SndFile) {
	sf_count_t Current = sndfile_tell(SndFile);
	sf_count_t FileLen = sndfile_seek(0, SEEK_END, SndFile);
	sndfile_seek(Current, SEEK_SET, SndFile);
	return FileLen;
}

ML_FLAGS2(SndFileFormatT, "sndfile::format",
	"WAV", SF_FORMAT_WAV,
	"AIFF", SF_FORMAT_AIFF,
	"AU", SF_FORMAT_AU,
	"RAW", SF_FORMAT_RAW,
	"PAF", SF_FORMAT_PAF,
	"SVX", SF_FORMAT_SVX,
	"NIST", SF_FORMAT_NIST,
	"VOC", SF_FORMAT_VOC,
	"IRCAM", SF_FORMAT_IRCAM,
	"W64", SF_FORMAT_W64,
	"MAT4", SF_FORMAT_MAT4,
	"MAT5", SF_FORMAT_MAT5,
	"PVF", SF_FORMAT_PVF,
	"XI", SF_FORMAT_XI,
	"HTK", SF_FORMAT_HTK,
	"SDS", SF_FORMAT_SDS,
	"AVR", SF_FORMAT_AVR,
	"WAVEX", SF_FORMAT_WAVEX,
	"SD2", SF_FORMAT_SD2,
	"FLAC", SF_FORMAT_FLAC,
	"CAF", SF_FORMAT_CAF,
	"WVE", SF_FORMAT_WVE,
	"Ogg", SF_FORMAT_OGG,
	"MPC2K", SF_FORMAT_MPC2K,
	"RF64", SF_FORMAT_RF64,
	"PCM_S8", SF_FORMAT_PCM_S8,
	"PCM_16", SF_FORMAT_PCM_16,
	"PCM_24", SF_FORMAT_PCM_24,
	"PCM_32", SF_FORMAT_PCM_32,
	"PCM_U8", SF_FORMAT_PCM_U8,
	"Float", SF_FORMAT_FLOAT,
	"Double", SF_FORMAT_DOUBLE,
	"ULAW", SF_FORMAT_ULAW,
	"ALAW", SF_FORMAT_ALAW,
	"IMA_ADPCM", SF_FORMAT_IMA_ADPCM,
	"MS_ADPCM", SF_FORMAT_MS_ADPCM,
	"GSM610", SF_FORMAT_GSM610,
	"VOX_ADPCM", SF_FORMAT_VOX_ADPCM,
	"G721_32", SF_FORMAT_G721_32,
	"G723_24", SF_FORMAT_G723_24,
	"G723_40", SF_FORMAT_G723_40,
	"DWVW_12", SF_FORMAT_DWVW_12,
	"DWVW_16", SF_FORMAT_DWVW_16,
	"DWVW_24", SF_FORMAT_DWVW_24,
	"DWVW_N", SF_FORMAT_DWVW_N,
	"DPCM_8", SF_FORMAT_DPCM_8,
	"DPCM_16", SF_FORMAT_DPCM_16,
	"Vorbis", SF_FORMAT_VORBIS,
	"SubMask", SF_FORMAT_SUBMASK,
	"TypeMask", SF_FORMAT_TYPEMASK,
	"EndMask", SF_FORMAT_ENDMASK
);

static void sndfile_run(sndfile_t *SndFile, ml_value_t *Value) {
	SndFile->Result = Value;
}

ML_METHODV(SndFileT, MLStreamT, MLStringT, MLNamesT) {
	ML_NAMES_CHECK_ARG_COUNT(2);
	ml_value_t *Stream = Args[0];
	sndfile_t *SndFile = new(sndfile_t);
	SndFile->Base.Type = SndFileT;
	SndFile->Stream = Stream;
	SndFile->read = ml_typed_fn_get(Stream->Type, ml_stream_read) ?: ml_stream_read_method;
	SndFile->write = ml_typed_fn_get(Stream->Type, ml_stream_write) ?: ml_stream_write_method;
	SndFile->seek = ml_typed_fn_get(Stream->Type, ml_stream_seek) ?: ml_stream_seek_method;
	SndFile->tell = ml_typed_fn_get(Stream->Type, ml_stream_tell) ?: ml_stream_tell_method;
	SF_VIRTUAL_IO VirtualIO = {
		(void *)sndfile_get_filelen,
		(void *)sndfile_seek,
		(void *)sndfile_read,
		(void *)sndfile_write,
		(void *)sndfile_tell
	};
	int Mode = 0;
	for (const char *M = ml_string_value(Args[1]); *M; ++M) {
		if (*M == 'r') Mode |= SFM_READ;
		if (*M == 'w') Mode |= SFM_WRITE;
	}
	SF_INFO Info = {0,};
	int I = 2;
	ML_NAMES_FOREACH(Args[2], Iter) {
		++I;
		const char *Name = ml_string_value(Iter->Value);
		if (!strcmp(Name, "rate")) {
			Info.samplerate = ml_integer_value(Args[I]);
		} else if (!strcmp(Name, "channels")) {
			Info.channels = ml_integer_value(Args[I]);
		} else if (!strcmp(Name, "format")) {
			ML_CHECK_ARG_TYPE(I, SndFileFormatT);
			Info.format = ml_flags_value_value(Args[I]);
		} else if (!strcmp(Name, "seekable")) {
			Info.seekable = ml_boolean_value(Args[I]);
		}
	}
	if ((SndFile->Handle = sf_open_virtual(&VirtualIO, Mode, &Info, SndFile))) {
		SndFile->SampleRate = ml_integer(Info.samplerate);
		SndFile->Channels = ml_integer(Info.channels);
		SndFile->Format = ml_flags_value(SndFileFormatT, Info.format);
		return (ml_value_t *)SndFile;
	} else {
		return ml_error("SndFileError", "%s", sf_strerror(0));
	};
}

ML_LIBRARY_ENTRY0(snd_sndfile) {
#include "sndfile_init.c"
	Slot[0] = (ml_value_t *)SndFileT;
}
