#include <minilang/ml_library.h>
#include <minilang/ml_macros.h>
#include <float.h>

typedef struct {
	ml_type_t *Type;
	ml_value_t *Unscaled;
	int32_t Scale;
} ml_decimal_t;

static long ml_decimal_hash(ml_decimal_t *Value, ml_hash_chain_t *Chain) {
	return ml_hash_chain(Value->Unscaled, Chain) + Value->Scale;
}

ML_TYPE(MLDecimalT, (MLNumberT), "decimal",
	.hash = (void *)ml_decimal_hash
);

ML_METHOD("unscaled", MLDecimalT) {
	ml_decimal_t *Decimal = (ml_decimal_t *)Args[0];
	return Decimal->Unscaled;
}

ML_METHOD("scaled", MLDecimalT) {
	ml_decimal_t *Decimal = (ml_decimal_t *)Args[0];
	return ml_integer(Decimal->Scale);
}

ML_METHOD(MLDecimalT, MLIntegerT, MLIntegerT) {
	ml_decimal_t *Decimal = new(ml_decimal_t);
	Decimal->Type = MLDecimalT;
	Decimal->Unscaled = Args[0];
	Decimal->Scale = ml_integer_value(Args[1]);
	return (ml_value_t *)Decimal;
}

ML_METHOD(MLDecimalT, MLIntegerT) {
	ml_decimal_t *Decimal = new(ml_decimal_t);
	Decimal->Type = MLDecimalT;
	Decimal->Unscaled = Args[0];
	Decimal->Scale = 0;
	return (ml_value_t *)Decimal;
}

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

ML_METHOD(MLDecimalT, MLRealT) {
	char Temp[DBL_DIG + 10];
	int Length = sprintf(Temp, "%." TOSTRING(DBL_DIG) "g", ml_real_value(Args[0]));
	int Scale = 0;
	char *Tail = strchr(Temp, 'e');
	if (Tail) {
		Scale = -strtol(Tail + 1, NULL, 10);
		*Tail = 0;
	} else {
		Tail = Temp + Length;
	}
	char *Point = strchr(Temp, '.');
	if (Point) {
		int Digits = Tail - (Point + 1);
		Scale += Digits;
		memmove(Point, Point + 1, Digits);
		*--Tail = 0;
	}
	ml_decimal_t *Decimal = new(ml_decimal_t);
	Decimal->Type = MLDecimalT;
	Decimal->Unscaled = ml_integer_parse(Temp);
	Decimal->Scale = Scale;
	return (ml_value_t *)Decimal;
}

ML_METHOD("append", MLStringBufferT, MLDecimalT) {
	ml_stringbuffer_t *Buffer = (ml_stringbuffer_t *)Args[0];
	ml_decimal_t *Decimal = (ml_decimal_t *)Args[1];
	ml_stringbuffer_t TempBuffer[1] = {ML_STRINGBUFFER_INIT};
	ml_stringbuffer_simple_append(TempBuffer, Decimal->Unscaled);
	int Scale = Decimal->Scale;
	if (Scale > 0) {
		if (Scale >= TempBuffer->Length) {
			ml_stringbuffer_write(Buffer, "0.", strlen("0."));
			for (int I = Scale - TempBuffer->Length; --I >= 0;) ml_stringbuffer_put(Buffer, '0');
			ml_stringbuffer_drain(TempBuffer, Buffer, (void *)ml_stringbuffer_write);
		} else {
			int WholeDigits = TempBuffer->Length - Scale;
			while (WholeDigits > 0) {
				int N = ml_stringbuffer_reader(TempBuffer, 0);
				if (N >= WholeDigits) {
					ml_stringbuffer_write(Buffer, TempBuffer->Head->Chars + TempBuffer->Start, WholeDigits);
					ml_stringbuffer_reader(TempBuffer, WholeDigits);
					break;
				}
				ml_stringbuffer_write(Buffer, TempBuffer->Head->Chars + TempBuffer->Start, N);
				ml_stringbuffer_reader(TempBuffer, N);
				WholeDigits -= N;
			}
			ml_stringbuffer_put(Buffer, '.');
			ml_stringbuffer_drain(TempBuffer, Buffer, (void *)ml_stringbuffer_write);
		}
	} else if (Scale < 0) {
		ml_stringbuffer_drain(TempBuffer, Buffer, (void *)ml_stringbuffer_write);
		for (int I = Scale; ++I <= 0;) ml_stringbuffer_put(Buffer, '0');
	} else {
		ml_stringbuffer_drain(TempBuffer, Buffer, (void *)ml_stringbuffer_write);
	}
	return MLSome;
}

ML_LIBRARY_ENTRY0(math_decimal) {
#include "decimal_init.c"
	Slot[0] = (ml_value_t *)MLDecimalT;
}
