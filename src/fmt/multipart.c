#include <minilang/ml_library.h>
#include <minilang/ml_macros.h>
#include <minilang/ml_object.h>
#include <minilang/ml_stream.h>
#include "multipart-parser/multipartparser.h"

#undef ML_CATEGORY
#define ML_CATEGORY "fmt/multipart"

typedef struct {
	ml_type_t *Type;
	ml_context_t *Context;
	ml_value_t *Fn, *Headers, *Name, *Stream;
	multipartparser Parser[1];
	ml_stringbuffer_t Buffer[1];
} multipart_t;

ML_TYPE(MultiPartT, (MLStreamT), "multipart");

ML_METHODX(MultiPartT, MLStringT, MLFunctionT) {
	if (ml_string_length(Args[0]) >= 70) ML_ERROR("SizeError", "Boundary string too long (>=70)");
	multipart_t *MultiPart = new(multipart_t);
	MultiPart->Type = MultiPartT;
	MultiPart->Context = Caller->Context;
	multipartparser_init(MultiPart->Parser, ml_string_value(Args[0]));
	MultiPart->Parser->data = MultiPart;
	MultiPart->Buffer[0] = ML_STRINGBUFFER_INIT;
	MultiPart->Fn = Args[1];
	MultiPart->Headers = MLNil;
	MultiPart->Name = MLNil;
	ML_RETURN(MultiPart);
}

static multipartparser_callbacks Callbacks[1];

ML_METHOD("write", MultiPartT, MLAddressT) {
	multipart_t *MultiPart = (multipart_t *)Args[0];
	size_t Result = multipartparser_execute(MultiPart->Parser, Callbacks, ml_address_value(Args[1]), ml_address_length(Args[1]));
	return ml_integer(Result);
}

static int on_body_begin(multipartparser *Parser) {
    return 0;
}

static int on_body_end(multipartparser *Parser) {
    return 0;
}

static int on_header_field(multipartparser *Parser, const char *Data, size_t Size) {
	multipart_t *MultiPart = (multipart_t *)Parser->data;
	if (MultiPart->Buffer->Length) {
		ml_map_insert(MultiPart->Headers, MultiPart->Name, ml_stringbuffer_get_value(MultiPart->Buffer));
	}
	ml_stringbuffer_write(MultiPart->Buffer, Data, Size);
    return 0;
}

static int on_header_value(multipartparser *Parser, const char *Data, size_t Size) {
	multipart_t *MultiPart = (multipart_t *)Parser->data;
	MultiPart->Name = ml_stringbuffer_get_value(MultiPart->Buffer);
	ml_stringbuffer_write(MultiPart->Buffer, Data, Size);
    return 0;
}

static int on_headers_complete(multipartparser *Parser) {
	multipart_t *MultiPart = (multipart_t *)Parser->data;
    if (MultiPart->Buffer->Length) {
		ml_map_insert(MultiPart->Headers, MultiPart->Name, ml_stringbuffer_get_value(MultiPart->Buffer));
	}
    MultiPart->Stream = ml_call_wait(MultiPart->Context, MultiPart->Fn, 1, &MultiPart->Headers);
    return 0;
}

ML_METHOD_DECL(WriteMethod, "write");
ML_METHOD_DECL(CloseMethod, "close");

static int on_data(multipartparser *Parser, const char *Data, size_t Size) {
	multipart_t *MultiPart = (multipart_t *)Parser->data;
	ml_value_t *Args[2] = {MultiPart->Stream, ml_address(Data, Size)};
	ml_call_wait(MultiPart->Context, WriteMethod, 2, Args);
    return 0;
}

static int on_part_begin(multipartparser *Parser) {
	multipart_t *MultiPart = (multipart_t *)Parser->data;
	MultiPart->Headers = ml_map();
    return 0;
}

static int on_part_end(multipartparser *Parser) {
	multipart_t *MultiPart = (multipart_t *)Parser->data;
	ml_call_wait(MultiPart->Context, CloseMethod, 1, &MultiPart->Stream);
    return 0;
}

ML_LIBRARY_ENTRY0(fmt_multipart) {
	multipartparser_callbacks_init(Callbacks);
	Callbacks->on_body_begin = on_body_begin;
	Callbacks->on_body_end = on_body_end;
	Callbacks->on_data = on_data;
	Callbacks->on_header_field = on_header_field;
	Callbacks->on_header_value = on_header_value;
	Callbacks->on_headers_complete = on_headers_complete;
	Callbacks->on_part_begin = on_part_begin;
	Callbacks->on_part_end = on_part_end;
#include "multipart_init.c"
	Slot[0] = (ml_value_t *)MultiPartT;
}
