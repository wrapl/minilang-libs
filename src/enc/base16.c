#include <minilang/ml_library.h>
#include <minilang/ml_macros.h>

ML_FUNCTION(Encode) {
	ML_CHECK_ARG_TYPE(0, MLAddressT);
	static const char HexDigits[] = "0123456789ABCDEF";
	size_t InSize = ml_address_length(Args[0]);
	size_t OutSize = 2 * InSize;
	const char *InChars = ml_address_value(Args[0]);
	char *OutChars = snew(OutSize + 1);
	ml_value_t *Result = ml_string(OutChars, OutSize);
	for (int I = InSize; --I >= 0;) {
		char C = *InChars++;
		*OutChars++ = HexDigits[(C >> 4) & 15];
		*OutChars++ = HexDigits[C & 15];
	}
	*OutChars = 0;
	return Result;
}

ML_FUNCTION(Decode) {
	ML_CHECK_ARG_TYPE(0, MLAddressT);
	size_t InSize = ml_address_length(Args[0]);
	size_t OutSize = (InSize + 1) / 2;
	const char *InChars = ml_address_value(Args[0]);
	char *OutChars = snew(OutSize + 1);
	ml_value_t *Result = ml_string(OutChars, OutSize);
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
			*OutChars = C << 4;
			Odd = 0;
		} else {
			*OutChars++ += C;
			Odd = 1;
		}
	}
	if (!Odd) OutChars++;
	*OutChars = 0;
	return Result;
}

void ml_library_entry0(ml_value_t **Slot) {
#include "base16_init.c"
	Slot[0] = ml_module("base16",
		"encode", Encode,
		"decode", Decode,
	NULL);
}
