#include <minilang/ml_library.h>
#include <minilang/ml_time.h>
#include <minilang/ml_uuid.h>
#include <minilang/ml_macros.h>
#include <libpq-fe.h>
#include <catalog/pg_type_d.h>
#include <glib-object.h>
#include <glib-unix.h>
#include <ctype.h>
#include <errno.h>

#undef ML_CATEGORY
#define ML_CATEGORY "db/postgres"

typedef struct connection_t connection_t;
typedef struct statement_t statement_t;
typedef struct query_t query_t;

struct connection_t {
	ml_type_t *Type;
	PGconn *Conn;
	query_t *Head, *Tail;
	query_t *Waiting;
	ml_value_t *Result;
	statement_t *Statements;
	const char **Keywords, **Values;
	int StatementId, Reconnect;
	int Pipeline, NeedsFlush;
};

ML_TYPE(MLConnectionT, (), "postgres::connection");
// A connection to a Postgresql database.

typedef ml_value_t *(*recv_fn)(const char *Value, int Length);

struct statement_t {
	ml_type_t *Type;
	statement_t *Next;
	connection_t *Connection;
	const char *Name, *SQL;
	recv_fn *RecvFns;
	int NumFields;
};

struct query_t {
	query_t *Next;
	ml_state_t *Caller;
	const char *Name, *SQL;
	recv_fn *RecvFns;
	const char **Values;
	int *Lengths, *Formats;
	int NumParams, NumFields;
};

static int query_send(connection_t *Connection, query_t *Query) {
	if (!Connection->Conn) return 0;
	if (Connection->NeedsFlush) {
		if (!Connection->Waiting) Connection->Waiting = Query;
		return 0;
	}
	if (Query->SQL) {
		if (Query->Name) {
			PQsendPrepare(Connection->Conn, Query->Name, Query->SQL, 0, NULL);
		} else {
			PQsendQueryParams(Connection->Conn, Query->SQL, Query->NumParams, NULL, Query->Values, Query->Lengths, Query->Formats, 0);
		}
	} else {
		PQsendQueryPrepared(Connection->Conn, Query->Name, Query->NumParams, Query->Values, Query->Lengths, Query->Formats, 0);
	}
	if (Connection->Pipeline) {
		PQpipelineSync(Connection->Conn);
		PQsendFlushRequest(Connection->Conn);
		Connection->Waiting = Query->Next;
		Connection->NeedsFlush = PQflush(Connection->Conn);
	} else {
		PQflush(Connection->Conn);
	}
	return 1;
}

static ml_value_t *query_param(ml_value_t *Param, const char **Value, int *Length, int *Format) {
	typeof(query_param) *function = ml_typed_fn_get(ml_typeof(Param), query_param);
	if (!function) return ml_error("TypeError", "Unable to use %s in query", ml_typeof(Param)->Name);
	return function(Param, Value, Length, Format);
}

static ml_value_t *ML_TYPED_FN(query_param, MLNilT, ml_value_t *Param, const char **Value, int *Length, int *Format) {
	*Value = NULL;
	*Length = 0;
	*Format = 0;
	return NULL;
}

static ml_value_t *ML_TYPED_FN(query_param, MLIntegerT, ml_value_t *Param, const char **Value, int *Length, int *Format) {
	*Length = GC_asprintf((char **)Value, "%ld", ml_integer_value(Param));
	*Format = 0;
	return NULL;
}

static ml_value_t *ML_TYPED_FN(query_param, MLRealT, ml_value_t *Param, const char **Value, int *Length, int *Format) {
	*Length = GC_asprintf((char **)Value, "0x%a", ml_real_value(Param));
	*Format = 0;
	return NULL;
}

static ml_value_t *ML_TYPED_FN(query_param, MLAddressT, ml_value_t *Param, const char **Value, int *Length, int *Format) {
	*Value = ml_address_value(Param);
	*Length = ml_address_length(Param);
	*Format = 1;
	return NULL;
}

