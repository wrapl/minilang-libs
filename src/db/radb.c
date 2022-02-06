#include <minilang/ml_library.h>
#include <minilang/ml_macros.h>
#include <minilang/ml_cbor.h>
#include "radb/radb.h"
#include <libgen.h>
#include <stdio.h>

#define CHECK_HANDLE(STORE) \
	if (!(STORE)->Handle) { \
		return ml_error("RadbError", "Radb handle is closed"); \
	}

typedef struct ml_string_store_t {
	const ml_type_t *Type;
	string_store_t *Handle;
} ml_string_store_t;

typedef struct ml_string_store_writer_t {
	const ml_type_t *Type;
	string_store_writer_t Handle[1];
} ml_string_store_writer_t;

typedef struct ml_string_store_reader_t {
	const ml_type_t *Type;
	string_store_reader_t Handle[1];
} ml_string_store_reader_t;

ML_TYPE(StringStoreT, (), "string-store");
ML_TYPE(StringStoreWriterT, (), "string-store-writer");
ML_TYPE(StringStoreReaderT, (), "string-store-reader");

ML_FUNCTION(StringStoreCreate) {
	ML_CHECK_ARG_COUNT(2);
	ML_CHECK_ARG_TYPE(0, MLStringT);
	ML_CHECK_ARG_TYPE(1, MLIntegerT);
	size_t ChunkSize = 0;
	if (Count > 2) {
		ML_CHECK_ARG_TYPE(2, MLIntegerT);
		ChunkSize = ml_integer_value_fast(Args[2]);
	}
	ml_string_store_t *Store = new(ml_string_store_t);
	Store->Type = StringStoreT;
	Store->Handle = string_store_create(ml_string_value(Args[0]), ml_integer_value_fast(Args[1]), ChunkSize);
	CHECK_HANDLE(Store);
	return (ml_value_t *)Store;
}

ML_FUNCTION(StringStoreOpen) {
	ML_CHECK_ARG_COUNT(1);
	ML_CHECK_ARG_TYPE(0, MLStringT);
	ml_string_store_t *Store = new(ml_string_store_t);
	Store->Type = StringStoreT;
	Store->Handle = string_store_open(ml_string_value(Args[0]));
	if (!Store->Handle) return ml_error("StoreError", "Error opening string store");
	return (ml_value_t *)Store;
}

ML_METHOD("close", StringStoreT) {
	ml_string_store_t *Store = (ml_string_store_t *)Args[0];
	CHECK_HANDLE(Store);
	string_store_close(Store->Handle);
	Store->Handle = NULL;
	return MLNil;
}

ML_METHOD("get", StringStoreT, MLIntegerT) {
	ml_string_store_t *Store = (ml_string_store_t *)Args[0];
	CHECK_HANDLE(Store);
	size_t Index = ml_integer_value_fast(Args[1]);
	size_t Length = string_store_size(Store->Handle, Index);
	if (Length == INVALID_INDEX) return ml_error("IndexError", "Invalid index");
	char *Value = snew(Length + 1);
	string_store_get(Store->Handle, Index, Value, Length);
	Value[Length] = 0;
	return ml_string(Value, Length);
}

ML_METHOD("set", StringStoreT, MLIntegerT, MLStringT) {
	ml_string_store_t *Store = (ml_string_store_t *)Args[0];
	CHECK_HANDLE(Store);
	size_t Index = ml_integer_value_fast(Args[1]);
	string_store_set(Store->Handle, Index, ml_string_value(Args[2]), ml_string_length(Args[2]));
	return Args[2];
}

ML_METHOD("write", StringStoreT, MLIntegerT) {
	ml_string_store_t *Store = (ml_string_store_t *)Args[0];
	CHECK_HANDLE(Store);
	ml_string_store_writer_t *Writer = new(ml_string_store_writer_t);
	Writer->Type = StringStoreWriterT;
	string_store_writer_open(Writer->Handle, Store->Handle, ml_integer_value_fast(Args[1]));
	return (ml_value_t *)Writer;
}

ML_METHOD("write", StringStoreWriterT, MLStringT) {
	ml_string_store_writer_t *Writer = (ml_string_store_writer_t *)Args[0];
	size_t Total = string_store_writer_write(Writer->Handle, ml_string_value(Args[1]), ml_string_length(Args[1]));
	return ml_integer(Total);
}

ML_METHOD("read", StringStoreT, MLIntegerT) {
	ml_string_store_t *Store = (ml_string_store_t *)Args[0];
	CHECK_HANDLE(Store);
	ml_string_store_reader_t *Reader = new(ml_string_store_reader_t);
	Reader->Type = StringStoreReaderT;
	string_store_reader_open(Reader->Handle, Store->Handle, ml_integer_value_fast(Args[1]));
	return (ml_value_t *)Reader;
}

