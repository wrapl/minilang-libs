#include <minilang/ml_library.h>
#include <minilang/ml_macros.h>
#include <minilang/ml_object.h>
#include <minilang/ml_stream.h>
#include <nettle/blowfish.h>

#undef ML_CATEGORY
#define ML_CATEGORY "crypto/bcrypt"

ML_FUNCTION(Hash) {
//<Key
//<Spec
//<Rounds?:integer
//<Salt?:address
	ML_CHECK_ARG_COUNT(2);
	ML_CHECK_ARG_TYPE(0, MLAddressT);
	ML_CHECK_ARG_TYPE(1, MLStringT);
	char *Dest = snew(BLOWFISH_BCRYPT_HASH_SIZE);
	int Log2Rounds = -1;
	const uint8_t *Salt = NULL;
	if (Count > 2) {
		ML_CHECK_ARG_TYPE(2, MLIntegerT);
		Log2Rounds = ml_integer_value(Args[2]);
	}
	if (Count > 3) {
		ML_CHECK_ARG_TYPE(3, MLAddressT);
		if (ml_address_length(Args[3]) < BLOWFISH_BCRYPT_BINSALT_SIZE) return ml_error("ShapeError", "Salt must have at least %d bytes", BLOWFISH_BCRYPT_BINSALT_SIZE);
		Salt = (const uint8_t *)ml_address_value(Args[3]);
	}
	if (blowfish_bcrypt_hash((uint8_t *)Dest, ml_address_length(Args[0]), (const uint8_t *)ml_address_value(Args[0]), ml_string_length(Args[1]), (const uint8_t *)ml_string_value(Args[1]), Log2Rounds, Salt)) {
		Dest[BLOWFISH_BCRYPT_HASH_SIZE - 1] = 0;
		return ml_string(Dest, BLOWFISH_BCRYPT_HASH_SIZE - 1);
	} else {
		return ml_error("CryptoError", "Error creating bcrypt hash");
	}
}

ML_FUNCTION(Verify) {
//<Key
//<Hash
	ML_CHECK_ARG_COUNT(2);
	ML_CHECK_ARG_TYPE(0, MLAddressT);
	ML_CHECK_ARG_TYPE(1, MLAddressT);
	if (blowfish_bcrypt_verify(ml_address_length(Args[0]), (const uint8_t *)ml_address_value(Args[0]), ml_address_length(Args[1]), (const uint8_t *)ml_address_value(Args[1]))) {
		return MLSome;
	} else {
		return MLNil;
	}
}

ML_LIBRARY_ENTRY0(crypto_bcrypt) {
#include "bcrypt_init.c"
	Slot[0] = ml_module("bcrypt",
		"hash", Hash,
		"verify", Verify,
	NULL);
}
