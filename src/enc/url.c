#include <minilang/ml_library.h>
#include <minilang/ml_macros.h>
#include <ctype.h>

ML_FUNCTION(Encode) {
	ML_CHECK_ARG_TYPE(0, MLAddressT);
	static const char HexDigits[] = "0123456789ABCDEF";
	size_t InSize = ml_address_length(Args[0]);
	const char *InChars = ml_address_value(Args[0]);
	size_t OutSize = 0;
	for (int I = InSize; --I >= 0;) {
		char C = *InChars++;
		if (isalnum(C) || C == '-' || C == '_' || C == '.' || C == '~' || C == ' ') {
			OutSize += 1;
		} else {
			OutSize += 3;
		}
	}
	char *OutChars = snew(OutSize + 1);
	ml_value_t *Result = ml_string(OutChars, OutSize);
	InChars = ml_address_value(Args[0]);
	for (int I = InSize; --I >= 0;) {
		char C = *InChars++;
		if (isalnum(C) || C == '-' || C == '_' || C == '.' || C == '~') {
			*OutChars++ = C;
		} else if (C == ' ') {
			*OutChars++ = '+';
		} else {
			*OutChars++ = '%';
			*OutChars++ = HexDigits[(C >> 4) & 15];
			*OutChars++ = HexDigits[C & 15];
		}
	}
	*OutChars = 0;
	return Result;
}

ML_FUNCTION(Decode) {
	ML_CHECK_ARG_TYPE(0, MLAddressT);
	size_t InSize = ml_address_length(Args[0]);
	size_t OutSize = 0;
	const char *InChars = ml_address_value(Args[0]);
	for (int I = InSize; --I >= 0;) {
		char C = *InChars++;
		if (C == '%') {
			I -= 2;
			InChars += 2;
		}
		OutSize += 1;
	}
	char *OutChars = snew(OutSize + 1);
	ml_value_t *Result = ml_string(OutChars, OutSize);
	InChars = ml_address_value(Args[0]);
	for (int I = InSize; --I >= 0;) {
		char C = *InChars++;
		if (isalnum(C) || C == '-' || C == '_' || C == '.' || C == '~') {
			*OutChars++ = C;
		} else if (C == '+') {
			*OutChars++ = ' ';
		} else if (C == '%') {
			char D = 0;
			char A = *InChars++;
			switch (A) {
			case '0' ... '9': D = (A - '0') << 4; break;
			case 'A' ... 'F': D = (A + 10 - 'A') << 4; break;
			case 'a' ... 'f': D = (A + 10 - 'a') << 4; break;
			default: return ml_error("UrlError", "Invalid character %c in url", A);
			}
			char B = *InChars++;
			switch (B) {
			case '0' ... '9': D += (B - '0'); break;
			case 'A' ... 'F': D += (B + 10 - 'A'); break;
			case 'a' ... 'f': D += (B + 10 - 'a'); break;
			default: return ml_error("UrlError", "Invalid character %c in url", B);
			}
			*OutChars++ = D;
			I -= 2;
		} else {
			return ml_error("UrlError", "Invalid character %c in url", C);
		}
	}
	return Result;
}

void ml_library_entry0(ml_value_t **Slot) {
#include "url_init.c"
	Slot[0] = ml_module("url",
		"encode", Encode,
		"decode", Decode,
	NULL);
}
