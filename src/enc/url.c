#include <minilang/ml_library.h>
#include <minilang/ml_macros.h>
#include <ctype.h>

#undef ML_CATEGORY
#define ML_CATEGORY "enc/url"

ML_FUNCTION(Encode) {
//<Address
//>string
	ML_CHECK_ARG_COUNT(1);
	ML_CHECK_ARG_TYPE(0, MLAddressT);
	static const char HexDigits[] = "0123456789ABCDEF";
	size_t InSize = ml_address_length(Args[0]);
	const unsigned char *InChars = (const unsigned char *)ml_address_value(Args[0]);
	size_t OutSize = 0;
	for (int I = InSize; --I >= 0;) {
		unsigned char C = *InChars++;
		if (isalnum(C) || C == '-' || C == '_' || C == '.' || C == '~' || C == ' ') {
			OutSize += 1;
		} else {
			OutSize += 3;
		}
	}
	char *OutChars = snew(OutSize + 1), *Out = OutChars;
	InChars = (const unsigned char *)ml_address_value(Args[0]);
	for (int I = InSize; --I >= 0;) {
		unsigned char C = *InChars++;
		if (isalnum(C) || C == '-' || C == '_' || C == '.' || C == '~') {
			*Out++ = C;
		} else if (C == ' ') {
			*Out++ = '+';
		} else {
			*Out++ = '%';
			*Out++ = HexDigits[(C >> 4) & 15];
			*Out++ = HexDigits[C & 15];
		}
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
	unsigned char *Out = (unsigned char *)OutChars;
	InChars = ml_address_value(Args[0]);
	for (int I = InSize; --I >= 0;) {
		char C = *InChars++;
		if (isalnum(C) || C == '-' || C == '_' || C == '.' || C == '~') {
			*Out++ = C;
		} else if (C == '+') {
			*Out++ = ' ';
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
			*Out++ = D;
			I -= 2;
		} else {
			return ml_error("UrlError", "Invalid character %c in url", C);
		}
	}
	return ml_string_unchecked(OutChars, OutSize);
}

ML_LIBRARY_ENTRY0(enc_url) {
#include "url_init.c"
	Slot[0] = ml_module("url",
		"encode", Encode,
		"decode", Decode,
	NULL);
}
