#include <minilang/ml_library.h>
#include <minilang/ml_macros.h>
#include <SWI-Prolog.h>
#include <ctype.h>

#undef ML_CATEGORY
#define ML_CATEGORY "solver/swi-prolog"

typedef struct {
	void **Ptrs;
	int Space, Size;
} ptrset_t;

#define PTRSET_INIT {NULL, 0, 0}
#define PTRSET_INITIAL_SIZE 4

static void ptrset_insert(ptrset_t *Set, void *Ptr) {
	if (!Set->Space) {
		int Size = Set->Size + PTRSET_INITIAL_SIZE;
		void **Ptrs = anew(void *, Size);
		memcpy(Ptrs, Set->Ptrs, Set->Size * sizeof(void *));
		Ptrs[Set->Size] = Ptr;
		Set->Ptrs = Ptrs;
		Set->Size = Size;
		Set->Space += PTRSET_INITIAL_SIZE - 1;
		return;
	}
	void **Slot = Set->Ptrs;
	while (Slot[0]) ++Slot;
	Slot[0] = Ptr;
	--Set->Space;
}

static void ptrset_remove(ptrset_t *Set, void *Ptr) {
	for (void **Slot = Set->Ptrs, **Limit = Set->Ptrs + Set->Size; Slot < Limit; ++Slot) {
		if (Slot[0] == Ptr) {
			Slot[0] = NULL;
			++Set->Space;
			return;
		}
	}
}

typedef struct {
	ml_type_t *Type;
	atom_t Value;
} pl_atom_t;

typedef struct {
	ml_type_t *Type;
	functor_t Functor;
	int Count;
	ml_value_t *Args[];
} pl_term_t;

typedef struct {
	ml_type_t *Type;
	ml_value_t *Name;
} pl_variable_t;

ML_TYPE(PrologT, (), "prolog");

ML_VALUE(Prolog, PrologT);

ML_TYPE(TermT, (MLSequenceT), "prolog::term");

static void pl_atom_call(ml_state_t *Caller, pl_atom_t *Atom, int Count, ml_value_t **Args) {
	pl_term_t *Term = xnew(pl_term_t, Count, ml_value_t *);
	Term->Type = TermT;
	Term->Functor = PL_new_functor(Atom->Value, Count);
	Term->Count = Count;
	for (int I = 0; I < Count; ++I) Term->Args[I] = ml_deref(Args[I]);
	ML_RETURN(Term);
}

static functor_t CommaFunctor;

ML_METHOD(".", TermT, TermT) {
	pl_term_t *Term = xnew(pl_term_t, 2, ml_value_t *);
	Term->Type = TermT;
	Term->Functor = CommaFunctor;
	Term->Count = Count;
	Term->Args[0] = Args[0];
	Term->Args[1] = Args[1];
	return (ml_value_t *)Term;
}

ML_TYPE(AtomT, (), "prolog::atom",
	.call = (void *)pl_atom_call
);

ML_TYPE(VariableT, (), "prolog::variable");

static void pl_atom_finalize(pl_atom_t *Atom, void *Data) {
	PL_unregister_atom(Atom->Value);
}

ML_METHOD("::", PrologT, MLStringT) {
	const char *Name = ml_string_value(Args[1]);
	if (isupper(Name[0])) {
		pl_variable_t *Variable = new(pl_variable_t);
		Variable->Type = VariableT;
		Variable->Name = Args[1];
		return (ml_value_t *)Variable;
	} else {
		pl_atom_t *Atom = new(pl_atom_t);
		Atom->Type = AtomT;
		Atom->Value = PL_new_atom(Name);
		GC_register_finalizer(Atom, (GC_finalization_proc)pl_atom_finalize, Atom, NULL, NULL);
		return (ml_value_t *)Atom;
	}
}

ML_METHOD("append", MLStringBufferT, AtomT) {
	ml_stringbuffer_t *Buffer = (ml_stringbuffer_t *)Args[0];
	pl_atom_t *Atom = (pl_atom_t *)Args[1];
	size_t Length;
	const char *Name = PL_atom_nchars(Atom->Value, &Length);
	ml_stringbuffer_write(Buffer, Name, Length);
	return MLSome;
}

typedef struct query_var_t query_var_t;

struct query_var_t {
	query_var_t *Next;
	ml_value_t *Name;
	term_t Term;
};

