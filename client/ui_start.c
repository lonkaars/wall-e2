#include "i18n.h"
#include "ui.h"

void w2_ui_tab_start(bool first) {
	g_w2_ui_pad_body_scroll = 0;
	refresh();
	w2_wmvaddstr(g_w2_ui_pad_body, 0, 0, W2_UI_TAB_START_MESSAGE);
}
