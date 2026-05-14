#include <minilang/ml_library.h>
#include <minilang/ml_macros.h>
#include <minilang/ml_object.h>
#include <minilang/ml_logging.h>
#include <fluent-bit/flb_lib.h>
#include <string.h>

#undef ML_CATEGORY
#define ML_CATEGORY "log/fluent-bit"

static flb_ctx_t *Ctx = NULL;

ML_TYPE(FLBContextT, (), "flb-context");

ML_VALUE(FLBContext, FLBContextT);

ML_METHOD("set", FLBContextT, MLStringT, MLStringT) {
	const char *Property = ml_string_value(Args[1]);
	int Ret = flb_service_set(Ctx, Property, ml_string_value(Args[2]), NULL);
	if (Ret < 0) return ml_error("FluentBitError", "Error setting property %s", Property);
	return FLBContext;
}

static int LibInput = -1;

static const char *LogLevelNames[] = {
	[ML_LOG_LEVEL_NONE] = "NONE",
	[ML_LOG_LEVEL_FATAL] = "FATAL",
	[ML_LOG_LEVEL_ERROR] = "ERROR",
	[ML_LOG_LEVEL_WARN] = "WARN",
	[ML_LOG_LEVEL_MESSAGE] = "MESSAGE",
	[ML_LOG_LEVEL_INFO] = "INFO",
	[ML_LOG_LEVEL_DEBUG] = "DEBUG"
};

static void flb_log(ml_logger_t *Logger, ml_log_level_t Level, ml_value_t *Error, const char *Source, int Line, const char *Format, ...) {
	char Record[512];
	struct timespec Time;
	clock_gettime(CLOCK_REALTIME, &Time);
	long Milli = Time.tv_nsec / 1000;
	int PrefixLength = snprintf(Record, 508, "[%ld.%06ld,{\"level\":\"%s\",\"source\":\"%s\",\"message\":\"", Time.tv_sec, Milli, LogLevelNames[Level], Logger->Name);
	va_list Args;
	va_start(Args, Format);
	int TotalLength = PrefixLength + vsnprintf(Record + PrefixLength, 508 - PrefixLength, Format, Args);
	va_end(Args);
	int Escapes = 0;
	for (int I = PrefixLength; I < TotalLength; ++I) if (Record[I] == '\\' || Record[I] == '\"') ++Escapes;
	//fprintf(stderr, "#Escapes = %d\n", Escapes);
	if (!Escapes) {
		if (TotalLength >= 509) {
			strcpy(Record + 505, "...\"}]");
			TotalLength = 511;
		} else {
			strcpy(Record + TotalLength, "\"}]");
			TotalLength += 3;
		}
	} else {
		int MessageLength = TotalLength, EscapedLength = MessageLength + Escapes;
		if (EscapedLength >= 509) {
			do {
				--MessageLength;
				if (Record[MessageLength] == '\\' || Record[MessageLength] == '\"') --Escapes;
				EscapedLength = MessageLength + Escapes;
			} while (EscapedLength >= 505);
			strcpy(Record + EscapedLength, "...\"}]");
			TotalLength = EscapedLength + 6;
		} else {
			strcpy(Record + EscapedLength, "\"}]");
			TotalLength = EscapedLength + 3;
		}
		//fprintf(stderr, "MessageLength = %d, EscapedLength = %d, TotalLength = %d\n", MessageLength, EscapedLength, TotalLength);
		for (int J = MessageLength - 1, K = EscapedLength - 1; Escapes;) {
			char C = Record[J--];
			Record[K--] = C;
			if (C == '\\' || C == '\"') {
				Record[K--] = '\\';
				--Escapes;
			}
		}
	}
	//fprintf(stderr, "Record = %.*s\n", TotalLength, Record);
	flb_lib_push(Ctx, LibInput, Record, TotalLength);
}

ML_METHOD("use", FLBContextT) {
	ml_log = flb_log;
	flb_start(Ctx);
	return MLNil;
}

#define FLB_STAGE(NAME, CNAME) \
\
typedef struct { \
	ml_type_t *Type; \
	int Handle; \
} flb_ ## CNAME ## _t; \
\
ML_TYPE(FLB ## NAME ## T, (), "flb-" #CNAME); \
\
ML_METHOD(#CNAME, FLBContextT, MLStringT) { \
	int Handle = flb_ ## CNAME(Ctx, ml_string_value(Args[1]), NULL); \
	if (Handle < 0) return ml_error("FluentBitError", "Error creating fluent-bit " #CNAME); \
	flb_ ## CNAME ## _t *NAME = new(flb_ ## CNAME ## _t); \
	NAME->Type = FLB ## NAME ## T; \
	NAME->Handle = Handle; \
	return (ml_value_t *)NAME; \
} \
\
ML_METHOD("set", FLB ## NAME ## T, MLStringT, MLStringT) { \
	flb_ ## CNAME ## _t *NAME = (flb_ ## CNAME ## _t *)Args[0]; \
	const char *Property = ml_string_value(Args[1]); \
	int Ret = flb_ ## CNAME ## _set(Ctx, NAME->Handle, Property, ml_string_value(Args[2]), NULL); \
	if (Ret < 0) return ml_error("FluentBitError", "Error setting property %s", Property); \
	return (ml_value_t *)NAME; \
}

FLB_STAGE(Input, input)
FLB_STAGE(Output, output)
FLB_STAGE(Filter, filter)

ML_LIBRARY_ENTRY0(log_fluent_bit) {
	Ctx = flb_create();
	LibInput = flb_input(Ctx, "lib", NULL);
#include "fluent_bit_init.c"
	Slot[0] = FLBContext;
}
