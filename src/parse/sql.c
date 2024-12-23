#include <libpg_query/pg_query.h>
#include <minilang/ml_library.h>
#include <minilang/ml_macros.h>
#include <minilang/ml_object.h>
#include <minilang/ml_json.h>

ML_METHOD_ANON(SqlParse, "sql::parse");

ML_METHOD(SqlParse, MLStringT) {
	PgQueryParseResult Parse = pg_query_parse(ml_string_value(Args[0]));
	ml_value_t *Result;
	if (Parse.error) {
		Result = ml_error("SQLError", "%s", Parse.error->message);
	} else {
		Result = ml_json_decode(Parse.parse_tree, strlen(Parse.parse_tree));
	}
	pg_query_free_parse_result(Parse);
	return Result;
}

ML_LIBRARY_ENTRY0(parse_sql) {
#include "sql_init.c"
	Slot[0] = ml_module("sql",
		"parse", SqlParse,
	NULL);
}
