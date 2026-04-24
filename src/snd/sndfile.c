#include <minilang/ml_library.h>
#include <minilang/ml_macros.h>
#include <minilang/ml_stream.h>
#include <minilang/ml_object.h>
#include <minilang/ml_array.h>
#include <sndfile.h>

#undef ML_CATEGORY
#define ML_CATEGORY "snd/sndfile"

typedef struct {
	ml_state_t Base;
	SNDFILE *Handle;
	ml_value_t *Stream;
	ml_value_t *Result;
	void (*read)(ml_state_t *, ml_value_t *, void *, int );
	void (*write)(ml_state_t *, ml_value_t *, const void *, int );
	void (*seek)(ml_state_t *, ml_value_t *, int64_t Offset, int Mode);
	void (*tell)(ml_state_t *, ml_value_t *);
	int SampleRate, Channels, Format;
} sndfile_t;

ML_TYPE(SndFileT, (), "sndfile");

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
//@sndfile::format
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

ML_METHODVX(SndFileT, MLStreamT, MLStringT, MLNamesT) {
//>sndfile
	ML_NAMES_CHECKX_ARG_COUNT(2);
	ml_value_t *Stream = Args[0];
	sndfile_t *SndFile = new(sndfile_t);
	SndFile->Base.Type = SndFileT;
	SndFile->Base.Caller = Caller;
	SndFile->Base.Context = Caller->Context;
	SndFile->Base.run = (ml_state_fn)sndfile_run;
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
		if (!strcmp(Name, "sample_rate")) {
			Info.samplerate = ml_integer_value(Args[I]);
		} else if (!strcmp(Name, "channels")) {
			Info.channels = ml_integer_value(Args[I]);
		} else if (!strcmp(Name, "format")) {
			ML_CHECKX_ARG_TYPE(I, SndFileFormatT);
			Info.format = ml_flags_value_value(Args[I]);
		} else if (!strcmp(Name, "seekable")) {
			Info.seekable = ml_boolean_value(Args[I]);
		}
	}
	if ((SndFile->Handle = sf_open_virtual(&VirtualIO, Mode, &Info, SndFile))) {
		SndFile->SampleRate = Info.samplerate;
		SndFile->Channels = Info.channels;
		SndFile->Format = Info.format;
		ML_RETURN(SndFile);
	} else {
		ML_ERROR("SndFileError", "%s", sf_strerror(0));
	}
}

ML_METHODVX(SndFileT, MLStreamT, MLStringT) {
//>sndfile
	ml_value_t *Stream = Args[0];
	sndfile_t *SndFile = new(sndfile_t);
	SndFile->Base.Type = SndFileT;
	SndFile->Base.Caller = Caller;
	SndFile->Base.Context = Caller->Context;
	SndFile->Base.run = (ml_state_fn)sndfile_run;
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
	if ((SndFile->Handle = sf_open_virtual(&VirtualIO, Mode, &Info, SndFile))) {
		SndFile->SampleRate = Info.samplerate;
		SndFile->Channels = Info.channels;
		SndFile->Format = Info.format;
		ML_RETURN(SndFile);
	} else {
		ML_ERROR("SndFileError", "%s", sf_strerror(0));
	}
}

ML_METHOD("rate", SndFileT) {
	sndfile_t *SndFile = (sndfile_t *)Args[0];
	return ml_integer(SndFile->SampleRate);
}

ML_METHOD("channels", SndFileT) {
	sndfile_t *SndFile = (sndfile_t *)Args[0];
	return ml_integer(SndFile->Channels);
}

ML_METHOD("format", SndFileT) {
	sndfile_t *SndFile = (sndfile_t *)Args[0];
	return ml_flags_value(SndFileFormatT, SndFile->Format);
}

ML_METHOD("strerror", SndFileT) {
	sndfile_t *SndFile = (sndfile_t *)Args[0];
	return ml_string_copy(sf_strerror(SndFile->Handle), -1);
}

ML_METHOD("read", SndFileT, MLVectorT) {
	sndfile_t *SndFile = (sndfile_t *)Args[0];
	ml_array_t *Vector = (ml_array_t *)Args[1];
	if (Vector->Dimensions->Indices) return ml_error("ValueError", "Sparse vectors not supported");
	sf_count_t Actual = 0;
	switch (Vector->Format) {
	case ML_ARRAY_FORMAT_I16:
	case ML_ARRAY_FORMAT_U16:
		if (Vector->Dimensions->Stride != sizeof(short)) return ml_error("ValueError", "Sparse vectors not supported");
		Actual = sf_read_short(SndFile->Handle, (short *)Vector->Base.Value, Vector->Dimensions->Size);
		break;
	case ML_ARRAY_FORMAT_I32:
	case ML_ARRAY_FORMAT_U32:
		if (Vector->Dimensions->Stride != sizeof(int)) return ml_error("ValueError", "Sparse vectors not supported");
		Actual = sf_read_int(SndFile->Handle, (int *)Vector->Base.Value, Vector->Dimensions->Size);
		break;
	case ML_ARRAY_FORMAT_F32:
		if (Vector->Dimensions->Stride != sizeof(float)) return ml_error("ValueError", "Sparse vectors not supported");
		Actual = sf_read_float(SndFile->Handle, (float *)Vector->Base.Value, Vector->Dimensions->Size);
		break;
	case ML_ARRAY_FORMAT_F64:
		if (Vector->Dimensions->Stride != sizeof(double)) return ml_error("ValueError", "Sparse vectors not supported");
		Actual = sf_read_double(SndFile->Handle, (double *)Vector->Base.Value, Vector->Dimensions->Size);
		break;
	default:
		return ml_error("TypeError", "Array format not supported");
	}
	return ml_integer(Actual);
}

