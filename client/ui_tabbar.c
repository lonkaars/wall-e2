#include <stdlib.h>
#include <string.h>

#include "ui.h"

unsigned int g_w2_ui_tabbar_scroll = 0;
unsigned int g_w2_ui_tabbar_lengths[W2_UI_TAB_COUNT];
void (*g_w2_tab_ptrs[W2_UI_TAB_COUNT])(bool first);

void w2_ui_tabbar_init() {
	g_w2_tab_ptrs[W2_UI_TAB_START] = &w2_ui_tab_start;
	g_w2_tab_ptrs[W2_UI_TAB_DIRC] = &w2_ui_tab_dirc;
}

char* w2_ui_tabbar_format_tab(char* name, bool selected) {
	char* ret_val = malloc(strlen(name) + 3);
	printf("%c%s%c", selected ? '[' : ' ', name, selected ? ']' : ' ');
	return ret_val;
}

void w2_ui_paint_tabbar() {
	char temp[g_w2_ui_width];
	sprintf(temp, "-- tab bar here --");
	w2_wmvaddstr(g_w2_ui_pad_tabbar, 0, g_w2_ui_width / 2 - strlen(temp) / 2, temp);
}
