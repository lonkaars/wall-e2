#include <string.h>
#include <ncurses.h>

#include "../shared/bin.h"
#include "../shared/util.h"
#include "i18n.h"
#include "main.h"
#include "term.h"
#include "ui.h"

WINDOW *g_w2_ui_win;
unsigned int g_w2_ui_width = 0;
unsigned int g_w2_ui_height = 0;

void w2_ui_main() {
	g_w2_ui_width = getmaxx(g_w2_ui_win);
	g_w2_ui_height = getmaxy(g_w2_ui_win);

	w2_ui_paint();
}

void w2_ui_paint() {
	w2_ui_paint_statusbar();
	refresh();
}

void w2_ui_paint_statusbar() {
	char temp[g_w2_ui_width + 1];
	sprintf(temp, "%s, %ims %s",
			g_w2_state.connected ? W2_UI_CONN_STAT_CONNECTED : W2_UI_CONN_STAT_DISCONNECTED,
			g_w2_state.ping,
			W2_UI_CONN_STAT_PING);
	mvaddstr(0, 0, temp);

	sprintf(temp, "(%s)", g_w2_state.info.build_str);
	mvaddstr(0, g_w2_ui_width / 2 - strlen(temp) / 2, temp);

	sprintf(temp, "%s %i%%", W2_UI_BATT_STAT_BATTERY, g_w2_state.battery_level);
	mvaddstr(0, g_w2_ui_width - strlen(temp), temp);

	sprintf(temp, "[mode 0x%02x]", g_w2_state.mode);
	mvaddstr(1, 0, temp);

	sprintf(temp, "%i %s, %i %s",
			0, W2_UI_EXPT_STAT_WARNINGS,
			0, W2_UI_EXPT_STAT_ERRORS);
	mvaddstr(1, g_w2_ui_width - strlen(temp), temp);

	w2_ui_paint_tabbar();

	for (unsigned int i = 0; i < g_w2_ui_width; i++) temp[i] = '-';
	temp[g_w2_ui_width] = 0;
	mvaddstr(3, 0, temp);
}

void w2_ui_paint_tabbar() {
	char temp[g_w2_ui_width];
	sprintf(temp, "-- tab bar here --");
	mvaddstr(2, g_w2_ui_width / 2 - strlen(temp) / 2, temp);
}

