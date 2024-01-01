#include <minilang/ml_library.h>
#include <minilang/ml_macros.h>
#include <minilang/ml_stream.h>
#include <minilang/ml_object.h>
#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>
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

#define MODE(VALUE) #VALUE, VALUE

ML_ENUM2(TerminalIFlagT, "terminal::iflag",
	MODE(IGNBRK),
	MODE(BRKINT),
	MODE(IGNPAR),
	MODE(PARMRK),
	MODE(INPCK),
	MODE(ISTRIP),
	MODE(INLCR),
	MODE(IGNCR),
	MODE(ICRNL),
	MODE(IUCLC),
	MODE(IXON),
	MODE(IXANY),
	MODE(IXOFF),
	MODE(IMAXBEL),
	MODE(IUTF8)
);

ML_ENUM2(TerminalOFlagT, "terminal::oflag",
	MODE(OPOST),
	MODE(OLCUC),
	MODE(ONLCR),
	MODE(OCRNL),
	MODE(ONOCR),
	MODE(ONLRET),
	MODE(OFILL),
	MODE(OFDEL),
	MODE(NLDLY),
	MODE(NL0),
	MODE(NL1),
	MODE(CRDLY),
	MODE(CR0),
	MODE(CR1),
	MODE(CR2),
	MODE(CR3),
	MODE(TABDLY),
	MODE(TAB0),
	MODE(TAB1),
	MODE(TAB2),
	MODE(TAB3),
	MODE(BSDLY),
	MODE(BS0),
	MODE(BS1),
	MODE(FFDLY),
	MODE(FF0),
	MODE(FF1),
	MODE(VTDLY),
	MODE(VT0),
	MODE(VT1),
	MODE(XTABS)
);

ML_ENUM2(TerminalCFlagT, "terminal::cflag",
	MODE(CSIZE),
	MODE(CS5),
	MODE(CS6),
	MODE(CS7),
	MODE(CS8),
	MODE(CSTOPB),
	MODE(CREAD),
	MODE(PARENB),
	MODE(PARODD),
	MODE(HUPCL),
	MODE(CLOCAL)//,
	//MODE(ADDRB)
);

ML_ENUM2(TerminalLFlagT, "terminal::lflag",
	MODE(ISIG),
	MODE(ICANON),
	MODE(XCASE),
	MODE(ECHO),
	MODE(ECHOE),
	MODE(ECHOK),
	MODE(ECHONL),
	MODE(NOFLSH),
	MODE(TOSTOP),
	MODE(ECHOCTL),
	MODE(ECHOPRT),
	MODE(ECHOKE),
	MODE(FLUSHO),
	MODE(PENDIN),
	MODE(IEXTEN),
	MODE(EXTPROC)
);

#define FLAG_METHODS(UPPER, LOWER) \
\
ML_METHOD("get", TerminalT, Terminal ## UPPER ## FlagT) { \
	int Fd = ml_fd_stream_fd(Args[0]); \
	struct termios Termios; \
	tcgetattr(Fd, &Termios); \
	return ml_boolean(Termios.c_ ## LOWER ## flag & ml_enum_value_value(Args[1])); \
} \
\
ML_METHOD("set", TerminalT, Terminal ## UPPER ## FlagT, MLBooleanT) { \
	int Fd = ml_fd_stream_fd(Args[0]); \
	struct termios Termios; \
	tcgetattr(Fd, &Termios); \
	if (ml_boolean_value(Args[2])) { \
		Termios.c_ ## LOWER ## flag |= ml_enum_value_value(Args[1]); \
	} else { \
		Termios.c_ ## LOWER ## flag &= ~ml_enum_value_value(Args[1]); \
	}  \
	tcsetattr(Fd, TCSAFLUSH, &Termios); \
	return Args[0]; \
}

FLAG_METHODS(I, i)
FLAG_METHODS(O, o)
FLAG_METHODS(C, c)
FLAG_METHODS(L, l)

static struct termios SavedIn;
static struct termios SavedOut;
static struct termios SavedErr;

static void restore_termios() {
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &SavedIn);
	tcsetattr(STDOUT_FILENO, TCSAFLUSH, &SavedOut);
	tcsetattr(STDERR_FILENO, TCSAFLUSH, &SavedErr);
}

ML_LIBRARY_ENTRY0(io_terminal) {
#include "terminal_init.c"
	stringmap_insert(TerminalT->Exports, "iflag", TerminalIFlagT);
	stringmap_insert(TerminalT->Exports, "oflag", TerminalOFlagT);
	stringmap_insert(TerminalT->Exports, "cflag", TerminalCFlagT);
	stringmap_insert(TerminalT->Exports, "lflag", TerminalLFlagT);
	if (isatty(STDIN_FILENO)) tcgetattr(STDIN_FILENO, &SavedIn);
	if (isatty(STDOUT_FILENO)) tcgetattr(STDOUT_FILENO, &SavedOut);
	if (isatty(STDERR_FILENO)) tcgetattr(STDERR_FILENO, &SavedErr);
	atexit(restore_termios);
	stringmap_insert(TerminalT->Exports, "Stdin", ml_fd_stream(isatty(STDIN_FILENO) ? TerminalT : MLStreamFdT, STDIN_FILENO));
	stringmap_insert(TerminalT->Exports, "Stdout", ml_fd_stream(isatty(STDOUT_FILENO) ? TerminalT : MLStreamFdT, STDOUT_FILENO));
	stringmap_insert(TerminalT->Exports, "Stderr", ml_fd_stream(isatty(STDERR_FILENO) ? TerminalT : MLStreamFdT, STDERR_FILENO));
	Slot[0] = (ml_value_t *)TerminalT;
}
