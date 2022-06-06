#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

#include "../shared/bin.h"
#include "../shared/protocol.h"
#include "commands.h"
#include "serial.h"
#include "setup.h"
#include "strings.h"
#include "ui.h"

// pointers for endianness check
static const uint16_t _test	 = 1;
static const uint8_t *_ptest = (uint8_t *)&_test;
uint8_t g_w2_endianness;

void w2_client_setup(int argc, char **argv) {
	if (argc < 2) {
		printf(W2_UI_CLI_USAGE, argv[0]);
		exit(1);
	}

	if (w2_serial_open(argv[1]) == 0) {
		printf(W2_UI_CLI_SERPORT_ERROR);
		exit(1);
	}

	if ((g_w2_ui_win = initscr()) == NULL) {
		printf(W2_UI_CLI_INITSCR_FAIL);
		exit(1);
	}
	noecho();
	curs_set(false);
	nodelay(g_w2_ui_win, true);

	w2_strings_init();
	w2_cmd_setup_handlers();
	w2_ui_tabbar_init();

	w2_send_info();

	g_w2_ui_width  = getmaxx(g_w2_ui_win);
	g_w2_ui_height = getmaxy(g_w2_ui_win);

	g_w2_ui_pad_tabbar = newpad(1, g_w2_ui_width);
	g_w2_ui_pad_body   = newpad(g_w2_ui_height - 5, g_w2_ui_width);
	scrollok(g_w2_ui_pad_body, true);

	// check endianness
	g_w2_endianness = *_ptest;
}
