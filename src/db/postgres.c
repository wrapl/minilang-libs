#include <minilang/ml_library.h>
#include <minilang/ml_time.h>
#include <minilang/ml_uuid.h>
#include <minilang/ml_macros.h>
#include <libpq-fe.h>
#include <postgresql/server/catalog/pg_type_d.h>
#include <glib-object.h>

#undef ML_CATEGORY
#define ML_CATEGORY "db/postgres"

typedef struct connection_t connection_t;
typedef struct statement_t statement_t;
typedef struct query_t query_t;

struct connection_t {
	ml_type_t *Type;
	PGconn *Conn;
	query_t *Head, *Tail;
	ml_value_t *Result;
	int StatementId;
};

ML_TYPE(ConnectionT, (), "postgres::connection");
// A connection to a Postgresql database.

typedef ml_value_t *(*recv_fn)(const char *Value, int Length);

struct statement_t {
	ml_type_t *Type;
	connection_t *Connection;
	const char *Name;
	recv_fn *RecvFns;
	int NumFields;
};

struct query_t {
	query_t *Next;
	ml_state_t *Caller;
	const char *Name, *SQL;
	recv_fn *RecvFns;
	const char **Values;
	int *Lengths;
	int NumParams, NumFields;
};

typedef struct {
	GSource Base;
	connection_t *Connection;
} connection_source_t;

static void query_send(PGconn *Conn, query_t *Query) {
	if (Query->SQL) {
		if (Query->Name) {
			PQsendPrepare(Conn, Query->Name, Query->SQL, 0, NULL);
		} else {
			PQsendQueryParams(Conn, Query->SQL, Query->NumParams, NULL, Query->Values, Query->Lengths, NULL, 0);
		}
	} else {
		PQsendQueryPrepared(Conn, Query->Name, Query->NumParams, Query->Values, Query->Lengths, NULL, 0);
	}
}

static ml_value_t *query_param(ml_value_t *Param, const char **Value, int *Length) {
	typeof(query_param) *function = ml_typed_fn_get(ml_typeof(Param), query_param);
	if (!function) return ml_error("TypeError", "Unable to use %s in query", ml_typeof(Param)->Name);
	return function(Param, Value, Length);
}

static ml_value_t *ML_TYPED_FN(query_param, MLNilT, ml_value_t *Param, const char **Value, int *Length) {
	*Value = NULL;
	*Length = 0;
	return NULL;
}

static ml_value_t *ML_TYPED_FN(query_param, MLIntegerT, ml_value_t *Param, const char **Value, int *Length) {
	*Length = asprintf((char **)Value, "%ld", ml_integer_value(Param));
	return NULL;
}

static ml_value_t *ML_TYPED_FN(query_param, MLRealT, ml_value_t *Param, const char **Value, int *Length) {
	*Length = asprintf((char **)Value, "0x%a", ml_real_value(Param));
	return NULL;
}

static ml_value_t *ML_TYPED_FN(query_param, MLStringT, ml_value_t *Param, const char **Value, int *Length) {
	*Value = ml_string_value(Param);
	*Length = ml_string_length(Param);
	return NULL;
}

static ml_value_t *ML_TYPED_FN(query_param, MLUUIDT, ml_value_t *Param, const char **Value, int *Length) {
	char *IdString = snew(UUID_STR_LEN);
	uuid_unparse_lower(ml_uuid_value(Param), IdString);
	*Value = IdString;
	*Length = UUID_STR_LEN - 1;
	return NULL;
}

static ml_value_t *ML_TYPED_FN(query_param, MLTimeT, ml_value_t *Param, const char **Value, int *Length) {
	struct timespec Time[1];
	ml_time_value(Param, Time);
	struct tm TM = {0,};
	gmtime_r(&Time->tv_sec, &TM);
	char *Temp = snew(60);
	size_t Actual;
	unsigned long NSec = Time->tv_nsec;
	if (NSec) {
		int Width = 9;
		while (NSec % 10 == 0) {
			--Width;
			NSec /= 10;
		}
		Actual = strftime(Temp, 40, "%FT%T", &TM);
		Actual += sprintf(Temp + Actual, ".%0*luZ", Width, NSec);
	} else {
		Actual = strftime(Temp, 60, "%FT%TZ", &TM);
	}
	*Value = Temp;
	*Length = Actual;
	return NULL;
}

static ml_value_t *query_params(query_t *Query, int Count, ml_value_t **Args) {
	Query->NumParams = Count;
	const char **Values = Query->Values = anew(const char *, Count);
	int *Lengths = Query->Lengths = anew(int, Count);
	for (int I = 0; I < Count; ++I) {
		ml_value_t *Error = query_param(ml_deref(Args[I]), Values + I, Lengths + I);
		if (Error) return Error;
	}
	return NULL;
}

