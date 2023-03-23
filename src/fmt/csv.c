#include <minilang/ml_library.h>
#include <minilang/ml_macros.h>
#include <string.h>
#include <stdio.h>
#include "csv.h"

#undef ML_CATEGORY
#define ML_CATEGORY "fmt/csv"

extern ml_type_t MLCsvT[];

typedef struct csv_row_t csv_row_t;

typedef struct csv_t {
	const ml_type_t *Type;
	FILE *File;
	csv_row_t *Head, *Tail;
	ml_value_t *Row;
	struct csv_parser Parser[1];
} csv_t;

struct csv_row_t {
	csv_row_t *Next;
	ml_value_t *Values;
};

static void field_fn(void *Buffer, size_t Size, csv_t *Csv) {
	char *Copy = GC_malloc_atomic(Size + 1);
	memcpy(Copy, Buffer, Size);
	Copy[Size] = 0;
	ml_list_append(Csv->Row, ml_string(Copy, Size));
}

static void row_fn(int Delim, csv_t *Csv) {
	csv_row_t *Row = new(csv_row_t);
	Row->Values = Csv->Row;
	Csv->Row = ml_list();
	if (Csv->Tail) {
		Csv->Tail->Next = Row;
	} else {
		Csv->Head = Row;
	}
	Csv->Tail = Row;
}

ML_METHOD("read", MLCsvT) {
//<Csv
//>list|nil
// Returns the new row from :mini:`Csv` or :mini:`nil` if there are no more rows.
	csv_t *Csv = (csv_t *)Args[0];
	char Buffer[256];
	while (!Csv->Head) {
		size_t Size = fread(Buffer, 1, 256, Csv->File);
		if (Size == 0) return MLNil;
		csv_parse(Csv->Parser, Buffer, Size, (void *)field_fn, (void *)row_fn, Csv);
	}
	csv_row_t *Row = Csv->Head;
	Csv->Head = Row->Next;
	if (!Row->Next) Csv->Tail = NULL;
	return Row->Values;
}

ML_METHOD("write", MLCsvT, MLListT) {
//<Csv
//<Row
//>csv
// Writes a row to :mini:`Csv`.
	csv_t *Csv = (csv_t *)Args[0];
	int Comma = 0;
	ML_LIST_FOREACH(Args[1], Node) {
		if (Comma) fputc(',', Csv->File);
		ml_value_t *Field = Node->Value;
		if (Field->Type != MLStringT) {
			Field = ml_simple_call((ml_value_t *)MLStringT, 1, &Field);
			if (Field->Type == MLErrorT) return Field;
			if (Field->Type != MLStringT) return ml_error("ResultError", "string method did not return string");
		}
		csv_fwrite(Csv->File, ml_string_value(Field), ml_string_length(Field));
		Comma = 1;
	}
	fputc('\n', Csv->File);
	return Args[0];
}

ML_METHOD("close", MLCsvT) {
//<Csv
// Closes :mini:`Csv`.
	csv_t *Csv = (csv_t *)Args[0];
	if (Csv->File) {
		fclose(Csv->File);
		Csv->File = 0;
	}
	return MLNil;
}

static void csv_finalize(csv_t *Csv, void *Data) {
	if (Csv->File) {
		fclose(Csv->File);
		Csv->File = 0;
	}
}

ML_TYPE(MLCsvT, (), "csv");
// An open CSV file.

ML_METHOD(MLCsvT, MLStringT, MLStringT) {
//<Path
//<Mode
//>csv
// Opens the file at :mini:`Path` for reading or writing as a CSV depending on the value of :mini:`Mode`.
	ml_value_t *FileName = Args[0];
	const char *Path = ml_string_value(FileName);
	const char *Mode = ml_string_value(Args[1]);
	FILE *File = fopen(Path, Mode);
	if (!File) return ml_error("FileError", "failed to open %s in mode %s", Path, Mode);
	csv_t *Csv= new(csv_t);
	Csv->Type = MLCsvT;
	Csv->File = File;
	csv_init(Csv->Parser, 0);
	Csv->Row = ml_list();
	Csv->Parser->malloc_func = GC_malloc;
	Csv->Parser->realloc_func = GC_realloc;
	Csv->Parser->free_func = GC_free;
	GC_register_finalizer(Csv, (void *)csv_finalize, 0, 0, 0);
	return (ml_value_t *)Csv;
}

ML_LIBRARY_ENTRY0 {
#include "csv_init.c"
	Slot[0] = (ml_value_t *)MLCsvT;
}
