#include <ncurses.h>
#include <string.h>

#include "../shared/bin.h"
#include "../shared/util.h"
#include "i18n.h"
#include "main.h"
#include "strings.h"
#include "term.h"
#include "time.h"
#include "ui.h"

WINDOW *g_w2_ui_win;
WINDOW *g_w2_ui_pad_tabbar;
WINDOW *g_w2_ui_pad_statusbar;
WINDOW *g_w2_ui_pad_seperator;
WINDOW *g_w2_ui_pad_body;
int g_w2_ui_pad_body_scroll		 = 0;
unsigned int g_w2_ui_width		 = 0;
unsigned int g_w2_ui_height		 = 0;
w2_e_ui_tabs g_w2_ui_current_tab = W2_UI_TAB_START;
w2_e_ui_tabs g_w2_ui_last_tab;

void w2_wmvaddstr(WINDOW *win, unsigned int y, unsigned int x, char *str) {
	wmove(win, y, x);
	waddstr(win, str);
}

void w2_wmvaddnstr(WINDOW *win, unsigned int y, unsigned int x, char *str, unsigned int len) {
	wmove(win, y, x);
	waddnstr(win, str, len);
}

void w2_ui_switch_tab(w2_e_ui_tabs next_tab) {
	g_w2_ui_current_tab = next_tab % W2_UI_TAB_COUNT;
	wclear(g_w2_ui_pad_body);
	curs_set(false);
}

void w2_ui_key_handler() {
	int ch;
	void (*current_mode_key_handler)() = g_w2_keyhndl_ptrs[g_w2_ui_current_tab];
	while ((ch = getch()) != -1) {
		if (ch == '\t')
			w2_ui_switch_tab(g_w2_ui_current_tab + 1);
		else if (current_mode_key_handler != NULL)
			(*current_mode_key_handler)(ch);
	}
}

void w2_ui_main() {
	g_w2_ui_width  = getmaxx(g_w2_ui_win);
	g_w2_ui_height = getmaxy(g_w2_ui_win);

	w2_ui_key_handler();
	w2_ui_paint();
}

void w2_ui_paint() {
	w2_ui_paint_statusbar();
	w2_ui_paint_tabbar();
	w2_ui_paint_seperator();
	if (w2_timer_end(W2_TIMER_UPDATE) >= (1000 / W2_UI_UPDATE_FPS)) {
		(*g_w2_tab_ptrs[g_w2_ui_current_tab])(g_w2_ui_last_tab != g_w2_ui_current_tab);
		g_w2_ui_last_tab = g_w2_ui_current_tab;
		w2_timer_start(W2_TIMER_UPDATE);
	}
	prefresh(g_w2_ui_pad_statusbar, 0, 0, 0, 0, 1, g_w2_ui_width - 1);
	prefresh(g_w2_ui_pad_tabbar, 0, 0, 2, 0, 2, g_w2_ui_width - 1);
	prefresh(g_w2_ui_pad_seperator, 0, 0, 3, 0, 3, g_w2_ui_width - 1);
	prefresh(g_w2_ui_pad_body, W2_MAX(0, g_w2_ui_pad_body_scroll), 0,
			 4 - W2_MIN(0, g_w2_ui_pad_body_scroll), 0, g_w2_ui_height - 2, g_w2_ui_width - 1);
}

void w2_ui_paint_statusbar() {
	char temp[g_w2_ui_width];

	g_w2_state.connected ? sprintf(temp, W2_UI_CONN_STAT_CONNECTED ", %ims %s", g_w2_state.ping,
								   W2_UI_CONN_STAT_PING)
						 : sprintf(temp, W2_UI_CONN_STAT_DISCONNECTED);
	w2_wmvaddstr(g_w2_ui_pad_statusbar, 0, 0, temp);

	sprintf(temp, "(%s)", g_w2_state.info.build_str);
	w2_wmvaddstr(g_w2_ui_pad_statusbar, 0, g_w2_ui_width / 2 - strlen(temp) / 2, temp);

	sprintf(temp, "%s %i%%", W2_UI_BATT_STAT_BATTERY, g_w2_state.battery_level);
	w2_wmvaddstr(g_w2_ui_pad_statusbar, 0, g_w2_ui_width - strlen(temp), temp);

	sprintf(temp, "[%s]", g_w2_mode_strings[g_w2_state.mode]);
	w2_wmvaddstr(g_w2_ui_pad_statusbar, 1, 0, temp);

	sprintf(temp, "%i %s, %i %s", 0, W2_UI_EXPT_STAT_WARNINGS, 0, W2_UI_EXPT_STAT_ERRORS);
	w2_wmvaddstr(g_w2_ui_pad_statusbar, 1, g_w2_ui_width - strlen(temp), temp);
}

void w2_ui_paint_seperator() {
	char temp[g_w2_ui_width];
	for (unsigned int i = 0; i < g_w2_ui_width; i++) temp[i] = '-';
	w2_wmvaddnstr(g_w2_ui_pad_seperator, 0, 0, temp, g_w2_ui_width - 1);
}