static ml_value_t *ML_TYPED_FN(query_param, MLStringT, ml_value_t *Param, const char **Value, int *Length, int *Format) {
	*Value = ml_string_value(Param);
	*Length = ml_string_length(Param);
	*Format = 0;
	return NULL;
}

static ml_value_t *ML_TYPED_FN(query_param, MLUUIDT, ml_value_t *Param, const char **Value, int *Length, int *Format) {
	*Value = (const char *)ml_uuid_value(Param);
	*Length = sizeof(uuid_t);
	*Format = 1;
	return NULL;
}

static ml_value_t *ML_TYPED_FN(query_param, MLTimeT, ml_value_t *Param, const char **Value, int *Length, int *Format) {
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
	*Format = 0;
	return NULL;
}

static ml_value_t *query_params(query_t *Query, int Count, ml_value_t **Args) {
	Query->NumParams = Count;
	const char **Values = Query->Values = anew(const char *, Count);
	int *Lengths = Query->Lengths = anew(int, Count);
	int *Formats = Query->Formats = anew(int, Count);
	for (int I = 0; I < Count; ++I) {
		ml_value_t *Error = query_param(ml_deref(Args[I]), Values + I, Lengths + I, Formats + I);
		if (Error) return Error;
	}
	return NULL;
}

static void query_queue(connection_t *Connection, query_t *Query) {
	query_t *Tail = Connection->Tail;
	Connection->Tail = Query;
	if (Tail) Tail->Next = Query; else Connection->Head = Query;
	if (!Tail || Connection->Pipeline) query_send(Connection, Query);
}

ML_METHODVX("query", MLConnectionT, MLStringT) {
//<Connection
//<SQL
//<Arg
//>list[tuple]|nil
// Executes :mini:`SQL` on :mini:`Connection`, with arguments :mini:`Arg/i` if supplied.
// Returns a list of tuples (for ``SELECT``, etc) or :mini:`nil` for commands without results.
	connection_t *Connection = (connection_t *)Args[0];
	if (!Connection->Conn && !Connection->Reconnect) ML_ERROR("DatabaseError", "Connection is closed");
	query_t *Query = new(query_t);
	Query->Caller = Caller;
	Query->SQL = ml_string_value(Args[1]);
	ml_value_t *Error = query_params(Query, Count - 2, Args + 2);
	if (Error) ML_RETURN(Error);
	query_queue(Connection, Query);
}

ML_METHODX("prepare", MLConnectionT, MLStringT) {
//<Connection
//<SQL
//>statement
// Creates a prepared statement on :mini:`Connection`.
	connection_t *Connection = (connection_t *)Args[0];
	if (!Connection->Conn && !Connection->Reconnect) ML_ERROR("DatabaseError", "Connection is closed");
	query_t *Query = new(query_t);
	Query->Caller = Caller;
	Query->SQL = ml_string_value(Args[1]);
	GC_asprintf((char **)&Query->Name, "S%d", ++Connection->StatementId);
	query_queue(Connection, Query);
}