typedef struct {
	ml_type_t *Type;
	query_var_t *Variables;
	qid_t Handle;
	int Index;
} pl_query_t;

static ml_value_t *ml_to_term(ml_value_t *Value, term_t Arg, pl_query_t *Query) {
	typeof(ml_to_term) *function = ml_typed_fn_get(ml_typeof(Value), ml_to_term);
	if (!function) return ml_error("TypeError", "Unable to convert %s to term", ml_typeof(Value)->Name);
	return function(Value, Arg, Query);
}

static ml_value_t *ML_TYPED_FN(ml_to_term, MLNilT, ml_value_t *Value, term_t Arg, pl_query_t *Query) {
	PL_put_nil(Arg);
	return NULL;
}

static ml_value_t *ML_TYPED_FN(ml_to_term, MLBooleanT, ml_value_t *Value, term_t Arg, pl_query_t *Query) {
	PL_put_bool(Arg, ml_boolean_value(Value));
	return NULL;
}

static ml_value_t *ML_TYPED_FN(ml_to_term, MLIntegerT, ml_value_t *Value, term_t Arg, pl_query_t *Query) {
	PL_put_int64(Arg, ml_integer_value(Value));
	return NULL;
}

static ml_value_t *ML_TYPED_FN(ml_to_term, MLRealT, ml_value_t *Value, term_t Arg, pl_query_t *Query) {
	PL_put_float(Arg, ml_real_value(Value));
	return NULL;
}

static ml_value_t *ML_TYPED_FN(ml_to_term, MLStringT, ml_value_t *Value, term_t Arg, pl_query_t *Query) {
	PL_put_string_nchars(Arg, ml_string_length(Value), ml_string_value(Value));
	return NULL;
}

static ml_value_t *ML_TYPED_FN(ml_to_term, MLListT, ml_value_t *Value, term_t Arg, pl_query_t *Query) {
	PL_put_nil(Arg);
	if (ml_list_length(Value)) {
		term_t Head = PL_new_term_ref();
		ML_LIST_REVERSE(Value, Iter) {
			ml_value_t *Error = ml_to_term(Iter->Value, Head, Query);
			if (Error) return Error;
			PL_cons_list(Arg, Head, Arg);
		}
	}
	return NULL;
}

static ml_value_t *ML_TYPED_FN(ml_to_term, AtomT, pl_atom_t *Atom, term_t Arg, pl_query_t *Query) {
	PL_put_atom(Arg, Atom->Value);
	return NULL;
}

static ml_value_t *ML_TYPED_FN(ml_to_term, TermT, pl_term_t *Term, term_t Arg, pl_query_t *Query) {
	term_t Args = PL_new_term_refs(Term->Count);
	for (int I = 0; I < Term->Count; ++I) {
		ml_value_t *Error = ml_to_term(Term->Args[I], Args + I, Query);
		if (Error) return Error;
	}
	PL_cons_functor_v(Arg, Term->Functor, Args);
	return NULL;
}

static ml_value_t *ML_TYPED_FN(ml_to_term, VariableT, pl_variable_t *Variable, term_t Arg, pl_query_t *Query) {
	const char *Name = ml_string_value(Variable->Name);
	int Length = ml_string_length(Variable->Name);
	for (query_var_t *Var = Query->Variables; Var; Var = Var->Next) {
		if (ml_string_length(Var->Name) != Length) continue;
		if (memcmp(ml_string_value(Var->Name), Name, Length)) continue;
		PL_put_term(Arg, Var->Term);
		return NULL;
	}
	PL_put_variable(Arg);
	query_var_t *Var = new(query_var_t);
	Var->Name = Variable->Name;
	Var->Next = Query->Variables;
	Var->Term = Arg;
	Query->Variables = Var;
	return NULL;
}

static ml_value_t *ML_TYPED_FN(ml_to_term, MLSymbolT, ml_symbol_t *Symbol, term_t Arg, pl_query_t *Query) {
	const char *Name = ml_symbol_name(Symbol);
	int Length = strlen(Name);
	for (query_var_t *Var = Query->Variables; Var; Var = Var->Next) {
		if (ml_string_length(Var->Name) != Length) continue;
		if (memcmp(ml_string_value(Var->Name), Name, Length)) continue;
		PL_put_term(Arg, Var->Term);
		return NULL;
	}
	PL_put_variable(Arg);
	query_var_t *Var = new(query_var_t);
	Var->Name = ml_string_unchecked(Name, Length);
	Var->Next = Query->Variables;
	Var->Term = Arg;
	Query->Variables = Var;
	return NULL;
}

