#include <minilang/ml_library.h>
#include <minilang/ml_macros.h>
#include <minilang/ml_object.h>
#include <minilang/ml_stream.h>
#include <nettle/hmac.h>

#undef ML_CATEGORY
#define ML_CATEGORY "digest/hmac"

#define HMAC(NAME, CNAME, DEFAULT_LENGTH) \
\
typedef struct { \
	ml_type_t *Type; \
	struct hmac_ ## CNAME ## _ctx Context[1]; \
} CNAME ## _t; \
\
ML_TYPE(NAME ## T, (MLStreamT), "hmac::" #CNAME); \
/*@CNAME
*/ \
\
ML_METHOD(NAME ## T, MLAddressT) { \
/*@CNAME
//<Key
*/ \
	CNAME ## _t *HMAC = new(CNAME ## _t); \
	HMAC->Type = NAME ## T; \
	hmac_ ## CNAME ## _set_key(HMAC->Context, \
		ml_address_length(Args[0]), \
		(uint8_t *)ml_address_value(Args[0]) \
	); \
	return (ml_value_t *)HMAC; \
} \
\
ML_METHOD("update", NAME ## T, MLAddressT) { \
/*<HMAC:CNAME
//<Bytes
//>CNAME
*/ \
	CNAME ## _t *HMAC = (CNAME ## _t *)Args[0]; \
	hmac_ ## CNAME ## _update(HMAC->Context, \
		ml_address_length(Args[1]), \
		(uint8_t *)ml_address_value(Args[1]) \
	); \
	return (ml_value_t *)HMAC; \
} \
\
ML_METHOD("digest", NAME ## T) { \
/*<HMAC:CNAME
//>address
*/ \
	CNAME ## _t *HMAC = (CNAME ## _t *)Args[0]; \
	char *Buffer = snew(DEFAULT_LENGTH); \
	hmac_ ## CNAME ## _digest(HMAC->Context, DEFAULT_LENGTH, (uint8_t *)Buffer); \
	return ml_address(Buffer, DEFAULT_LENGTH); \
} \
\
ML_METHOD("digest", NAME ## T, MLIntegerT) { \
/*<HMAC:CNAME
//<Length
//>address
*/ \
	CNAME ## _t *HMAC = (CNAME ## _t *)Args[0]; \
	int Length = ml_integer_value(Args[1]); \
	char *Buffer = snew(Length); \
	hmac_ ## CNAME ## _digest(HMAC->Context, Length, (uint8_t *)Buffer); \
	return ml_address(Buffer, Length); \
}

HMAC(MD5, md5, 16);
HMAC(Ripemd160, ripemd160, 20);
HMAC(SHA1, sha1, 20);
HMAC(SHA224, sha224, 28);
HMAC(SHA256, sha256, 32);
HMAC(SHA384, sha384, 48);
HMAC(SHA512, sha512, 64);

ML_LIBRARY_ENTRY0(digest_hmac) {
#include "hmac_init.c"
	Slot[0] = ml_module("hmac",
		"md5", MD5T,
		"ripemd160", Ripemd160T,
		"sha1", SHA1T,
		"sha224", SHA224T,
		"sha256", SHA256T,
		"sha384", SHA384T,
		"sha512", SHA512T,
	NULL);
}
