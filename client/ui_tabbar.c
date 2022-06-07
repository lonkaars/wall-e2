#include <stdlib.h>
#include <string.h>

#include "strings.h"
#include "ui.h"

unsigned int g_w2_ui_tabbar_scroll = 0;
unsigned int g_w2_ui_tabbar_lengths[W2_UI_TAB_COUNT];
void (*g_w2_tab_ptrs[W2_UI_TAB_COUNT])(bool first);
void (*g_w2_keyhndl_ptrs[W2_UI_TAB_COUNT])(int key);

void w2_ui_tabbar_init() {
	g_w2_tab_ptrs[W2_UI_TAB_START]	   = &w2_ui_tab_start;
	g_w2_tab_ptrs[W2_UI_TAB_ERRCATCH]  = &w2_ui_tab_errcatch;
	g_w2_keyhndl_ptrs[W2_UI_TAB_START] = &w2_ui_onkey_errcatch;
	g_w2_tab_ptrs[W2_UI_TAB_DIRC]	   = &w2_ui_tab_dirc;
	g_w2_keyhndl_ptrs[W2_UI_TAB_DIRC]  = &w2_ui_onkey_dirc;
}

void w2_ui_paint_tabbar() {
	wmove(g_w2_ui_pad_tabbar, 0, 0);
	for (unsigned int i = 0; i < W2_UI_TAB_COUNT; i++) {
		g_w2_ui_tabbar_lengths[i] += 2 + strlen(g_w2_tab_strings[i]);

		wprintw(g_w2_ui_pad_tabbar, " %c%s%c", g_w2_ui_current_tab == i ? '[' : ' ',
				g_w2_tab_strings[i], g_w2_ui_current_tab == i ? ']' : ' ');
	}
	wprintw(g_w2_ui_pad_tabbar, " ");
}
