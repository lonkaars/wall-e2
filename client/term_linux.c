#ifdef W2_HOST_LINUX

#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>

#include "term.h"
#include "ui.h"

void w2_term_raw_mode() {
	fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);
	struct termios term;
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHO | ICANON);
	term.c_cc[VTIME] = 0;
	term.c_cc[VMIN] = 1;
	tcsetattr(STDIN_FILENO, 0, &term);
}

void w2_term_props() {
	struct winsize window;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &window);

	g_w2_ui_canvas.width = window.ws_col;
	g_w2_ui_canvas.height = window.ws_row;
}

#endif
