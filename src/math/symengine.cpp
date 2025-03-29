#include <minilang/ml_library.h>
#include <minilang/ml_array.h>
#include <gc/gc_cpp.h>
#include <symengine/expression.h>
#include <symengine/simplify.h>
#include <symengine/solve.h>

using namespace SymEngine;

ML_TYPE(BasicT, (), "basic");

ML_TYPE(BasicSetT, (BasicT, MLSequenceT), "basic::set");

struct basic_t : gc {
	ml_type_t *Type;
	RCP<const Basic> Value;

	basic_t(RCP<const Basic> Value) : Value(Value) {
		if (is_a_Set(*Value.get())) {
			Type = BasicSetT;
		} else {
			Type = BasicT;
		}
	}
};

ML_METHOD(BasicT, MLStringT) {
	try {
		Expression Expr(ml_string_value(Args[0]));
		return (ml_value_t *)(new basic_t(Expr.get_basic()));
	} catch (std::exception &E) {
		return ml_error("SymengineError", "%s", E.what());
	}
}

struct ml_streambuf : std::basic_streambuf<char> {
	ml_stringbuffer_t *Buffer;

	ml_streambuf(ml_stringbuffer_t *Buffer) : Buffer(Buffer) {}

	std::streamsize xsputn(const char_type *Str, std::streamsize N) {
		return ml_stringbuffer_write(Buffer, Str, N);
	}

	int_type overflow(int_type C) {
		ml_stringbuffer_put(Buffer, C);
		return C;
	}
};

ML_METHOD("append", MLStringBufferT, BasicT) {
	ml_stringbuffer_t *Buffer = (ml_stringbuffer_t *)Args[0];
	basic_t *Basic = (basic_t *)Args[1];
	ml_streambuf StreamBuffer(Buffer);
	std::basic_ostream Stream(&StreamBuffer);
	Stream << *Basic->Value.get();
	return MLSome;
}

#define EXPRESSION_INFIX_METHOD(OP, FUN) \
\
ML_METHOD(#OP, BasicT, BasicT) { \
	basic_t *A = (basic_t *)Args[0]; \
	basic_t *B = (basic_t *)Args[1]; \
	basic_t *C = new basic_t(FUN(A->Value, B->Value)); \
	return (ml_value_t *)C; \
}  \
\
ML_METHOD(#OP, MLRealT, BasicT) { \
	double A = ml_real_value(Args[0]); \
	basic_t *B = (basic_t *)Args[1]; \
	basic_t *C = new basic_t(FUN(number(A), B->Value)); \
	return (ml_value_t *)C; \
}  \
\
ML_METHOD(#OP, BasicT, MLRealT) { \
	basic_t *A = (basic_t *)Args[0]; \
	double B = ml_real_value(Args[1]); \
	basic_t *C = new basic_t(FUN(A->Value, number(B))); \
	return (ml_value_t *)C; \
}

EXPRESSION_INFIX_METHOD(+, add)
EXPRESSION_INFIX_METHOD(-, sub)
EXPRESSION_INFIX_METHOD(*, mul)
EXPRESSION_INFIX_METHOD(/, div)

ML_METHOD("^", BasicT, BasicT) {
	basic_t *A = (basic_t *)Args[0];
	basic_t *B = (basic_t *)Args[1];
	basic_t *C = new basic_t(pow(A->Value, B->Value));
	return (ml_value_t *)C;
}

ML_METHOD("^", MLRealT, BasicT) {
	double A = ml_real_value(Args[0]);
	basic_t *B = (basic_t *)Args[1];
	basic_t *C = new basic_t(pow(A, B->Value));
	return (ml_value_t *)C; \
}

ML_METHOD("^", BasicT, MLRealT) {
	basic_t *A = (basic_t *)Args[0];
	double B = ml_real_value(Args[1]);
	basic_t *C = new basic_t(pow(A->Value, B));
	return (ml_value_t *)C;
}

ML_METHOD("simplify", BasicT) {
	basic_t *A = (basic_t *)Args[0];
	basic_t *C = new basic_t(simplify(A->Value, nullptr));
	return (ml_value_t *)C;
}

ML_METHOD("expand", BasicT) {
	basic_t *A = (basic_t *)Args[0];
	basic_t *C = new basic_t(expand(A->Value));
	return (ml_value_t *)C;
}

ML_METHOD("solve", BasicT, MLStringT) {
	basic_t *A = (basic_t *)Args[0];
	auto Symbol = symbol(ml_string_value(Args[1]));
	basic_t *C = new basic_t(solve(A->Value, Symbol));
	return (ml_value_t *)C;
}

struct basic_iterator_t : gc {
	ml_type_t *Type;
	std::set<RCP<const Basic>>::iterator Iter, End;
	size_t Index;
};

ML_TYPE(BasicIteratorT, (), "basic_iterator");

static void ML_TYPED_FN(ml_iterate, BasicSetT, ml_state_t *Caller, basic_t *Basic) {
	const FiniteSet *Set = dynamic_cast<const FiniteSet *>(Basic->Value.get());
	if (Set) {
		const auto Container = Set->get_container();
		if (Container.empty()) ML_RETURN(MLNil);
		basic_iterator_t *Iterator = new basic_iterator_t;
		Iterator->Type = BasicIteratorT;
		Iterator->Iter = Container.begin();
		Iterator->End = Container.end();
		Iterator->Index = 1;
		ML_RETURN(Iterator);
	}
	ML_RETURN(MLNil);
}

static void ML_TYPED_FN(ml_iter_next, BasicIteratorT, ml_state_t *Caller, basic_iterator_t *Iter) {
	if (++Iter->Iter == Iter->End) ML_RETURN(MLNil);
	++Iter->Index;
	ML_RETURN(Iter);
}

static void ML_TYPED_FN(ml_iter_key, BasicIteratorT, ml_state_t *Caller, basic_iterator_t *Iter) {
	ML_RETURN(ml_integer(Iter->Index));
}

static void ML_TYPED_FN(ml_iter_value, BasicIteratorT, ml_state_t *Caller, basic_iterator_t *Iter) {
	basic_t *C = new basic_t(*Iter->Iter);
	ML_RETURN(C);
}

ML_LIBRARY_ENTRY0(math_symengine) {
#include "symengine_init.cpp"
	Slot[0] = (ml_value_t *)BasicT;
}