ML_METHOD("read", SndFileT, MLMatrixT) {
	sndfile_t *SndFile = (sndfile_t *)Args[0];
	ml_array_t *Matrix = (ml_array_t *)Args[1];
	if (Matrix->Dimensions[0].Indices) return ml_error("ValueError", "Sparse vectors not supported");
	if (Matrix->Dimensions[1].Indices) return ml_error("ValueError", "Sparse vectors not supported");
	if (Matrix->Dimensions[1].Size != SndFile->Channels) return ml_error("ShapeError", "Number of channels do not match");
	sf_count_t Actual = 0;
	switch (Matrix->Format) {
	case ML_ARRAY_FORMAT_I16:
	case ML_ARRAY_FORMAT_U16:
		if (Matrix->Dimensions[1].Stride != sizeof(short)) return ml_error("ValueError", "Sparse vectors not supported");
		if (Matrix->Dimensions[0].Stride != SndFile->Channels * sizeof(short)) return ml_error("ValueError", "Sparse vectors not supported");
		Actual = sf_readf_short(SndFile->Handle, (short *)Matrix->Base.Value, Matrix->Dimensions[0].Size);
		break;
	case ML_ARRAY_FORMAT_I32:
	case ML_ARRAY_FORMAT_U32:
		if (Matrix->Dimensions[1].Stride != sizeof(int)) return ml_error("ValueError", "Sparse vectors not supported");
		if (Matrix->Dimensions[0].Stride != SndFile->Channels * sizeof(int)) return ml_error("ValueError", "Sparse vectors not supported");
		Actual = sf_readf_int(SndFile->Handle, (int *)Matrix->Base.Value, Matrix->Dimensions[0].Size);
		break;
	case ML_ARRAY_FORMAT_F32:
		if (Matrix->Dimensions[1].Stride != sizeof(float)) return ml_error("ValueError", "Sparse vectors not supported");
		if (Matrix->Dimensions[0].Stride != SndFile->Channels * sizeof(float)) return ml_error("ValueError", "Sparse vectors not supported");
		Actual = sf_readf_float(SndFile->Handle, (float *)Matrix->Base.Value, Matrix->Dimensions[0].Size);
		break;
	case ML_ARRAY_FORMAT_F64:
		if (Matrix->Dimensions[1].Stride != sizeof(double)) return ml_error("ValueError", "Sparse vectors not supported");
		if (Matrix->Dimensions[0].Stride != SndFile->Channels * sizeof(double)) return ml_error("ValueError", "Sparse vectors not supported");
		Actual = sf_readf_double(SndFile->Handle, (double *)Matrix->Base.Value, Matrix->Dimensions[0].Size);
		break;
	default:
		return ml_error("TypeError", "Array format not supported");
	}
	return ml_integer(Actual);
}

ML_METHOD("write", SndFileT, MLVectorT) {
	sndfile_t *SndFile = (sndfile_t *)Args[0];
	ml_array_t *Vector = (ml_array_t *)Args[1];
	if (Vector->Dimensions->Indices) return ml_error("ValueError", "Sparse vectors not supported");
	sf_count_t Actual = 0;
	switch (Vector->Format) {
	case ML_ARRAY_FORMAT_I16:
	case ML_ARRAY_FORMAT_U16:
		if (Vector->Dimensions->Stride != sizeof(short)) return ml_error("ValueError", "Sparse vectors not supported");
		Actual = sf_write_short(SndFile->Handle, (short *)Vector->Base.Value, Vector->Dimensions->Size);
		break;
	case ML_ARRAY_FORMAT_I32:
	case ML_ARRAY_FORMAT_U32:
		if (Vector->Dimensions->Stride != sizeof(int)) return ml_error("ValueError", "Sparse vectors not supported");
		Actual = sf_write_int(SndFile->Handle, (int *)Vector->Base.Value, Vector->Dimensions->Size);
		break;
	case ML_ARRAY_FORMAT_F32:
		if (Vector->Dimensions->Stride != sizeof(float)) return ml_error("ValueError", "Sparse vectors not supported");
		Actual = sf_write_float(SndFile->Handle, (float *)Vector->Base.Value, Vector->Dimensions->Size);
		break;
	case ML_ARRAY_FORMAT_F64:
		if (Vector->Dimensions->Stride != sizeof(double)) return ml_error("ValueError", "Sparse vectors not supported");
		Actual = sf_write_double(SndFile->Handle, (double *)Vector->Base.Value, Vector->Dimensions->Size);
		break;
	default:
		return ml_error("TypeError", "Array format not supported");
	}
	return ml_integer(Actual);
}

