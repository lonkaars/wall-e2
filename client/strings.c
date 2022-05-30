#include "strings.h"

char *g_w2_mode_strings[W2_MODE_COUNT];

void w2_strings_modes_init() {
	g_w2_mode_strings[W2_M_CHRG] = W2_UI_MODE_CHRG;
	g_w2_mode_strings[W2_M_DIRC] = W2_UI_MODE_DIRC;
	g_w2_mode_strings[W2_M_GRID] = W2_UI_MODE_GRID;
	g_w2_mode_strings[W2_M_HALT] = W2_UI_MODE_HALT;
	g_w2_mode_strings[W2_M_LCAL] = W2_UI_MODE_LCAL;
	g_w2_mode_strings[W2_M_MAZE] = W2_UI_MODE_MAZE;
	g_w2_mode_strings[W2_M_SCAL] = W2_UI_MODE_SCAL;
	g_w2_mode_strings[W2_M_SPIN] = W2_UI_MODE_SPIN;
}

void w2_strings_init() { w2_strings_modes_init(); }