ML_METHODVX("query", ConnectionT, MLStringT) {
//<Connection
//<SQL
//<Arg
//>list[tuple]|nil
// Executes :mini:`SQL` on :mini:`Connection`, with arguments :mini:`Arg/i` if supplied.
// Returns a list of tuples (for ``SELECT``, etc) or :mini:`nil` for commands without results.
	connection_t *Connection = (connection_t *)Args[0];
	query_t *Query = new(query_t);
	Query->Caller = Caller;
	Query->SQL = ml_string_value(Args[1]);
	ml_value_t *Error = query_params(Query, Count - 2, Args + 2);
	if (Error) ML_RETURN(Error);
	query_t *Tail = Connection->Tail;
	Connection->Tail = Query;
	if (Tail) {
		Tail->Next = Query;
	} else {
		Connection->Head = Query;
		query_send(Connection->Conn, Query);
	}
}

ML_METHODX("prepare", ConnectionT, MLStringT) {
//<Connection
//<SQL
//>statement
// Creates a prepared statement on :mini:`Connection`.
	connection_t *Connection = (connection_t *)Args[0];
	query_t *Query = new(query_t);
	Query->Caller = Caller;
	Query->SQL = ml_string_value(Args[1]);
	asprintf((char **)&Query->Name, "S%d", ++Connection->StatementId);
	query_t *Tail = Connection->Tail;
	Connection->Tail = Query;
	if (Tail) {
		Tail->Next = Query;
	} else {
		Connection->Head = Query;
		query_send(Connection->Conn, Query);
	}
}

static void statement_call(ml_state_t *Caller, statement_t *Statement, int Count, ml_value_t **Args) {
	connection_t *Connection = Statement->Connection;
	query_t *Query = new(query_t);
	Query->Caller = Caller;
	Query->Name = Statement->Name;
	Query->RecvFns = Statement->RecvFns;
	Query->NumFields = Statement->NumFields;
	ml_value_t *Error = query_params(Query, Count, Args);
	if (Error) ML_RETURN(Error);
	query_t *Tail = Connection->Tail;
	Connection->Tail = Query;
	if (Tail) {
		Tail->Next = Query;
	} else {
		Connection->Head = Query;
		query_send(Connection->Conn, Query);
	}
}

ML_TYPE(StatementT, (MLFunctionT), "postgres::statement",
// A prepared statement. Calling a statement executes the prepared statement on the associated connection, with the provided arguments (if any).
	.call = (void *)statement_call
);

static ml_value_t *query_recv_boolean(const char *Value, int Length) {
	return Value[0] == 't' ? (ml_value_t *)MLTrue : (ml_value_t *)MLFalse;
}

static ml_value_t *query_recv_integer(const char *Value, int Length) {
	return ml_integer(strtoll(Value, NULL, 10));
}

static ml_value_t *query_recv_real(const char *Value, int Length) {
	return ml_real(strtod(Value, NULL));
}

static ml_value_t *query_recv_string(const char *Value, int Length) {
	char *Copy = snew(Length + 1);
	memcpy(Copy, Value, Length);
	Copy[Length] = 0;
	return ml_string(Copy, Length);
}

static ml_value_t *query_recv_time(const char *Value, int Length) {
	return ml_time_parse(Value, Length);
}

static ml_value_t *query_recv_uuid(const char *Value, int Length) {
	return ml_uuid_parse(Value, Length);
}

static recv_fn *query_recv_fns(PGresult *Result, int NumFields) {
	recv_fn *RecvFns = anew(recv_fn, NumFields);
	for (int I = 0; I < NumFields; ++I) {
		switch (PQftype(Result, I)) {
		case BOOLOID: RecvFns[I] = query_recv_boolean; break;
		case INT8OID:
		case INT2OID:
		case INT4OID: RecvFns[I] = query_recv_integer; break;
		case FLOAT4OID:
		case FLOAT8OID: RecvFns[I] = query_recv_real; break;
		case CHAROID:
		case BYTEAOID:
		case TEXTOID:
		case JSONOID:
		case XMLOID:
		case VARCHAROID: RecvFns[I] = query_recv_string; break;
		case DATEOID:
		case TIMEOID:
		case TIMESTAMPOID:
		case TIMESTAMPTZOID:
		case TIMETZOID: RecvFns[I] = query_recv_time; break;
		case UUIDOID: RecvFns[I] = query_recv_uuid; break;
		default: RecvFns[I] = query_recv_string; break;
		}
	}
	return RecvFns;
}