ML_METHOD("write", SndFileT, MLMatrixT) {
	sndfile_t *SndFile = (sndfile_t *)Args[0];
	ml_array_t *Matrix = (ml_array_t *)Args[1];
	if (Matrix->Dimensions[0].Indices) return ml_error("ValueError", "Sparse vectors not supported");
	if (Matrix->Dimensions[1].Indices) return ml_error("ValueError", "Sparse vectors not supported");
	if (Matrix->Dimensions[1].Size != SndFile->Channels) return ml_error("ShapeError", "Number of channels do not match");
	sf_count_t Actual = 0;
	switch (Matrix->Format) {
	case ML_ARRAY_FORMAT_I16:
	case ML_ARRAY_FORMAT_U16:
		if (Matrix->Dimensions[1].Stride != sizeof(short)) return ml_error("ValueError", "Sparse vectors not supported");
		if (Matrix->Dimensions[0].Stride != SndFile->Channels * sizeof(short)) return ml_error("ValueError", "Sparse vectors not supported");
		Actual = sf_writef_short(SndFile->Handle, (short *)Matrix->Base.Value, Matrix->Dimensions[0].Size);
		break;
	case ML_ARRAY_FORMAT_I32:
	case ML_ARRAY_FORMAT_U32:
		if (Matrix->Dimensions[1].Stride != sizeof(int)) return ml_error("ValueError", "Sparse vectors not supported");
		if (Matrix->Dimensions[0].Stride != SndFile->Channels * sizeof(int)) return ml_error("ValueError", "Sparse vectors not supported");
		Actual = sf_writef_int(SndFile->Handle, (int *)Matrix->Base.Value, Matrix->Dimensions[0].Size);
		break;
	case ML_ARRAY_FORMAT_F32:
		if (Matrix->Dimensions[1].Stride != sizeof(float)) return ml_error("ValueError", "Sparse vectors not supported");
		if (Matrix->Dimensions[0].Stride != SndFile->Channels * sizeof(float)) return ml_error("ValueError", "Sparse vectors not supported");
		Actual = sf_writef_float(SndFile->Handle, (float *)Matrix->Base.Value, Matrix->Dimensions[0].Size);
		break;
	case ML_ARRAY_FORMAT_F64:
		if (Matrix->Dimensions[1].Stride != sizeof(double)) return ml_error("ValueError", "Sparse vectors not supported");
		if (Matrix->Dimensions[0].Stride != SndFile->Channels * sizeof(double)) return ml_error("ValueError", "Sparse vectors not supported");
		Actual = sf_writef_double(SndFile->Handle, (double *)Matrix->Base.Value, Matrix->Dimensions[0].Size);
		break;
	default:
		return ml_error("TypeError", "Array format not supported");
	}
	return ml_integer(Actual);
}


ML_METHOD("flush", SndFileT) {
	sndfile_t *SndFile = (sndfile_t *)Args[0];
	sf_write_sync(SndFile->Handle);
	return MLNil;
}

ML_METHOD("close", SndFileT) {
	sndfile_t *SndFile = (sndfile_t *)Args[0];
	if (sf_close(SndFile->Handle)) return ml_error("SndFileError", "%s", sf_strerror(SndFile->Handle));
	return MLNil;
}

ML_ENUM2(SndFileStringT, "sndfile::string",
//@sndfile::string
	"Title", SF_STR_TITLE,
	"Copyright", SF_STR_COPYRIGHT,
	"Software", SF_STR_SOFTWARE,
	"Artist", SF_STR_ARTIST,
	"Comment", SF_STR_COMMENT,
	"Date", SF_STR_DATE,
	"Album", SF_STR_ALBUM,
	"License", SF_STR_LICENSE,
	"TrackNumber", SF_STR_TRACKNUMBER,
	"Genre", SF_STR_GENRE
);

ML_METHOD("get", SndFileT, SndFileStringT) {
//<SndFile
//<Name
//>string
	sndfile_t *SndFile = (sndfile_t *)Args[0];
	const char *Value = sf_get_string(SndFile->Handle, ml_enum_value_value(Args[1]));
	if (Value) return ml_string_copy(Value, -1);
	return ml_error("SndFileError", "Unknown attribute %s", ml_enum_value_name(Args[1]));
}

ML_METHOD("set", SndFileT, SndFileStringT, MLStringT) {
//<SndFile
//<Name
//<Value
	sndfile_t *SndFile = (sndfile_t *)Args[0];
	if (!sf_set_string(SndFile->Handle, ml_enum_value_value(Args[1]), ml_string_value(Args[2]))) {
		return Args[0];
	}
	return ml_error("SndFileError", "Unknown attribute %s", ml_enum_value_name(Args[1]));
}

ML_LIBRARY_ENTRY0(snd_sndfile) {
#include "sndfile_init.c"
	stringmap_insert(SndFileT->Exports, "format", SndFileFormatT);
	stringmap_insert(SndFileT->Exports, "string", SndFileStringT);
	Slot[0] = (ml_value_t *)SndFileT;
}