ML_METHOD("read", StringStoreReaderT, MLIntegerT) {
	ml_string_store_reader_t *Reader = (ml_string_store_reader_t *)Args[0];
	size_t Size = ml_integer_value_fast(Args[1]);
	char *Buffer = GC_MALLOC_ATOMIC(Size);
	size_t Length = string_store_reader_read(Reader->Handle, Buffer, Size);
	return ml_string(Buffer, Length);
}

ML_TYPE(CborStoreT, (), "cbor-store");

ML_FUNCTION(CborStoreCreate) {
	ML_CHECK_ARG_COUNT(2);
	ML_CHECK_ARG_TYPE(0, MLStringT);
	ML_CHECK_ARG_TYPE(1, MLIntegerT);
	size_t ChunkSize = 0;
	if (Count > 2) {
		ML_CHECK_ARG_TYPE(2, MLIntegerT);
		ChunkSize = ml_integer_value_fast(Args[2]);
	}
	ml_string_store_t *Store = new(ml_string_store_t);
	Store->Type = CborStoreT;
	Store->Handle = string_store_create(ml_string_value(Args[0]), ml_integer_value_fast(Args[1]), ChunkSize);
	CHECK_HANDLE(Store);
	return (ml_value_t *)Store;
}

ML_FUNCTION(CborStoreOpen) {
	ML_CHECK_ARG_COUNT(1);
	ML_CHECK_ARG_TYPE(0, MLStringT);
	ml_string_store_t *Store = new(ml_string_store_t);
	Store->Type = CborStoreT;
	Store->Handle = string_store_open(ml_string_value(Args[0]));
	if (!Store->Handle) return ml_error("StoreError", "Error opening string store");
	return (ml_value_t *)Store;
}

ML_METHOD("close", CborStoreT) {
	ml_string_store_t *Store = (ml_string_store_t *)Args[0];
	CHECK_HANDLE(Store);
	string_store_close(Store->Handle);
	Store->Handle = NULL;
	return MLNil;
}

ML_METHOD("get", CborStoreT, MLIntegerT) {
	ml_string_store_t *Store = (ml_string_store_t *)Args[0];
	CHECK_HANDLE(Store);
	size_t Index = ml_integer_value_fast(Args[1]);
	size_t Length = string_store_size(Store->Handle, Index);
	if (Length == INVALID_INDEX) return ml_error("IndexError", "Invalid index");
	ml_cbor_reader_t *Cbor = ml_cbor_reader_new(NULL, NULL);
	string_store_reader_t Reader[1];
	string_store_reader_open(Reader, Store->Handle, Index);
	unsigned char Buffer[16];
	size_t Size;
	do {
		Size = string_store_reader_read(Reader, Buffer, 16);
		ml_cbor_reader_read(Cbor, Buffer, Size);
	} while (Size == 16);
	return ml_cbor_reader_get(Cbor);
}

ML_METHOD("set", CborStoreT, MLIntegerT, MLAnyT) {
	ml_string_store_t *Store = (ml_string_store_t *)Args[0];
	CHECK_HANDLE(Store);
	size_t Index = ml_integer_value_fast(Args[1]);
	string_store_writer_t Writer[1];
	string_store_writer_open(Writer, Store->Handle, Index);
	ml_cbor_writer_t *CborWriter = ml_cbor_writer_new(Writer, (void *)string_store_writer_write, NULL);
	ml_value_t *Error = ml_cbor_write(CborWriter, Args[2]);
	if (Error) return Error;
	return Args[2];
}

typedef struct ml_string_index_t {
	const ml_type_t *Type;
	string_index_t *Handle;
} ml_string_index_t;

ML_TYPE(StringIndexT, (), "string-index");

ML_FUNCTION(StringIndexCreate) {
	ML_CHECK_ARG_COUNT(1);
	ML_CHECK_ARG_TYPE(0, MLStringT);
	size_t ChunkSize = 0;
	if (Count > 1) {
		ML_CHECK_ARG_TYPE(2, MLIntegerT);
		ChunkSize = ml_integer_value_fast(Args[1]);
	}
	ml_string_index_t *Store = new(ml_string_index_t);
	Store->Type = StringIndexT;
	Store->Handle = string_index_create(ml_string_value(Args[0]), 16, ChunkSize);
	CHECK_HANDLE(Store);
	return (ml_value_t *)Store;
}

ML_FUNCTION(StringIndexOpen) {
	ML_CHECK_ARG_COUNT(1);
	ML_CHECK_ARG_TYPE(0, MLStringT);
	ml_string_index_t *Store = new(ml_string_index_t);
	Store->Type = StringIndexT;
	Store->Handle = string_index_open(ml_string_value(Args[0]));
	if (!Store->Handle) return ml_error("StoreError", "Error opening string store");
	return (ml_value_t *)Store;
}

ML_METHOD("close", StringIndexT) {
	ml_string_index_t *Store = (ml_string_index_t *)Args[0];
	CHECK_HANDLE(Store);
	string_index_close(Store->Handle);
	Store->Handle = NULL;
	return MLNil;
}

