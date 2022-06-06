#include "strings.h"

char *g_w2_mode_strings[W2_MODE_COUNT];
char *g_w2_tab_strings[W2_UI_TAB_COUNT];

void w2_strings_modes_init() {
	g_w2_mode_strings[W2_M_CHRG] = W2_UI_MODE_CHRG;
	g_w2_mode_strings[W2_M_DIRC] = W2_UI_MODE_DIRC;
	g_w2_mode_strings[W2_M_GRID] = W2_UI_MODE_GRID;
	g_w2_mode_strings[W2_M_HALT] = W2_UI_MODE_HALT;
	g_w2_mode_strings[W2_M_MAZE] = W2_UI_MODE_MAZE;
	g_w2_mode_strings[W2_M_SCAL] = W2_UI_MODE_SCAL;
	g_w2_mode_strings[W2_M_SPIN] = W2_UI_MODE_SPIN;
}

void w2_strings_tabs_init() {
	g_w2_tab_strings[W2_UI_TAB_START] = W2_UI_TAB_LABEL_START;
	g_w2_tab_strings[W2_UI_TAB_DIRC]  = W2_UI_TAB_LABEL_DIRC;
}

void w2_strings_init() {
	w2_strings_modes_init();
	w2_strings_tabs_init();
}
