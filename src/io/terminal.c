#include <minilang/ml_library.h>
#include <minilang/ml_macros.h>
#include <minilang/ml_stream.h>
#include <unistd.h>
#include <termio.h>
#include <errno.h>

ML_TYPE(TerminalT, (MLStreamFdT), "terminal");

ML_METHOD("winsize", TerminalT) {
	int Fd = ml_fd_stream_fd(Args[0]);
	struct winsize Size[1];
	if (ioctl(Fd, TIOCGWINSZ, Size)) return ml_error("IoctlError", "%s", strerror(errno));
	return ml_tuplev(4,
		ml_integer(Size->ws_col), ml_integer(Size->ws_row),
		ml_integer(Size->ws_xpixel), ml_integer(Size->ws_ypixel)
	);
}

ML_LIBRARY_ENTRY0(io_terminal) {
#include "terminal_init.c"
	stringmap_insert(TerminalT->Exports, "Stdin", ml_fd_stream(isatty(STDIN_FILENO) ? TerminalT : MLStreamFdT, STDIN_FILENO));
	stringmap_insert(TerminalT->Exports, "Stdout", ml_fd_stream(isatty(STDOUT_FILENO) ? TerminalT : MLStreamFdT, STDOUT_FILENO));
	stringmap_insert(TerminalT->Exports, "Stderr", ml_fd_stream(isatty(STDERR_FILENO) ? TerminalT : MLStreamFdT, STDERR_FILENO));
	Slot[0] = (ml_value_t *)TerminalT;
}