ML_METHOD("insert", StringIndexT, MLStringT) {
	ml_string_index_t *Store = (ml_string_index_t *)Args[0];
	CHECK_HANDLE(Store);
	size_t Index = string_index_insert(Store->Handle, ml_string_value(Args[1]), ml_string_length(Args[1]));
	return ml_integer(Index);
}

ML_METHOD("search", StringIndexT, MLStringT) {
	ml_string_index_t *Store = (ml_string_index_t *)Args[0];
	CHECK_HANDLE(Store);
	size_t Index = string_index_search(Store->Handle, ml_string_value(Args[1]), ml_string_length(Args[1]));
	if (Index == INVALID_INDEX) return MLNil;
	return ml_integer(Index);
}

ML_METHOD("get", StringIndexT, MLIntegerT) {
	ml_string_index_t *Store = (ml_string_index_t *)Args[0];
	CHECK_HANDLE(Store);
	size_t Index = ml_integer_value_fast(Args[1]);
	size_t Size = string_index_size(Store->Handle, Index);
	char *Value = snew(Size + 1);
	string_index_get(Store->Handle, Index, Value, Size);
	return ml_string(Value, Size);
}

ML_METHOD("count", StringIndexT) {
	ml_string_index_t *Store = (ml_string_index_t *)Args[0];
	CHECK_HANDLE(Store);
	return ml_integer(string_index_count(Store->Handle));
}

ML_TYPE(CborIndexT, (), "cbor-index");

ML_FUNCTION(CborIndexCreate) {
	ML_CHECK_ARG_COUNT(1);
	ML_CHECK_ARG_TYPE(0, MLStringT);
	size_t ChunkSize = 0;
	if (Count > 1) {
		ML_CHECK_ARG_TYPE(2, MLIntegerT);
		ChunkSize = ml_integer_value_fast(Args[1]);
	}
	ml_string_index_t *Store = new(ml_string_index_t);
	Store->Type = CborIndexT;
	Store->Handle = string_index_create(ml_string_value(Args[0]), 16, ChunkSize);
	CHECK_HANDLE(Store);
	return (ml_value_t *)Store;
}

ML_FUNCTION(CborIndexOpen) {
	ML_CHECK_ARG_COUNT(1);
	ML_CHECK_ARG_TYPE(0, MLStringT);
	ml_string_index_t *Store = new(ml_string_index_t);
	Store->Type = CborIndexT;
	Store->Handle = string_index_open(ml_string_value(Args[0]));
	if (!Store->Handle) return ml_error("StoreError", "Error opening string store");
	return (ml_value_t *)Store;
}

ML_METHOD("close", CborIndexT) {
	ml_string_index_t *Store = (ml_string_index_t *)Args[0];
	CHECK_HANDLE(Store);
	string_index_close(Store->Handle);
	Store->Handle = NULL;
	return MLNil;
}

ML_METHOD("insert", CborIndexT, MLAnyT) {
	ml_string_index_t *Store = (ml_string_index_t *)Args[0];
	CHECK_HANDLE(Store);
	ml_cbor_t Cbor = ml_to_cbor(Args[1]);
	if (!Cbor.Length) return Cbor.Error;
	size_t Index = string_index_insert(Store->Handle, Cbor.Data, Cbor.Length);
	return ml_integer(Index);
}

ML_METHOD("search", CborIndexT, MLAnyT) {
	ml_string_index_t *Store = (ml_string_index_t *)Args[0];
	CHECK_HANDLE(Store);
	ml_cbor_t Cbor = ml_to_cbor(Args[1]);
	if (!Cbor.Length) return Cbor.Error;
	size_t Index = string_index_search(Store->Handle, Cbor.Data, Cbor.Length);
	if (Index == INVALID_INDEX) return MLNil;
	return ml_integer(Index);
}

ML_METHOD("get", CborIndexT, MLIntegerT) {
	ml_string_index_t *Store = (ml_string_index_t *)Args[0];
	CHECK_HANDLE(Store);
	int Index = ml_integer_value_fast(Args[1]);
	int Size = string_index_size(Store->Handle, Index);
	char *Bytes = snew(Size + 1);
	string_index_get(Store->Handle, Index, Bytes, Size);
	ml_cbor_t Cbor = {{Bytes}, Size};
	return ml_from_cbor(Cbor, NULL);
}

void ml_library_entry0(ml_value_t **Slot) {
#include "radb_init.c"
	Slot[0] = ml_module("radb",
		"string_store_create", StringStoreCreate,
		"string_store_open", StringStoreOpen,
		"cbor_store_create", CborStoreCreate,
		"cbor_store_open", CborStoreOpen,
		"string_index_create", StringIndexCreate,
		"string_index_open", StringIndexOpen,
		"cbor_index_create", CborIndexCreate,
		"cbor_index_open", CborIndexOpen,
	NULL);
}
