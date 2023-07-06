#include <minilang/ml_library.h>
#include <minilang/ml_macros.h>
#include <minilang/ml_cbor.h>
#include <minilang/ml_stream.h>
#include <minilang/ml_uuid.h>
#include "radb/radb.h"
#include <libgen.h>
#include <stdio.h>

#undef ML_CATEGORY
#define ML_CATEGORY "db/radb"

#define CHECK_HANDLE(STORE) \
	if (!(STORE)->Handle) { \
		return ml_error("RadbError", "Radb handle is closed"); \
	}

typedef struct ml_fixed_store_t {
	const ml_type_t *Type;
	fixed_store_t *Handle;
} ml_fixed_store_t;

ML_TYPE(FixedStoreT, (), "fixed-store");
// A store for strings.

ML_FUNCTION(FixedStoreOpen) {
//<Path
//>string_store
// Opens an existing string store at :mini:`Path`.
	ML_CHECK_ARG_COUNT(1);
	ML_CHECK_ARG_TYPE(0, MLStringT);
	ml_fixed_store_t *Store = new(ml_fixed_store_t);
	Store->Type = FixedStoreT;
	Store->Handle = fixed_store_open(ml_string_value(Args[0]));
	if (!Store->Handle) return ml_error("StoreError", "Error opening fixed store");
	return (ml_value_t *)Store;
}

ML_FUNCTION(FixedStoreCreate) {
//<Path
//<NodeSize
//>string_store
// Creates a new string store at :mini:`Path` with node size :mini:`NodeSize` and default chunk size.
	ML_CHECK_ARG_COUNT(2);
	ML_CHECK_ARG_TYPE(0, MLStringT);
	ML_CHECK_ARG_TYPE(1, MLIntegerT);
	size_t ChunkSize = 0;
	ml_fixed_store_t *Store = new(ml_fixed_store_t);
	Store->Type = FixedStoreT;
	Store->Handle = fixed_store_create(ml_string_value(Args[0]), ml_integer_value_fast(Args[1]), ChunkSize);
	CHECK_HANDLE(Store);
	return (ml_value_t *)Store;
}

ML_METHOD("close", FixedStoreT) {
//<Store
// Closes :mini:`Store`.
	ml_fixed_store_t *Store = (ml_fixed_store_t *)Args[0];
	CHECK_HANDLE(Store);
	fixed_store_close(Store->Handle);
	Store->Handle = NULL;
	return MLNil;
}

