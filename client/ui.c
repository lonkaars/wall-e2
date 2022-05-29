#include <string.h>

#include "../shared/bin.h"
#include "../shared/util.h"
#include "i18n.h"
#include "main.h"
#include "term.h"
#include "ui.h"

w2_s_ui_tty_canvas g_w2_ui_canvas;

void w2_ui_main() {
	w2_ui_update();
	w2_ui_paint();
}

void w2_ui_update() { w2_term_props(); }

void w2_ui_paint() { w2_ui_paint_statusbar(); }

void w2_ui_align(char *text, w2_e_alignment align, unsigned int length) {
	unsigned int padding = 0;

	switch (align) {
		case W2_UI_ALIGN_LEFT: {
			break;
		}
		case W2_UI_ALIGN_CENTER: {
			unsigned int middle = length / 2;
			unsigned int offset = strlen(text) / 2;
			padding				= W2_MAX(0, middle - offset);
			break;
		}
		case W2_UI_ALIGN_RIGHT: {
			unsigned int right	= length;
			unsigned int offset = strlen(text);
			padding				= W2_MAX(0, right - offset);
			break;
		}
	}

	char *temp = calloc(length, 1);
	sprintf(temp, "%*s%s", padding, "", text);
	memcpy(text, temp, length);
	free(temp);
}

char *w2_ui_pt_sb_con_sts() {
	char *connected =
		g_w2_state.connected ? W2_UI_CONN_STAT_CONNECTED : W2_UI_CONN_STAT_DISCONNECTED;
	char *out = calloc(g_w2_ui_canvas.width, 1);
	sprintf(out, "%s, %ims %s", connected, g_w2_state.ping, W2_UI_CONN_STAT_PING);
	w2_ui_align(out, W2_UI_ALIGN_LEFT, g_w2_ui_canvas.width);
	return out;
}
char *w2_ui_pt_sb_ver_num() {
	char *out = calloc(g_w2_ui_canvas.width, 1);
	sprintf(out, "(%s)", g_w2_state.info.build_str);
	w2_ui_align(out, W2_UI_ALIGN_CENTER, g_w2_ui_canvas.width);
	return out;
}
char *w2_ui_pt_sb_bat_sts() {
	char *out = calloc(g_w2_ui_canvas.width, 1);
	sprintf(out, "%s %i%%", W2_UI_BATT_STAT_BATTERY, g_w2_state.battery_level);
	w2_ui_align(out, W2_UI_ALIGN_RIGHT, g_w2_ui_canvas.width);
	return out;
}

void w2_ui_nullsub(char *str, unsigned int length) {
	for (int i = 0; i < length; i++)
		if (str[i] == 0x00) str[i] = ' ';
}

void w2_ui_overlay(char *bottom, char *top, unsigned int length) {
	w2_ui_nullsub(bottom, length);
	w2_ui_nullsub(top, length);

	unsigned int start = 0;
	for (int i = 0; i < length; i++) {
		start = i;
		if (top[start] != ' ') break;
	}
	unsigned int stop = 0;
	for (int i = 0; i < length; i++) {
		stop = length - i;
		if (top[stop] != ' ') break;
	}

	for (int i = 0; i < length; i++) {
		if (i >= start && i <= stop) bottom[i] = top[i];
	}
}

// char* w2_ui_pt_sb_logic_mode() {}
// char* w2_ui_pt_sb_exceptions() {}
// char* w2_ui_pt_sb_tabbar() {}

void w2_ui_paint_statusbar() {
	char top_row[g_w2_ui_canvas.width];

	char *con_sts = w2_ui_pt_sb_con_sts();
	char *ver_num = w2_ui_pt_sb_ver_num();
	char *bat_sts = w2_ui_pt_sb_bat_sts();

	w2_ui_overlay(top_row, con_sts, g_w2_ui_canvas.width);
	w2_ui_overlay(top_row, ver_num, g_w2_ui_canvas.width);
	w2_ui_overlay(top_row, bat_sts, g_w2_ui_canvas.width);

	printf("%s", top_row);

	free(con_sts);
	free(ver_num);
	free(bat_sts);

	// w2_ui_pt_sb_connection_status();
	// w2_ui_pt_sb_connection_status();
	// w2_ui_pt_sb_connection_status();
	printf("\n");
}
