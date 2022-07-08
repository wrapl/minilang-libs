#include <minilang/ml_library.h>
#include <minilang/ml_macros.h>
#include <minilang/ml_object.h>

#include <dqlite.h>

typedef struct {
	ml_type_t *Type;
	dqlite_node *Handle;
} ml_dqlite_t;

extern ml_type_t MLDqliteT[];

ML_FUNCTION(MLDqlite) {
	ML_CHECK_ARG_COUNT(3);
	ML_CHECK_ARG_TYPE(0, MLIntegerT);
	ML_CHECK_ARG_TYPE(1, MLStringT);
	ML_CHECK_ARG_TYPE(2, MLStringT);
	ml_dqlite_t *Dqlite = new(ml_dqlite_t);
	Dqlite->Type = MLDqliteT;
	if (dqlite_node_create(ml_integer_value(Args[0]), ml_string_value(Args[1]), ml_string_value(Args[2]), &Dqlite->Handle)) {
		return ml_error("DqliteError", "Error creating node");
	}
	return (ml_value_t *)Dqlite;
}

ML_TYPE(MLDqliteT, (), "dqlite",
	.Constructor = (ml_value_t *)MLDqlite
);

ML_METHOD("start", MLDqliteT) {
	ml_dqlite_t *Dqlite = (ml_dqlite_t *)Args[0];
	if (dqlite_node_start(Dqlite->Handle)) {
		return ml_error("DqliteError", "Error starting node");
	}
	return (ml_value_t *)Dqlite;
}

ML_METHOD("stop", MLDqliteT) {
	ml_dqlite_t *Dqlite = (ml_dqlite_t *)Args[0];
	if (dqlite_node_stop(Dqlite->Handle)) {
		return ml_error("DqliteError", "Error starting node");
	}
	return (ml_value_t *)Dqlite;
}

void ml_library_entry0(ml_value_t **Slot) {
#include "dqlite_init.c"
	Slot[0] = (ml_value_t *)MLDqliteT;
}
