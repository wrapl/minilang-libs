#include <minilang/ml_library.h>
#include <minilang/ml_macros.h>
#include <minilang/ml_file.h>
#include <minilang/ml_object.h>
#include <minilang/ml_stream.h>
#include <minilang/ml_logging.h>
#include <termuxgui/termuxgui.h>

static tgui_connection Conn;

ML_FUNCTION(Toast) {
	ML_CHECK_ARG_COUNT(1);
	ML_CHECK_ARG_TYPE(0, MLStringT);
	tgui_toast(Conn, ml_string_value(Args[0]), 0);
	return MLNil;
}

ML_LIBRARY_ENTRY(ui_termux) {
	if (tgui_connection_create(&Conn)) {
		ML_ERROR("TermuxError", "Error create Termux gui connection");
	}
#include "termux_init.c"
	ml_value_t *Module = Slot[0] = ml_module("termux",
		"toast", Toast,
	NULL);
	ML_RETURN(Module);
}
