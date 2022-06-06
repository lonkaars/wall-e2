#include "i18n.h"
#include "ui.h"

void w2_ui_tab_start(bool first) {
	refresh();
	w2_wmvaddstr(g_w2_ui_pad_body, 0, 0, W2_UI_TAB_START_MESSAGE);
}
