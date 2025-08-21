#include <minilang/ml_library.h>
#include <minilang/ml_macros.h>
#include <minilang/ml_object.h>
#include <minilang/ml_stream.h>
#include <nettle/sha.h>
#include <nettle/md5.h>
#include <nettle/ripemd160.h>

#undef ML_CATEGORY
#define ML_CATEGORY "digest/hash"

#define HASH(NAME, CNAME, DEFAULT_LENGTH) \
\
typedef struct { \
	ml_type_t *Type; \
	struct CNAME ## _ctx Context[1]; \
} CNAME ## _t; \
\
ML_TYPE(NAME ## T, (MLStreamT), "hash::" #CNAME); \
/*@CNAME
*/ \
\
ML_METHOD(NAME ## T) { \
/*@CNAME
//<Key
*/ \
	CNAME ## _t *Hash = new(CNAME ## _t); \
	Hash->Type = NAME ## T; \
	CNAME ## _init(Hash->Context); \
	return (ml_value_t *)Hash; \
} \
\
ML_METHOD("update", NAME ## T, MLAddressT) { \
/*<Hash:CNAME
//<Bytes
//>CNAME
*/ \
	CNAME ## _t *Hash = (CNAME ## _t *)Args[0]; \
	CNAME ## _update(Hash->Context, \
		ml_address_length(Args[1]), \
		(uint8_t *)ml_address_value(Args[1]) \
	); \
	return (ml_value_t *)Hash; \
} \
\
static void ML_TYPED_FN(ml_stream_write, MLStreamFdT, ml_state_t *Caller, CNAME ## _t *Hash, void *Address, int Count) { \
	CNAME ## _update(Hash->Context, Count, Address); \
	ML_RETURN(ml_integer(Count)); \
} \
\
ML_METHOD("digest", NAME ## T) { \
/*<Hash:CNAME
//>address
*/ \
	CNAME ## _t *Hash = (CNAME ## _t *)Args[0]; \
	char *Buffer = snew(DEFAULT_LENGTH); \
	CNAME ## _digest(Hash->Context, DEFAULT_LENGTH, (uint8_t *)Buffer); \
	return ml_address(Buffer, DEFAULT_LENGTH); \
} \
\
ML_METHOD("digest", NAME ## T, MLIntegerT) { \
/*<Hash:CNAME
//<Length
//>address
*/ \
	CNAME ## _t *Hash = (CNAME ## _t *)Args[0]; \
	int Length = ml_integer_value(Args[1]); \
	char *Buffer = snew(Length); \
	CNAME ## _digest(Hash->Context, Length, (uint8_t *)Buffer); \
	return ml_address(Buffer, Length); \
}

HASH(MD5, md5, 16);
HASH(Ripemd160, ripemd160, 20);
HASH(SHA1, sha1, 20);
HASH(SHA224, sha224, 28);
HASH(SHA256, sha256, 32);
HASH(SHA384, sha384, 48);
HASH(SHA512, sha512, 64);

ML_LIBRARY_ENTRY0(digest_hash) {
#include "hash_init.c"
	Slot[0] = ml_module("hash",
		"md5", MD5T,
		"sha1", SHA1T,
		"sha224", SHA224T,
		"sha256", SHA256T,
		"sha384", SHA384T,
		"sha512", SHA512T,
	NULL);
}