static gboolean connection_source_dispatch(connection_source_t *Source, GSourceFunc Callback, gpointer Data) {
	connection_t *Connection = Source->Connection;
	PGconn *Conn = Connection->Conn;
	PQconsumeInput(Conn);
	while (Connection->Head && !PQisBusy(Conn)) {
		PGresult *Result = PQgetResult(Conn);
		if (!Result) {
			query_t *Query = Connection->Head;
			query_t *Next = Query->Next;
			Connection->Head = Next;
			if (Next) {
				query_send(Connection->Conn, Next);
			} else {
				Connection->Tail = NULL;
			}
			Query->Caller->run(Query->Caller, Connection->Result);
		} else {
			query_t *Query = Connection->Head;
			if (Query->SQL && Query->Name) {
				if (PQresultStatus(Result) != PGRES_COMMAND_OK) {
					Connection->Result = ml_error("DatabaseError", "%s", PQerrorMessage(Conn));
				} else {
					statement_t *Statement = new(statement_t);
					Statement->Type = StatementT;
					Statement->Name = Query->Name;
					Statement->Connection = Connection;
					Statement->NumFields = PQnfields(Result);
					Statement->RecvFns = query_recv_fns(Result, Statement->NumFields);
					Connection->Result = (ml_value_t *)Statement;
				}
			} else {
				switch (PQresultStatus(Result)) {
				case PGRES_TUPLES_OK: {
					ml_value_t *Rows = Connection->Result = ml_list();
					int NumFields = PQnfields(Result);
					recv_fn *RecvFns = Query->RecvFns;
					if (!RecvFns || Query->NumFields != NumFields) RecvFns = query_recv_fns(Result, NumFields);
					for (int I = 0; I < PQntuples(Result); ++I) {
						ml_tuple_t *Row = (ml_tuple_t *)ml_tuple(NumFields);
						for (int J = 0; J < NumFields; ++J) {
							if (PQgetisnull(Result, I, J)) {
								Row->Values[J] = MLNil;
							} else {
								Row->Values[J] = RecvFns[J](PQgetvalue(Result, I, J), PQgetlength(Result, I, J));
							}
						}
						ml_list_put(Rows, (ml_value_t *)Row);
					}
					break;
				}
				case PGRES_COMMAND_OK:
					Connection->Result = MLNil;
					break;
				default:
					Connection->Result = ml_error("DatabaseError", "%s", PQerrorMessage(Conn));
					break;
				}
				PQclear(Result);
			}
		}
	}
	return G_SOURCE_CONTINUE;
}

static ml_value_t *connection(const char **Keywords, const char **Values) {
	PGconn *Conn = PQconnectdbParams(Keywords, Values, 0);
	if (PQstatus(Conn) != CONNECTION_OK) {
		const char *Message = GC_strdup(PQerrorMessage(Conn));
		PQfinish(Conn);
		return ml_error("ConnectError", Message);
	}
	int Socket = PQsocket(Conn);
	PQsetnonblocking(Conn, 1);
	connection_t *Connection = new(connection_t);
	Connection->Type = ConnectionT;
	Connection->Conn = Conn;
	static GSourceFuncs ConnectionSourceFuncs = {
		.prepare = NULL,
		.check = NULL,
		.dispatch = (void *)connection_source_dispatch,
		.finalize = NULL
	};
	connection_source_t *Source = (connection_source_t *)g_source_new(&ConnectionSourceFuncs, sizeof(connection_source_t));
	Source->Connection = Connection;
	g_source_add_unix_fd((GSource *)Source, Socket, G_IO_IN | G_IO_ERR);
	g_source_attach((GSource *)Source, NULL);
	return (ml_value_t *)Connection;
}

ML_METHOD(ConnectionT, MLMapT) {
//<Settings
//>connection
// Connects to a Postgresql database with the supplied settings.
	int NumParams = ml_map_size(Args[0]);
	const char **Keywords = anew(const char *, NumParams + 1);
	const char **Values = anew(const char *, NumParams + 1);
	int I = 0;
	ML_MAP_FOREACH(Args[0], Iter) {
		if (!ml_is(Iter->Key, MLStringT)) return ml_error("TypeError", "Parameter key must be string");
		if (!ml_is(Iter->Value, MLStringT)) return ml_error("TypeError", "Parameter value must be string");
		Keywords[I] = ml_string_value(Iter->Key);
		Values[I] = ml_string_value(Iter->Value);
		++I;
	}
	return connection(Keywords, Values);
}

ML_METHODV(ConnectionT, MLNamesT) {
//<Name,Value
//>connection
// Connects to a Postgresql database with the supplied settings.
	int NumParams = ml_names_length(Args[0]);
	const char **Keywords = anew(const char *, NumParams + 1);
	const char **Values = anew(const char *, NumParams + 1);
	int I = 0;
	ML_NAMES_FOREACH(Args[0], Iter) {
		if (!ml_is(Args[I + 1], MLStringT)) return ml_error("TypeError", "Parameter value must be string");
		Keywords[I] = ml_string_value(Iter->Value);
		Values[I] = ml_string_value(Args[I + 1]);
		++I;
	}
	return connection(Keywords, Values);
}

void ml_library_entry0(ml_value_t **Slot) {
#include "postgres_init.c"
	Slot[0] = (ml_value_t *)ConnectionT;
}
