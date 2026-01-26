#include <minilang/ml_library.h>
#include <minilang/ml_macros.h>
#include <minilang/ml_stream.h>
#include <string.h>
#include "csv.h"

#undef ML_CATEGORY
#define ML_CATEGORY "fmt/csv"

extern ml_type_t MLCsvT[];

typedef struct csv_row_t csv_row_t;

typedef struct {
	ml_state_t Base;
	ml_value_t *Stream, *Iter, *Value;
	ml_stringbuffer_t Buffer[1];
	size_t Length;
} csv_writer_t;

typedef struct {
	ml_state_t Base;
	ml_value_t *Stream;
	ml_value_t *Rows, *Row;
	csv_writer_t *Writer;
	struct csv_parser Parser[1];
	char Input[256];
} csv_t;

static void field_fn(void *Buffer, size_t Size, csv_t *Csv) {
	ml_value_t *Row = Csv->Row;
	if (!Row) {
		Row = Csv->Row = ml_list();
		ml_slice_put(Csv->Rows, Row);
	}
	ml_list_put(Row, ml_string_copy(Buffer, Size));
}

static void row_fn(int Delim, csv_t *Csv) {
	Csv->Row = NULL;
}

static void csv_read_fn(csv_t *Csv, ml_value_t *Value) {
	ml_state_t *Caller = Csv->Base.Caller;
	if (ml_is_error(Value)) ML_RETURN(Value);
	size_t Size = ml_integer_value(Value);
	if (!Size) ML_RETURN(MLNil);
	csv_parse(Csv->Parser, Csv->Input, Size, (void *)field_fn, (void *)row_fn, Csv);
	if (ml_slice_length(Csv->Rows)) ML_RETURN(ml_slice_pop(Csv->Rows));
	return ml_stream_read((ml_state_t *)Csv, Csv->Stream, Csv->Input, 256);
}

ML_METHODX("read", MLCsvT) {
//<Csv
//>list|nil
// Returns the new row from :mini:`Csv` or :mini:`nil` if there are no more rows.
	csv_t *Csv = (csv_t *)Args[0];
	if (ml_slice_length(Csv->Rows)) ML_RETURN(ml_slice_pop(Csv->Rows));
	Csv->Base.Caller = Caller;
	Csv->Base.Context = Caller->Context;
	Csv->Base.run = (ml_state_fn)csv_read_fn;
	return ml_stream_read((ml_state_t *)Csv, Csv->Stream, Csv->Input, 256);
}

static void csv_row_write_fn(csv_writer_t *State, ml_value_t *Value) {
	ml_state_t *Caller = State->Base.Caller;
	if (ml_is_error(Value)) ML_RETURN(Value);
	size_t Length = ml_integer_value(Value);
	ml_stringbuffer_t *Buffer = State->Buffer;
	Length = ml_stringbuffer_reader(Buffer, Length);
	State->Length += Length;
	if (!Length) ML_RETURN(ml_integer(State->Length));
	return ml_stream_write((ml_state_t *)State, State->Stream, Buffer->Head->Chars + Buffer->Start, Length);
}

static void csv_field_next_fn(csv_writer_t *State, ml_value_t *Value);

static void csv_field_string_fn(csv_writer_t *State, ml_value_t *Value) {
	ml_state_t *Caller = State->Base.Caller;
	if (ml_is_error(Value)) ML_RETURN(Value);
	if (!ml_is(Value, MLStringT)) ML_ERROR("TypeError", "Expected string not %s", ml_typeof(Value)->Name);
	ml_stringbuffer_t *Buffer = State->Buffer;
	ml_stringbuffer_put(Buffer, '\"');
	for (const char *P = ml_string_value(Value); *P; ++P) {
		if (*P == '\"') ml_stringbuffer_put(Buffer, '\"');
		ml_stringbuffer_put(Buffer, *P);
	}
	ml_stringbuffer_put(Buffer, '\"');
	State->Base.run = (ml_state_fn)csv_field_next_fn;
	return ml_iter_next((ml_state_t *)State, State->Iter);
}

static void csv_field_value_fn(csv_writer_t *State, ml_value_t *Value) {
	ml_state_t *Caller = State->Base.Caller;
	if (ml_is_error(Value)) ML_RETURN(Value);
	State->Value = Value;
	State->Base.run = (ml_state_fn)csv_field_string_fn;
	return ml_call(State, (ml_value_t *)MLStringT, 1, &State->Value);
}

static void csv_field_next_fn(csv_writer_t *State, ml_value_t *Value) {
	ml_state_t *Caller = State->Base.Caller;
	if (ml_is_error(Value)) ML_RETURN(Value);
	ml_stringbuffer_t *Buffer = State->Buffer;
	if (Value == MLNil) {
		ml_stringbuffer_write(Buffer, "\n", strlen("\n"));
		size_t Length = ml_stringbuffer_reader(Buffer, 0);
		State->Base.run = (ml_state_fn)csv_row_write_fn;
		return ml_stream_write((ml_state_t *)State, State->Stream, Buffer->Head->Chars + Buffer->Start, Length);
	}
	ml_stringbuffer_put(Buffer, ',');
	State->Base.run = (ml_state_fn)csv_field_value_fn;
	return ml_iter_value((ml_state_t *)State, State->Iter = Value);
}

static void csv_field_first_fn(csv_writer_t *State, ml_value_t *Value) {
	ml_state_t *Caller = State->Base.Caller;
	if (ml_is_error(Value)) ML_RETURN(Value);
	if (Value == MLNil) return ml_stream_write(Caller, State->Stream, "\n", strlen("\n"));
	State->Length = 0;
	State->Base.run = (ml_state_fn)csv_field_value_fn;
	return ml_iter_value((ml_state_t *)State, State->Iter = Value);
}

ML_METHODX("write", MLCsvT, MLSequenceT) {
//<Csv
//<Row
//>csv
// Writes a row to :mini:`Csv`.
	csv_t *Csv = (csv_t *)Args[0];
	csv_writer_t *Writer = Csv->Writer;
	if (!Writer) {
		Writer = Csv->Writer = new(csv_writer_t);
		Writer->Buffer[0] = ML_STRINGBUFFER_INIT;
		Writer->Stream = Csv->Stream;
	}
	Writer->Base.Caller = Caller;
	Writer->Base.Context = Caller->Context;
	Writer->Base.run = (ml_state_fn)csv_field_first_fn;
	return ml_iterate((ml_state_t *)Writer, Args[1]);
}

ML_TYPE(MLCsvT, (), "csv");
// An open CSV file.

ML_METHOD(MLCsvT, MLStreamT) {
//<Path
//>csv
// Opens the file at :mini:`Path` for reading or writing as a CSV depending on the value of :mini:`Mode`.
	csv_t *Csv= new(csv_t);
	Csv->Base.Type = MLCsvT;
	Csv->Stream = Args[0];
	csv_init(Csv->Parser, 0);
	Csv->Rows = ml_slice(0);
	Csv->Parser->malloc_func = GC_malloc;
	Csv->Parser->realloc_func = GC_realloc;
	Csv->Parser->free_func = GC_free;
	return (ml_value_t *)Csv;
}

ML_LIBRARY_ENTRY0(fmt_csv) {
#include "csv_init.c"
	Slot[0] = (ml_value_t *)MLCsvT;
}
