#include <minilang/ml_library.h>
#include <minilang/ml_macros.h>

#undef ML_CATEGORY
#define ML_CATEGORY "enc/base16"

ML_FUNCTION(Encode) {
//<Address
//>string
	ML_CHECK_ARG_COUNT(1);
	ML_CHECK_ARG_TYPE(0, MLAddressT);
	static const unsigned char HexDigits[] = "0123456789ABCDEF";
	size_t InSize = ml_address_length(Args[0]);
	size_t OutSize = 2 * InSize;
	const unsigned char *InChars = (const unsigned char *)ml_address_value(Args[0]);
	char *OutChars = snew(OutSize + 1), *Out = OutChars;
	for (int I = InSize; --I >= 0;) {
		unsigned char C = *InChars++;
		*Out++ = HexDigits[(C >> 4) & 15];
		*Out++ = HexDigits[C & 15];
	}
	*Out = 0;
	return ml_string_unchecked(OutChars, OutSize);
}

ML_FUNCTION(Decode) {
//<String
//>address
	ML_CHECK_ARG_COUNT(1);
	ML_CHECK_ARG_TYPE(0, MLAddressT);
	size_t InSize = ml_address_length(Args[0]);
	size_t OutSize = (InSize + 1) / 2;
	const char *InChars = ml_address_value(Args[0]);
	char *OutChars = snew(OutSize + 1);
	unsigned char *Out = (unsigned char *)OutChars;
	int Odd = 1;
	for (int I = InSize; --I >= 0;) {
		unsigned char C = *InChars++;
		if (C >= 'a') {
			C -= ('a' - 10);
		} else if (C >= 'A') {
			C -= ('A' - 10);
		} else {
			C -= '0';
		}
		if (Odd) {
			*Out = C << 4;
			Odd = 0;
		} else {
			*Out++ += C;
			Odd = 1;
		}
	}
	if (!Odd) Out++;
	*Out = 0;
	return ml_address(OutChars, OutSize);
}

ML_LIBRARY_ENTRY0(enc_base16) {
#include "base16_init.c"
	Slot[0] = ml_module("base16",
		"encode", Encode,
		"decode", Decode,
	NULL);
}
