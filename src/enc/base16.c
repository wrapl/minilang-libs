#include <minilang/ml_library.h>
#include <minilang/ml_macros.h>

ML_FUNCTION(Encode) {
	ML_CHECK_ARG_TYPE(0, MLAddressT);
	static const char HexDigits[] = "0123456789ABCDEF";
	size_t InSize = ml_address_length(Args[0]);
	size_t OutSize = 2 * InSize;
	const char *InChars = ml_address_value(Args[0]);
	char *OutChars = snew(OutSize + 1), *HP = OutChars;
	for (int I = InSize; --I >= 0;) {
		char C = *InChars++;
		*HP++ = HexDigits[(C >> 4) & 15];
		*HP++ = HexDigits[C & 15];
	}
	*HP++ = 0;
	return ml_string(OutChars, OutSize);
}

ML_FUNCTION(Decode) {
	ML_CHECK_ARG_TYPE(0, MLAddressT);
	size_t InSize = ml_address_length(Args[0]);
	size_t OutSize = (InSize + 1) / 2;
	const char *InChars = ml_address_value(Args[0]);
	char *OutChars = snew(OutSize + 1), *SP = OutChars;
	int Odd = 1;
	for (int I = InSize; --I >= 0;) {
		char C = *InChars++;
		if (C >= 'a') {
			C -= ('a' - 10);
		} else if (C >= 'A') {
			C -= ('A' - 10);
		} else {
			C -= '0';
		}
		if (Odd) {
			*SP = C << 4;
			Odd = 0;
		} else {
			*SP++ += C;
			Odd = 1;
		}
	}
	if (!Odd) SP++;
	*SP = 0;
	return ml_string(OutChars, OutSize);
}

void ml_library_entry0(ml_value_t **Slot) {
#include "base16_init.c"
	Slot[0] = ml_module("base16",
		"encode", Encode,
		"decode", Decode,
	NULL);
};
