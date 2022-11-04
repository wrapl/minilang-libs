#include "roaring.h"
#include <minilang/minilang.h>
#include <minilang/ml_macros.h>
#include <minilang/ml_cbor.h>

#undef ML_CATEGORY
#define ML_CATEGORY "util/bitset"

typedef struct {
	ml_type_t *Type;
	roaring_bitmap_t *Value;
} bitset_t;

ML_TYPE(MLBitsetT, (MLSequenceT), "bitset");

static void bitset_finalize(void *Bitset, void *Data) {
	roaring_bitmap_free(((bitset_t *)Bitset)->Value);
}

ML_METHOD(MLBitsetT) {
//>bitset
	bitset_t *Bitset = new(bitset_t);
	Bitset->Type = MLBitsetT;
	Bitset->Value = roaring_bitmap_create();
	GC_register_finalizer(Bitset, bitset_finalize, NULL, NULL, NULL);
	return (ml_value_t *)Bitset;
}

ML_METHOD("set", MLBitsetT, MLIntegerT) {
	bitset_t *Bitset = (bitset_t *)Args[0];
	roaring_bitmap_add(Bitset->Value, ml_integer_value(Args[1]));
	return (ml_value_t *)Bitset;
}

ML_METHOD("set", MLBitsetT, MLIntegerRangeT) {
	bitset_t *Bitset = (bitset_t *)Args[0];
	ml_integer_range_t *Range = (ml_integer_range_t *)Args[1];
	roaring_bitmap_add_range_closed(Bitset->Value, Range->Start, Range->Limit);
	return (ml_value_t *)Bitset;
}

ML_METHOD("unset", MLBitsetT, MLIntegerT) {
	bitset_t *Bitset = (bitset_t *)Args[0];
	roaring_bitmap_remove(Bitset->Value, ml_integer_value(Args[1]));
	return (ml_value_t *)Bitset;
}

ML_METHOD("unset", MLBitsetT, MLIntegerRangeT) {
	bitset_t *Bitset = (bitset_t *)Args[0];
	ml_integer_range_t *Range = (ml_integer_range_t *)Args[1];
	roaring_bitmap_remove_range_closed(Bitset->Value, Range->Start, Range->Limit);
	return (ml_value_t *)Bitset;
}

ML_METHOD("append", MLStringBufferT, MLBitsetT) {
	ml_stringbuffer_t *Buffer = (ml_stringbuffer_t *)Args[0];
	bitset_t *Bitset = (bitset_t *)Args[1];
	roaring_uint32_iterator_t Iter[1];
	roaring_init_iterator(Bitset->Value, Iter);
	if (!Iter->has_value) {
		ml_stringbuffer_write(Buffer, "{}", 8);
		return MLSome;
	}
	ml_stringbuffer_write(Buffer, "<bitset", 7);
	uint32_t Lo = Iter->current_value, Hi = Lo;
	roaring_advance_uint32_iterator(Iter);
	while (Iter->has_value) {
		if (Iter->current_value == Hi + 1) {
			Hi += 1;
		} else {
			if (Hi > Lo) {
				ml_stringbuffer_printf(Buffer, " %u .. %u", Lo, Hi);
			} else {
				ml_stringbuffer_printf(Buffer, " %u", Lo);
			}
			Hi = Lo = Iter->current_value;
		}
		roaring_advance_uint32_iterator(Iter);
	}
	if (Hi > Lo) {
		ml_stringbuffer_printf(Buffer, " %u .. %u", Lo, Hi);
	} else {
		ml_stringbuffer_printf(Buffer, " %u", Lo);
	}
	ml_stringbuffer_write(Buffer, "}", 1);
	return MLSome;
}

typedef struct {
	ml_type_t *Type;
	roaring_uint32_iterator_t Iter[1];
	uint32_t Index;
} bitset_iter_t;

ML_TYPE(BitsetIterT, (), "bitset::iter");
//!internal

static void ML_TYPED_FN(ml_iterate, MLBitsetT, ml_state_t *Caller, bitset_t *Bitset) {
	if (!roaring_bitmap_get_cardinality(Bitset->Value)) ML_RETURN(MLNil);
	bitset_iter_t *Iter = new(bitset_iter_t);
	Iter->Type = BitsetIterT;
	Iter->Index = 1;
	roaring_init_iterator(Bitset->Value, Iter->Iter);
	ML_RETURN(Iter);
}

static void ML_TYPED_FN(ml_iter_next, BitsetIterT, ml_state_t *Caller, bitset_iter_t *Iter) {
	roaring_advance_uint32_iterator(Iter->Iter);
	if (!Iter->Iter->has_value) ML_RETURN(MLNil);
	++Iter->Index;
	ML_RETURN(Iter);
}

static void ML_TYPED_FN(ml_iter_key, BitsetIterT, ml_state_t *Caller, bitset_iter_t *Iter) {
	ML_RETURN(ml_integer(Iter->Index));
}

static void ML_TYPED_FN(ml_iter_value, BitsetIterT, ml_state_t *Caller, bitset_iter_t *Iter) {
	ML_RETURN(ml_integer(Iter->Iter->current_value));
}

static ml_value_t *ML_TYPED_FN(ml_cbor_write, MLBitsetT, ml_cbor_writer_t *Writer, bitset_t *Bitset) {
	ml_cbor_write_tag(Writer, ML_CBOR_TAG_OBJECT);
	ml_cbor_write_array(Writer, 2);
	ml_cbor_write_string(Writer, strlen("bitset"));
	ml_cbor_write_raw(Writer, "bitset", strlen("bitset"));
	size_t Size = roaring_bitmap_portable_size_in_bytes(Bitset->Value);
	ml_cbor_write_bytes(Writer, Size);
	char *Bytes = snew(Size);
	roaring_bitmap_portable_serialize(Bitset->Value, Bytes);
	ml_cbor_write_raw(Writer, Bytes, Size);
	return NULL;
}

ML_FUNCTION(DecodeBitset) {
	ML_CHECK_ARG_COUNT(1);
	ML_CHECK_ARG_TYPE(0, MLAddressT);
	roaring_bitmap_t *Value = roaring_bitmap_portable_deserialize_safe(ml_address_value(Args[0]), ml_address_length(Args[0]));
	if (!Value) return ml_error("DecodeError", "Error decoding bitmap data");
	bitset_t *Bitset = new(bitset_t);
	Bitset->Type = MLBitsetT;
	Bitset->Value = Value;
	return (ml_value_t *)Bitset;
}

void ml_library_entry0(ml_value_t **Slot) {
#include "bitset_init.c"
	ml_cbor_default_object("bitset", (ml_value_t *)DecodeBitset);
	Slot[0] = (ml_value_t *)MLBitsetT;
}
