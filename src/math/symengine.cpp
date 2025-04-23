#include <minilang/ml_library.h>
#include <minilang/ml_array.h>
#include <gc/gc_cpp.h>
#include <symengine/expression.h>
#include <symengine/simplify.h>
#include <symengine/solve.h>
#include <symengine/parser.h>

#undef ML_CATEGORY
#define ML_CATEGORY "math/symengine"

using namespace SymEngine;

ML_TYPE(BasicT, (), "basic");

ML_TYPE(BasicSetT, (BasicT), "basic::Set");

#define SYMENGINE_INCLUDE_ALL
#define SYMENGINE_ENUM(TYPECODE, CLASS) ML_TYPE(Basic ## CLASS ## T, (BasicT), "basic::" #CLASS);
#include <symengine/type_codes.inc>
#undef SYMENGINE_ENUM
#undef SYMENGINE_INCLUDE_ALL

struct basic_t : gc {
	ml_type_t *Type;
	RCP<const Basic> Value;

	basic_t(RCP<const Basic> Value) : Value(Value) {
		switch (Value->type_code_) {
#define SYMENGINE_INCLUDE_ALL
#define SYMENGINE_ENUM(TYPECODE, CLASS) case TYPECODE: Type = Basic ## CLASS ## T; break;
#include <symengine/type_codes.inc>
#undef SYMENGINE_ENUM
#undef SYMENGINE_INCLUDE_ALL
		default: Type = BasicT; break;
		}
	}
};

static RCP<const Basic> ml_basic_of(ml_value_t *Value) {
	typeof(ml_basic_of) *fn = (typeof(ml_basic_of) *)ml_typed_fn_get(ml_typeof(Value), (void *)ml_basic_of);
	if (fn) return fn(Value);
	return symbol("<invalid>");
}

static RCP<const Basic> ML_TYPED_FN(ml_basic_of, MLIntegerT, ml_value_t *Value) {
	return integer(ml_integer_value(Value));
}

static RCP<const Basic> ML_TYPED_FN(ml_basic_of, MLRealT, ml_value_t *Value) {
	return number(ml_real_value(Value));
}

ML_METHOD(MLRealT, BasicT) {
	basic_t *A = (basic_t *)Args[0];
	return ml_real(eval_double(*A->Value.get()));
}

#ifdef ML_COMPLEX

#include <ccomplex>
#undef I

static RCP<const Basic> ML_TYPED_FN(ml_basic_of, MLComplexT, ml_value_t *Value) {
	return number(ml_complex_value(Value));
}

ML_METHOD(MLComplexT, BasicT) {
	basic_t *A = (basic_t *)Args[0];
	std::complex<double> Value = eval_complex_double(*A->Value.get());
	return ml_complex(Value.__rep());
}

#endif

static void basic_symbol_call(ml_state_t *Caller, ml_value_t *Value, int Count, ml_value_t **Args) {
	basic_t *Basic = (basic_t *)Value;
	const Symbol *Sym = static_cast<const Symbol *>(Basic->Value.get());
	vec_basic Arg;
	for (int I = 0; I < Count; ++I) Arg.push_back(ml_basic_of(Args[I]));
	ML_RETURN(new basic_t(function_symbol(Sym->get_name(), Arg)));
}

ML_METHOD(BasicT, MLStringT) {
	try {
		return (ml_value_t *)new basic_t(parse(ml_string_value(Args[0])));
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

EXPRESSION_INFIX_METHOD(==, Eq)
EXPRESSION_INFIX_METHOD(!==, Ne)
EXPRESSION_INFIX_METHOD(<, Lt)
EXPRESSION_INFIX_METHOD(>, Gt)
EXPRESSION_INFIX_METHOD(<=, Le)
EXPRESSION_INFIX_METHOD(>=, Ge)

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

ML_METHOD("diff", BasicT, MLStringT) {
	basic_t *A = (basic_t *)Args[0];
	auto Symbol = symbol(ml_string_value(Args[1]));
	basic_t *C = new basic_t(diff(A->Value, Symbol, true));
	return (ml_value_t *)C;
}

ML_METHOD("sup", BasicSetT) {
	basic_t *A = (basic_t *)Args[0];
	basic_t *C = new basic_t(sup(*static_cast<const Set *>(A->Value.get())));
	return (ml_value_t *)C;
}

ML_METHOD("inf", BasicSetT) {
	basic_t *A = (basic_t *)Args[0];
	basic_t *C = new basic_t(inf(*static_cast<const Set *>(A->Value.get())));
	return (ml_value_t *)C;
}

struct basic_iterator_t : gc {
	ml_type_t *Type;
	std::set<RCP<const Basic>>::iterator Iter, End;
	size_t Index;
};

ML_TYPE(BasicIteratorT, (), "basic_iterator");

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

static void ML_TYPED_FN(ml_iterate, BasicFiniteSetT, ml_state_t *Caller, basic_t *Basic) {
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

ML_LIBRARY_ENTRY0(math_symengine) {
	ml_type_add_parent(BasicSymbolT, MLFunctionT);
	ml_type_add_parent(BasicEmptySetT, BasicSetT);
	ml_type_add_parent(BasicUniversalSetT, BasicSetT);
	ml_type_add_parent(BasicFiniteSetT, BasicSetT);
	ml_type_add_parent(BasicComplementT, BasicSetT);
	ml_type_add_parent(BasicConditionSetT, BasicSetT);
	ml_type_add_parent(BasicIntervalT, BasicSetT);
	ml_type_add_parent(BasicComplexesT, BasicSetT);
	ml_type_add_parent(BasicRealsT, BasicSetT);
	ml_type_add_parent(BasicIntegersT, BasicSetT);
	ml_type_add_parent(BasicNaturalsT, BasicSetT);
	ml_type_add_parent(BasicNaturals0T, BasicSetT);
	ml_type_add_parent(BasicUnionT, BasicSetT);
	ml_type_add_parent(BasicIntersectionT, BasicSetT);
	ml_type_add_parent(BasicImageSetT, BasicSetT);
	BasicSymbolT->call = basic_symbol_call;
#include "symengine_init.cpp"
	Slot[0] = (ml_value_t *)BasicT;
}