static void statement_call(ml_state_t *Caller, statement_t *Statement, int Count, ml_value_t **Args) {
	connection_t *Connection = Statement->Connection;
	if (!Connection->Conn && !Connection->Reconnect) ML_ERROR("DatabaseError", "Connection is closed");
	query_t *Query = new(query_t);
	Query->Caller = Caller;
	Query->Name = Statement->Name;
	Query->RecvFns = Statement->RecvFns;
	Query->NumFields = Statement->NumFields;
	ml_value_t *Error = query_params(Query, Count, Args);
	if (Error) ML_RETURN(Error);
	query_queue(Connection, Query);
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

static uint8_t hexdigit(char C) {
	return (C <= '9') ? (C - '0') : (C - 'a' + 10);
}

static uint8_t hexbyte(const char *P) {
	return (hexdigit(P[0]) << 4) | hexdigit(P[1]);
}

static ml_value_t *query_recv_bytes(const char *Value, int Length) {
	if (Value[0] == '\\' && Value[1] == 'x') {
		int Size = (Length - 2) / 2;
		uint8_t *Copy = anew(uint8_t, Size), *Q = Copy;
		for (const char *P = Value + 2; *P; P += 2) *Q++ = hexbyte(P);
		return ml_address((void *)Copy, Size);
	} else {
		char *Copy = snew(Length + 1);
		memcpy(Copy, Value, Length);
		Copy[Length] = 0;
		return ml_string(Copy, Length);
	}
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
		case TEXTOID:
		case JSONOID:
		case XMLOID:
		case VARCHAROID: RecvFns[I] = query_recv_string; break;
		case BYTEAOID: RecvFns[I] = query_recv_bytes; break;
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

static ml_value_t *connection_connect(connection_t *Connection);

static gboolean connection_reconnect(connection_t *Connection) {
	ml_value_t *Error = connection_connect(Connection);
	if (ml_is_error(Error)) return G_SOURCE_CONTINUE;
	return G_SOURCE_REMOVE;
}

static int connection_fn(connection_t *Connection) {
	PGconn *Conn = Connection->Conn;
	if (!PQconsumeInput(Conn)) {
		if (PQstatus(Conn) != CONNECTION_OK) {
			ml_value_t *Error = ml_error("DatabaseError", "%s", PQerrorMessage(Conn));
			PQfinish(Conn);
			Connection->Conn = NULL;
			if (Connection->Reconnect) {
				g_timeout_add(Connection->Reconnect, (GSourceFunc)connection_reconnect, Connection);
			} else {
				query_t *Query = Connection->Head;
				if (Query) {
					if (!(Connection->Head = Query->Next)) Connection->Tail = NULL;
					ml_state_schedule(Query->Caller, Error);
				}
			}
			return 0;
		}
	}
	int ShouldRetry = errno != EAGAIN && errno != EWOULDBLOCK;
	while (Connection->Head && !PQisBusy(Conn)) {
		query_t *Query = Connection->Head;
		PGresult *Result = PQgetResult(Conn);
		if (!Result) {
			query_t *Next = Query->Next;
			Connection->Head = Next;
			if (!Next) {
				Connection->Tail = NULL;
			} else if (!Connection->Pipeline) {
				query_send(Connection, Next);
			}
			ml_state_schedule(Query->Caller, Connection->Result);
		} else {
			ExecStatusType Status = PQresultStatus(Result);
			if (Status == PGRES_PIPELINE_SYNC) {
			} else if (Query->SQL && Query->Name) {
				if (Status != PGRES_COMMAND_OK) {
					Connection->Result = ml_error("DatabaseError", "%s", PQerrorMessage(Conn));
				} else {
					statement_t *Statement = new(statement_t);
					Statement->Type = StatementT;
					Statement->Next = Connection->Statements;
					Connection->Statements = Statement;
					Statement->Name = Query->Name;
					Statement->SQL = Query->SQL;
					Statement->Connection = Connection;
					Statement->NumFields = PQnfields(Result);
					Statement->RecvFns = query_recv_fns(Result, Statement->NumFields);
					Connection->Result = (ml_value_t *)Statement;
				}
			} else {
				switch (Status) {
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
			}
			PQclear(Result);
		}
	}
	if (ShouldRetry) return connection_fn(Connection);
	return 1;
}

static gboolean gio_connection_fn(gint Socket, GIOCondition Condition, connection_t *Connection) {
	return connection_fn(Connection) ? G_SOURCE_CONTINUE : G_SOURCE_REMOVE;
}

static int connection_pipeline_fn(connection_t *Connection) {
	PGconn *Conn = Connection->Conn;
	if (!PQconsumeInput(Conn)) {
		if (PQstatus(Conn) != CONNECTION_OK) {
			ml_value_t *Error = ml_error("DatabaseError", "%s", PQerrorMessage(Conn));
			PQfinish(Conn);
			Connection->Conn = NULL;
			if (Connection->Reconnect) {
				g_timeout_add(Connection->Reconnect, (GSourceFunc)connection_reconnect, Connection);
			} else {
				query_t *Query = Connection->Head;
				if (Query) {
					if (!(Connection->Head = Query->Next)) Connection->Tail = NULL;
					ml_state_schedule(Query->Caller, Error);
				}
			}
			return 0;
		}
	}
	int ShouldRetry = errno != EAGAIN && errno != EWOULDBLOCK;
	while (Connection->Head && !PQisBusy(Conn)) {
		PGresult *Result = PQgetResult(Conn);
		if (Result) {
			ExecStatusType Status = PQresultStatus(Result);
			if (Status == PGRES_PIPELINE_SYNC) {
			} else {
				query_t *Query = Connection->Head;
				query_t *Next = Query->Next;
				Connection->Head = Next;
				if (!Next) Connection->Tail = NULL;
				ml_value_t *Value = MLNil;
				if (Query->SQL && Query->Name) {
					if (Status != PGRES_COMMAND_OK) {
						Value = ml_error("DatabaseError", "%s", PQerrorMessage(Conn));
					} else {
						statement_t *Statement = new(statement_t);
						Statement->Type = StatementT;
						Statement->Next = Connection->Statements;
						Connection->Statements = Statement;
						Statement->Name = Query->Name;
						Statement->SQL = Query->SQL;
						Statement->Connection = Connection;
						Statement->NumFields = PQnfields(Result);
						Statement->RecvFns = query_recv_fns(Result, Statement->NumFields);
						Value = (ml_value_t *)Statement;
					}
				} else {
					switch (Status) {
					case PGRES_TUPLES_OK: {
						Value = ml_list();
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
							ml_list_put(Value, (ml_value_t *)Row);
						}
						break;
					}
					case PGRES_COMMAND_OK:
						Value = MLNil;
						break;
					default:
						Value = ml_error("DatabaseError", "%s", PQerrorMessage(Conn));
						break;
					}
				}
				PQclear(Result);
				ml_state_schedule(Query->Caller, Value);
			}
		}
	}
	if (ShouldRetry) return connection_pipeline_fn(Connection);
	if (Connection->NeedsFlush) {
		Connection->NeedsFlush = PQflush(Connection->Conn);
		query_t *Waiting = Connection->Waiting;
		Connection->Waiting = NULL;
		while (Waiting && query_send(Connection, Waiting)) Waiting = Waiting->Next;
	}
	return 1;
}

static gboolean gio_connection_pipeline_fn(gint Socket, GIOCondition Condition, connection_t *Connection) {
	return connection_pipeline_fn(Connection) ? G_SOURCE_CONTINUE : G_SOURCE_REMOVE;
}

static ml_value_t *connection_connect(connection_t *Connection) {
	PGconn *Conn = PQconnectdbParams(Connection->Keywords, Connection->Values, 0);
	if (PQstatus(Conn) != CONNECTION_OK) {
		ml_value_t *Error = ml_error("DatabaseError", "%s", PQerrorMessage(Conn));
		PQfinish(Conn);
		return Error;
	}
	Connection->Conn = Conn;
	for (statement_t *Statement = Connection->Statements; Statement; Statement = Statement->Next) {
		PGresult *Result = PQprepare(Conn, Statement->Name, Statement->SQL, 0, NULL);
		if (PQresultStatus(Result) != PGRES_COMMAND_OK) {
			PQclear(Result);
			ml_value_t *Error = ml_error("DatabaseError", "%s", PQerrorMessage(Conn));
			PQfinish(Conn);
			return Error;
		}
	}
	PQsetnonblocking(Conn, 1);
	if (Connection->Pipeline) {
		PQenterPipelineMode(Conn);
		query_t *Waiting = Connection->Head;
		while (Waiting && query_send(Connection, Waiting)) Waiting = Waiting->Next;
	} else if (Connection->Head) {
		query_send(Connection, Connection->Head);
	}
	GSource *Source = g_unix_fd_source_new(PQsocket(Conn), G_IO_IN | G_IO_ERR);
	if (Connection->Pipeline) {
		g_source_set_callback(Source, (void *)gio_connection_pipeline_fn, Connection, NULL);
	} else {
		g_source_set_callback(Source, (void *)gio_connection_fn, Connection, NULL);
	}
	g_source_attach(Source, NULL);
	return (ml_value_t *)Connection;
}

ML_METHOD(MLConnectionT, MLMapT) {
//<Settings
//>connection
// Connects to a Postgresql database with the supplied settings.
	int NumParams = ml_map_size(Args[0]);
	const char **Keywords = anew(const char *, NumParams + 1);
	const char **Values = anew(const char *, NumParams + 1);
	int I = 0, Pipeline = 0, Reconnect = 0;
	ML_MAP_FOREACH(Args[0], Iter) {
		if (!ml_is(Iter->Key, MLStringT)) return ml_error("TypeError", "Parameter key must be string");
		if (!ml_is(Iter->Value, MLStringT)) return ml_error("TypeError", "Parameter value must be string");
		const char *Keyword = ml_string_value(Iter->Key);
		const char *Value = ml_string_value(Iter->Value);
		if (!strcmp(Keyword, "pipeline")) {
			Pipeline = !strcmp(Value, "true");
		} else if (!strcmp(Keyword, "reconnect")) {
			char *End;
			Reconnect = 1000 * strtod(Value, &End);
		} else {
			if (!ml_is(Iter->Value, MLStringT)) return ml_error("TypeError", "Parameter value must be string");
			Keywords[I] = Keyword;
			Values[I] = Value;
			++I;
		}
	}
	connection_t *Connection = new(connection_t);
	Connection->Type = MLConnectionT;
	Connection->Keywords = Keywords;
	Connection->Values = Values;
	Connection->Pipeline = Pipeline;
	Connection->Reconnect = Reconnect;
	return connection_connect(Connection);
}

ML_METHODV(MLConnectionT, MLNamesT) {
//<Name,Value
//>connection
// Connects to a Postgresql database with the supplied settings.
	int NumParams = ml_names_length(Args[0]);
	const char **Keywords = anew(const char *, NumParams + 1);
	const char **Values = anew(const char *, NumParams + 1);
	int I = 0, J = 1, Pipeline = 0, Reconnect = 0;
	ML_NAMES_FOREACH(Args[0], Iter) {
		if (!ml_is(Args[J], MLStringT)) return ml_error("TypeError", "Parameter value must be string");
		const char *Keyword = ml_string_value(Iter->Value);
		const char *Value = ml_string_value(Args[J++]);
		if (!strcmp(Keyword, "pipeline")) {
			Pipeline = !strcmp(Value, "true");
		} else if (!strcmp(Keyword, "reconnect")) {
			char *End;
			Reconnect = 1000 * strtod(Value, &End);
		} else {
			Keywords[I] = Keyword;
			Values[I] = Value;
			++I;
		}
	}
	connection_t *Connection = new(connection_t);
	Connection->Type = MLConnectionT;
	Connection->Keywords = Keywords;
	Connection->Values = Values;
	Connection->Pipeline = Pipeline;
	Connection->Reconnect = Reconnect;
	return connection_connect(Connection);
}

ML_METHOD("reconnect", MLConnectionT, MLNumberT) {
	connection_t *Connection = (connection_t *)Args[0];
	Connection->Reconnect = 1000 * ml_real_value(Args[1]);
	return (ml_value_t *)Connection;
}

ML_METHOD("connect", MLConnectionT) {
	return connection_connect((connection_t *)Args[0]);
}

ML_METHOD("connected", MLConnectionT) {
	connection_t *Connection = (connection_t *)Args[0];
	return Connection->Conn ? (ml_value_t *)Connection : MLNil;
}

ML_LIBRARY_ENTRY0(db_postgres) {
#include "postgres_init.c"
	Slot[0] = (ml_value_t *)MLConnectionT;
}