ML_METHOD("get", FixedStoreT, MLIntegerT) {
//<Store
//<Index
//>string
// Returns the entry at :mini:`Index` in :mini:`Store`.
	ml_fixed_store_t *Store = (ml_fixed_store_t *)Args[0];
	CHECK_HANDLE(Store);
	size_t Index = ml_integer_value_fast(Args[1]);
	void *Value = fixed_store_get(Store->Handle, Index);
	size_t Length = fixed_store_node_size(Store->Handle);
	return ml_buffer(Value, Length);
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
// A store for strings.

ML_FUNCTION(StringStoreOpen) {
//<Path
//>string_store
// Opens an existing string store at :mini:`Path`.
	ML_CHECK_ARG_COUNT(1);
	ML_CHECK_ARG_TYPE(0, MLStringT);
	ml_string_store_t *Store = new(ml_string_store_t);
	Store->Type = StringStoreT;
	Store->Handle = string_store_open(ml_string_value(Args[0]));
	if (!Store->Handle) return ml_error("StoreError", "Error opening string store");
	return (ml_value_t *)Store;
}

ML_FUNCTION(StringStoreCreate) {
//<Path
//<NodeSize
//>string_store
// Creates a new string store at :mini:`Path` with node size :mini:`NodeSize` and default chunk size.
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

ML_METHOD("close", StringStoreT) {
//<Store
// Closes :mini:`Store`.
	ml_string_store_t *Store = (ml_string_store_t *)Args[0];
	CHECK_HANDLE(Store);
	string_store_close(Store->Handle);
	Store->Handle = NULL;
	return MLNil;
}

ML_METHOD("get", StringStoreT, MLIntegerT) {
//<Store
//<Index
//>string
// Returns the entry at :mini:`Index` in :mini:`Store`.
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
//<Store
//<Index
//<Value
//>string
// Stores :mini:`Value` as the entry at :mini:`Index` in :mini:`Store` and returns :mini:`Value`.
	ml_string_store_t *Store = (ml_string_store_t *)Args[0];
	CHECK_HANDLE(Store);
	size_t Index = ml_integer_value_fast(Args[1]);
	string_store_set(Store->Handle, Index, ml_string_value(Args[2]), ml_string_length(Args[2]));
	return Args[2];
}

static void ML_TYPED_FN(ml_stream_write, StringStoreWriterT, ml_state_t *Caller, ml_string_store_writer_t *Writer, const void *Address, int Count) {
	size_t Total = string_store_writer_write(Writer->Handle, Address, Count);
	ML_RETURN(ml_integer(Total));
}

ML_TYPE(StringStoreWriterT, (MLStreamT), "string-store-writer");
// A stream for writing to a string store entry.

ML_METHOD("write", StringStoreT, MLIntegerT) {
	ml_string_store_t *Store = (ml_string_store_t *)Args[0];
	CHECK_HANDLE(Store);
	ml_string_store_writer_t *Writer = new(ml_string_store_writer_t);
	Writer->Type = StringStoreWriterT;
	string_store_writer_open(Writer->Handle, Store->Handle, ml_integer_value_fast(Args[1]));
	return (ml_value_t *)Writer;
}

ML_METHOD("append", StringStoreT, MLIntegerT) {
	ml_string_store_t *Store = (ml_string_store_t *)Args[0];
	CHECK_HANDLE(Store);
	ml_string_store_writer_t *Writer = new(ml_string_store_writer_t);
	Writer->Type = StringStoreWriterT;
	string_store_writer_append(Writer->Handle, Store->Handle, ml_integer_value_fast(Args[1]));
	return (ml_value_t *)Writer;
}

ML_TYPE(StringStoreReaderT, (MLStreamT), "string-store-reader");
// A stream for reading from a string store entry.

static void ML_TYPED_FN(ml_stream_read, StringStoreReaderT, ml_state_t *Caller, ml_string_store_reader_t *Reader, void *Address, int Count) {
	size_t Total = string_store_reader_read(Reader->Handle, Address, Count);
	ML_RETURN(ml_integer(Total));
}

ML_METHOD("read", StringStoreT, MLIntegerT) {
	ml_string_store_t *Store = (ml_string_store_t *)Args[0];
	CHECK_HANDLE(Store);
	ml_string_store_reader_t *Reader = new(ml_string_store_reader_t);
	Reader->Type = StringStoreReaderT;
	string_store_reader_open(Reader->Handle, Store->Handle, ml_integer_value_fast(Args[1]));
	return (ml_value_t *)Reader;
}

ML_TYPE(CborStoreT, (), "cbor-store");

ML_FUNCTION(CborStoreOpen) {
	ML_CHECK_ARG_COUNT(1);
	ML_CHECK_ARG_TYPE(0, MLStringT);
	ml_string_store_t *Store = new(ml_string_store_t);
	Store->Type = CborStoreT;
	Store->Handle = string_store_open(ml_string_value(Args[0]));
	if (!Store->Handle) return ml_error("StoreError", "Error opening string store");
	return (ml_value_t *)Store;
}

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
	ml_cbor_reader_t *Cbor = ml_cbor_reader(NULL, NULL, NULL);
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
	ml_value_t *Error = ml_cbor_encode_to(Writer, (void *)string_store_writer_write, NULL, Args[2]);
	if (Error) return Error;
	return Args[2];
}

typedef struct {
	const ml_type_t *Type;
	linear_index_t *Handle;
	string_store_t *Values;
} ml_string_index_t;

ML_TYPE(StringIndexT, (), "string-index");

typedef struct {
	const char *String;
	size_t Length;
} ml_string_key_t;

static int linear_compare_string(string_store_t *Store, ml_string_key_t *Full, uint32_t Index) {
	if (Full->Length < 16) return 0;
	return string_store_compare(Store, Full->String, Full->Length, Index);
}

static size_t linear_insert_string(string_store_t *Store, ml_string_key_t *Full) {
	size_t Index = string_store_alloc(Store);
	string_store_set(Store, Index, Full->String, Full->Length);
	return Index;
}

ML_FUNCTION(StringIndexCreate) {
	ML_CHECK_ARG_COUNT(1);
	ML_CHECK_ARG_TYPE(0, MLStringT);
	size_t ChunkSize = 0;
	if (Count > 1) {
		ML_CHECK_ARG_TYPE(2, MLIntegerT);
		ChunkSize = ml_integer_value_fast(Args[1]);
	}
	const char *Prefix = ml_string_value(Args[0]);
	string_store_t *Values = string_store_create(Prefix, 16, ChunkSize);
	ml_string_index_t *Store = new(ml_string_index_t);
	Store->Type = StringIndexT;
	Store->Handle = linear_index_create(Prefix, Values);
	linear_index_set_compare(Store->Handle, (linear_compare_t)linear_compare_string);
	linear_index_set_insert(Store->Handle, (linear_insert_t)linear_insert_string);
	CHECK_HANDLE(Store);
	Store->Values = Values;
	return (ml_value_t *)Store;
}

ML_FUNCTION(StringIndexOpen) {
	ML_CHECK_ARG_COUNT(1);
	ML_CHECK_ARG_TYPE(0, MLStringT);
	const char *Prefix = ml_string_value(Args[0]);
	string_store_t *Values = string_store_open(Prefix);
	ml_string_index_t *Store = new(ml_string_index_t);
	Store->Type = StringIndexT;
	Store->Handle = linear_index_open(Prefix, Values);
	linear_index_set_compare(Store->Handle, (linear_compare_t)linear_compare_string);
	linear_index_set_insert(Store->Handle, (linear_insert_t)linear_insert_string);
	CHECK_HANDLE(Store);
	Store->Values = Values;
	return (ml_value_t *)Store;
}

ML_METHOD("close", StringIndexT) {
	ml_string_index_t *Store = (ml_string_index_t *)Args[0];
	CHECK_HANDLE(Store);
	linear_index_close(Store->Handle);
	Store->Handle = NULL;
	string_store_close(Store->Values);
	return MLNil;
}

static uint32_t string_hash(const char *String, size_t Length) {
	uint32_t Hash = 5381;
	for (int I = 0; I < Length; ++I) Hash = ((Hash << 5) + Hash) + String[I];
	return Hash;
}

ML_METHOD("search", StringIndexT, MLStringT) {
	ml_string_index_t *Store = (ml_string_index_t *)Args[0];
	CHECK_HANDLE(Store);
	ml_string_key_t Full = {ml_string_value(Args[1]), ml_string_length(Args[1])};
	linear_key_t Key = {0,};
	if (Full.Length < 16) {
		memcpy(Key, Full.String, Full.Length);
	} else {
		memcpy(Key, Full.String, 15);
		Key[15] = 1;
	}
	uint32_t Hash = string_hash(Full.String, Full.Length);
	size_t Index = linear_index_search(Store->Handle, Hash, Key, &Full);
	if (Index == INVALID_INDEX) return MLNil;
	return ml_integer(Index);
}

ML_METHOD("insert", StringIndexT, MLStringT) {
	ml_string_index_t *Store = (ml_string_index_t *)Args[0];
	CHECK_HANDLE(Store);
	ml_string_key_t Full = {ml_string_value(Args[1]), ml_string_length(Args[1])};
	linear_key_t Key = {0,};
	if (Full.Length < 16) {
		memcpy(Key, Full.String, Full.Length);
	} else {
		memcpy(Key, Full.String, 15);
		Key[15] = 1;
	}
	uint32_t Hash = string_hash(Full.String, Full.Length);
	size_t Index = linear_index_insert(Store->Handle, Hash, Key, &Full);
	return ml_integer(Index);
}

ML_METHOD("delete", StringIndexT, MLStringT) {
	ml_string_index_t *Store = (ml_string_index_t *)Args[0];
	CHECK_HANDLE(Store);
	ml_string_key_t Full = {ml_string_value(Args[1]), ml_string_length(Args[1])};
	linear_key_t Key = {0,};
	if (Full.Length < 16) {
		memcpy(Key, Full.String, Full.Length);
	} else {
		memcpy(Key, Full.String, 15);
		Key[15] = 1;
	}
	uint32_t Hash = string_hash(Full.String, Full.Length);
	size_t Index = linear_index_delete(Store->Handle, Hash, Key, &Full);
	if (Index != INVALID_INDEX) {
		string_store_free(Store->Values, Index);
		return ml_integer(Index);
	} else {
		return MLNil;
	}
}

ML_METHOD("get", StringIndexT, MLIntegerT) {
	ml_string_index_t *Store = (ml_string_index_t *)Args[0];
	CHECK_HANDLE(Store);
	size_t Index = ml_integer_value_fast(Args[1]);
	size_t Size = string_store_size(Store->Values, Index);
	char *Value = snew(Size + 1);
	string_store_get(Store->Values, Index, Value, Size);
	return ml_string(Value, Size);
}

ML_METHOD("count", StringIndexT) {
	ml_string_index_t *Store = (ml_string_index_t *)Args[0];
	CHECK_HANDLE(Store);
	return ml_integer(linear_index_count(Store->Handle));
}

typedef struct {
	const ml_type_t *Type;
	linear_index_t *Handle;
	fixed_store_t *Values;
} ml_uuid_index_t;

ML_TYPE(UUIDIndexT, (), "uuid-index");

static int linear_compare_uuid(fixed_store_t *Store, void *Full, uint32_t Index) {
	return 0;
}

static size_t linear_insert_uuid(fixed_store_t *Store, void *Full) {
	size_t Index = fixed_store_alloc(Store);
	memcpy(fixed_store_get(Store, Index), Full, 16);
	return Index;
}

ML_FUNCTION(UUIDIndexCreate) {
	ML_CHECK_ARG_COUNT(1);
	ML_CHECK_ARG_TYPE(0, MLStringT);
	const char *Prefix = ml_string_value(Args[0]);
	fixed_store_t *Values = fixed_store_create(Prefix, 16, 512);
	ml_uuid_index_t *Store = new(ml_uuid_index_t);
	Store->Type = UUIDIndexT;
	Store->Handle = linear_index_create(Prefix, Values);
	linear_index_set_compare(Store->Handle, (linear_compare_t)linear_compare_uuid);
	linear_index_set_insert(Store->Handle, (linear_insert_t)linear_insert_uuid);
	CHECK_HANDLE(Store);
	Store->Values = Values;
	return (ml_value_t *)Store;
}

ML_FUNCTION(UUIDIndexOpen) {
	ML_CHECK_ARG_COUNT(1);
	ML_CHECK_ARG_TYPE(0, MLStringT);
	const char *Prefix = ml_string_value(Args[0]);
	fixed_store_t *Values = fixed_store_open(Prefix);
	ml_uuid_index_t *Store = new(ml_uuid_index_t);
	Store->Type = UUIDIndexT;
	Store->Handle = linear_index_open(Prefix, Values);
	linear_index_set_compare(Store->Handle, (linear_compare_t)linear_compare_uuid);
	linear_index_set_insert(Store->Handle, (linear_insert_t)linear_insert_uuid);
	CHECK_HANDLE(Store);
	Store->Values = Values;
	return (ml_value_t *)Store;
}

ML_METHOD("search", UUIDIndexT, MLUUIDT) {
	ml_uuid_index_t *Store = (ml_uuid_index_t *)Args[0];
	CHECK_HANDLE(Store);
	size_t Index = linear_index_search(Store->Handle, *(uint32_t *)ml_uuid_value(Args[1]), ml_uuid_value(Args[1]), ml_uuid_value(Args[1]));
	return Index == INVALID_INDEX ? MLNil : ml_integer(Index);
}

ML_METHOD("insert", UUIDIndexT, MLUUIDT) {
	ml_uuid_index_t *Store = (ml_uuid_index_t *)Args[0];
	CHECK_HANDLE(Store);
	size_t Index = linear_index_insert(Store->Handle, *(uint32_t *)ml_uuid_value(Args[1]), ml_uuid_value(Args[1]), ml_uuid_value(Args[1]));
	return ml_integer(Index);
}

ML_METHOD("delete", UUIDIndexT, MLUUIDT) {
	ml_uuid_index_t *Store = (ml_uuid_index_t *)Args[0];
	CHECK_HANDLE(Store);
	size_t Index = linear_index_delete(Store->Handle, *(uint32_t *)ml_uuid_value(Args[1]), ml_uuid_value(Args[1]), ml_uuid_value(Args[1]));
	if (Index != INVALID_INDEX) {
		fixed_store_free(Store->Values, Index);
		return ml_integer(Index);
	} else {
		return MLNil;
	}
}

ML_METHOD("get", UUIDIndexT, MLIntegerT) {
	ml_uuid_index_t *Store = (ml_uuid_index_t *)Args[0];
	CHECK_HANDLE(Store);
	return ml_uuid(fixed_store_get(Store->Values, ml_integer_value(Args[1])));
}

ML_METHOD("count", UUIDIndexT) {
	ml_uuid_index_t *Store = (ml_uuid_index_t *)Args[0];
	CHECK_HANDLE(Store);
	return ml_integer(linear_index_count(Store->Handle));
}

ML_METHOD("close", UUIDIndexT) {
	ml_uuid_index_t *Store = (ml_uuid_index_t *)Args[0];
	CHECK_HANDLE(Store);
	linear_index_close(Store->Handle);
	fixed_store_close(Store->Values);
	Store->Handle = NULL;
	return MLNil;
}

ML_LIBRARY_ENTRY0(db_radb) {
#include "radb_init.c"
	stringmap_insert(FixedStoreT->Exports, "open", FixedStoreOpen);
	stringmap_insert(FixedStoreT->Exports, "create", FixedStoreCreate);
	stringmap_insert(StringStoreT->Exports, "open", StringStoreOpen);
	stringmap_insert(StringStoreT->Exports, "create", StringStoreCreate);
	stringmap_insert(CborStoreT->Exports, "open", CborStoreOpen);
	stringmap_insert(CborStoreT->Exports, "create", CborStoreCreate);
	stringmap_insert(StringIndexT->Exports, "open", StringIndexOpen);
	stringmap_insert(StringIndexT->Exports, "create", StringIndexCreate);
	stringmap_insert(UUIDIndexT->Exports, "open", UUIDIndexOpen);
	stringmap_insert(UUIDIndexT->Exports, "create", UUIDIndexCreate);
	Slot[0] = ml_module("radb",
		"fixed_store", FixedStoreT,
		"string_store", StringStoreT,
		"cbor_store", CborStoreT,
		"string_index", StringIndexT,
		"uuid_index", UUIDIndexT,
	NULL);
}
