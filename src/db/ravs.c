#include <minilang/ml_library.h>
#include <minilang/ml_macros.h>
#include <minilang/ml_cbor.h>
#include "ravs/ravs.h"
#include <libgen.h>
#include <stdio.h>

#undef ML_CATEGORY
#define ML_CATEGORY "db/ravs"

#define CHECK_HANDLE(STORE) \
	if (!(STORE)->Handle) { \
		return ml_error("RadbError", "Ravs handle is closed"); \
	}

typedef struct {
	const ml_type_t *Type;
	version_store_t *Handle;
} ml_version_store_t;

ML_TYPE(VersionStoreT, (), "version-store");

ML_FUNCTION(VersionStoreCreate) {
	ML_CHECK_ARG_COUNT(1);
	ML_CHECK_ARG_TYPE(0, MLStringT);
	ml_version_store_t *Store = new(ml_version_store_t);
	Store->Type = VersionStoreT;
	Store->Handle = version_store_create(ml_string_value(Args[0]), 16);
	CHECK_HANDLE(Store);
	return (ml_value_t *)Store;
}

ML_FUNCTION(VersionStoreOpen) {
	ML_CHECK_ARG_COUNT(1);
	ML_CHECK_ARG_TYPE(0, MLStringT);
	ml_version_store_t *Store = new(ml_version_store_t);
	Store->Type = VersionStoreT;
	Store->Handle = version_store_open(ml_string_value(Args[0]));
	CHECK_HANDLE(Store);
	return (ml_value_t *)Store;
}

ML_METHOD("close", VersionStoreT) {
	ml_version_store_t *Store = (ml_version_store_t *)Args[0];
	CHECK_HANDLE(Store);
	version_store_close(Store->Handle);
	Store->Handle = NULL;
	return MLNil;
}

ML_METHOD("change", VersionStoreT, MLStringT) {
	ml_version_store_t *Store = (ml_version_store_t *)Args[0];
	CHECK_HANDLE(Store);
	version_store_change_create(Store->Handle, ml_string_value(Args[1]), ml_string_length(Args[1]));
	return Args[0];
}

static int changes_fn(ml_value_t *Changes, uint32_t Index) {
	ml_list_put(Changes, ml_integer(Index));
	return 0;
}

ML_METHOD("changes", VersionStoreT, MLIntegerT) {
	ml_version_store_t *Store = (ml_version_store_t *)Args[0];
	CHECK_HANDLE(Store);
	ml_value_t *Changes = ml_list();
	version_store_change_list(Store->Handle, ml_integer_value_fast(Args[1]), (void *)changes_fn, Changes);
	return Changes;
}

ML_METHOD("add", VersionStoreT, MLAnyT) {
	ml_version_store_t *Store = (ml_version_store_t *)Args[0];
	CHECK_HANDLE(Store);
	ml_cbor_t Cbor = ml_to_cbor(Args[1]);
	if (!Cbor.Length) return Cbor.Error;
	size_t Index = version_store_value_create(Store->Handle, Cbor.Data, Cbor.Length);
	return ml_integer(Index);
}

ML_METHOD("set", VersionStoreT, MLIntegerT, MLAnyT) {
	ml_version_store_t *Store = (ml_version_store_t *)Args[0];
	CHECK_HANDLE(Store);
	size_t Index = ml_integer_value_fast(Args[1]);
	ml_cbor_t Cbor = ml_to_cbor(Args[2]);
	if (!Cbor.Length) return Cbor.Error;
	version_store_value_update(Store->Handle, Index, Cbor.Data, Cbor.Length);
	return MLNil;
}

ML_METHOD("get", VersionStoreT, MLIntegerT) {
	ml_version_store_t *Store = (ml_version_store_t *)Args[0];
	CHECK_HANDLE(Store);
	size_t Index = ml_integer_value_fast(Args[1]);
	size_t Length = version_store_value_size(Store->Handle, Index);
	void *Buffer = GC_malloc_atomic(Length);
	version_store_value_get(Store->Handle, Index, Buffer, Length);
	ml_cbor_reader_t *Cbor = ml_cbor_reader(NULL, NULL, NULL);
	ml_cbor_reader_read(Cbor, Buffer, Length);
	return ml_cbor_reader_get(Cbor);
}

static int history_fn(ml_value_t *History, uint32_t Change, time_t Time, uint32_t Author) {
	ml_value_t *Tuple = ml_tuple(3);
	ml_tuple_set(Tuple, 1, ml_integer(Change));
	ml_tuple_set(Tuple, 2, ml_integer(Time));
	ml_tuple_set(Tuple, 3, ml_integer(Author));
	ml_list_put(History, Tuple);
	return 0;
}

ML_METHOD("history", VersionStoreT, MLIntegerT) {
	ml_version_store_t *Store = (ml_version_store_t *)Args[0];
	CHECK_HANDLE(Store);
	size_t Index = ml_integer_value_fast(Args[1]);
	ml_value_t *History = ml_list();
	version_store_value_history(Store->Handle, Index, (void *)history_fn, History);
	return History;
}

ML_METHOD("get", VersionStoreT, MLIntegerT, MLIntegerT) {
	ml_version_store_t *Store = (ml_version_store_t *)Args[0];
	CHECK_HANDLE(Store);
	size_t Index = ml_integer_value_fast(Args[1]);
	size_t Change = ml_integer_value_fast(Args[2]);
	size_t Length = version_store_value_revision_size(Store->Handle, Index, Change);
	void *Buffer = GC_malloc_atomic(Length);
	version_store_value_revision_get(Store->Handle, Index, Change, Buffer, Length);
	ml_cbor_reader_t *Cbor = ml_cbor_reader(NULL, NULL, NULL);
	ml_cbor_reader_read(Cbor, Buffer, Length);
	return ml_cbor_reader_get(Cbor);
}

void ml_library_entry0(ml_value_t **Slot) {
#include "ravs_init.c"
	Slot[0] = ml_module("ravs",
		"create", VersionStoreCreate,
		"open", VersionStoreOpen,
	NULL);
}
