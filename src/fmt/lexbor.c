#include <minilang/ml_library.h>
#include <minilang/ml_macros.h>
#include <string.h>
#include <stdio.h>
#include <lexbor/html/parser.h>

#undef ML_CATEGORY
#define ML_CATEGORY "fmt/lexbor"

ML_METHOD_ANON(Parse, "html::parse");

ML_METHOD(Parse, MLStringT) {
	lxb_html_parser_t Parser[1];
	lxb_html_parser_init(Parser);
	lxb_html_document_t *Document = lxb_html_parse(Parser, ml_string_value(Args[0]), ml_string_length(Args[0]));
	return MLNil;
}

ML_LIBRARY_ENTRY0(fmt_html) {
#include "lexbor_init.c"
	Slot[0] = ml_callable_module("html", Parse,
		"parse", Parse,
	NULL);
}