ML_TYPE(QueryT, (), "prolog::query");

static void ML_TYPED_FN(ml_iterate, TermT, ml_state_t *Caller, pl_term_t *Term) {
	predicate_t Predicate = PL_pred(Term->Functor, NULL);
	term_t Args = PL_new_term_refs(Term->Count);
	pl_query_t *Query = new(pl_query_t);
	Query->Type = QueryT;
	for (int I = 0; I < Term->Count; ++I) {
		ml_value_t *Error = ml_to_term(Term->Args[I], Args + I, Query);
		if (Error) ML_RETURN(Error);
	}
	Query->Handle = PL_open_query(NULL, PL_Q_NORMAL, Predicate, Args);
	if (PL_next_solution(Query->Handle)) {
		Query->Index = 1;
		ML_RETURN(Query);
	} else {
		PL_close_query(Query->Handle);
		ML_RETURN(MLNil);
	}
}

static void ML_TYPED_FN(ml_iter_next, QueryT, ml_state_t *Caller, pl_query_t *Query) {
	if (PL_next_solution(Query->Handle)) {
		++Query->Index;
		ML_RETURN(Query);
	} else {
		PL_close_query(Query->Handle);
		ML_RETURN(MLNil);
	}
}

static void ML_TYPED_FN(ml_iter_key, QueryT, ml_state_t *Caller, pl_query_t *Query) {
	ML_RETURN(ml_integer(Query->Index));
}

static ml_value_t *ml_from_term(term_t Term) {
	switch (PL_term_type(Term)) {
	case PL_VARIABLE: return MLNil;
	case PL_ATOM: {
		pl_atom_t *Atom = new(pl_atom_t);
		Atom->Type = AtomT;
		PL_get_atom(Term, &Atom->Value);
		PL_register_atom(Atom->Value);
		GC_register_finalizer(Atom, (GC_finalization_proc)pl_atom_finalize, Atom, NULL, NULL);
		return (ml_value_t *)Atom;
	}
	case PL_NIL: return MLNil;
	case PL_BLOB: return MLNil;
	case PL_STRING: {
		char *String;
		size_t Length;
		PL_get_string_chars(Term, &String, &Length);
		return ml_string_copy(String, Length);
	}
	case PL_INTEGER: {
		int64_t Integer;
		PL_get_int64(Term, &Integer);
		return ml_integer(Integer);
	}
	case PL_RATIONAL: return MLNil;
		break;
	case PL_FLOAT: {
		double Real;
		PL_get_float(Term, &Real);
		return ml_real(Real);
	}
	case PL_TERM: {
		return MLNil;
	}
	case PL_LIST_PAIR: {
		ml_value_t *List = ml_list();
		term_t Head = PL_new_term_ref();
		while (PL_get_list(Term, Head, Term)) ml_list_put(List, ml_from_term(Head));
		return List;
	}
	case PL_DICT:
		return MLNil;
	}
}

static void ML_TYPED_FN(ml_iter_value, QueryT, ml_state_t *Caller, pl_query_t *Query) {
	ml_value_t *Values = ml_map();
	for (query_var_t *Var = Query->Variables; Var; Var = Var->Next) {
		ml_map_insert(Values, Var->Name, ml_from_term(Var->Term));
	}
	ML_RETURN(Values);
}

ML_LIBRARY_ENTRY0(swi_prolog) {
#include "swi-prolog_init.c"
	char *Path;
	for (size_t PathSize = 32;;) {
		Path = snew(PathSize);
		int Written = readlink("/proc/self/exe", Path, PathSize);
		if (Written < 0) {
			Slot[0] = ml_error("PathError", "Error getting executable path");
			return;
		}
		if (Written < PathSize) {
			Path[Written] = 0;
			break;
		}
		PathSize += 32;
	}
	char *Args[2] = {Path, NULL};
	PL_initialise(1, Args);
	CommaFunctor = PL_new_functor(PL_new_atom(","), 2);
	Slot[0] = Prolog;
}
