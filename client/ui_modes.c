#include "commands.h"
#include "i18n.h"
#include "ui.h"

void w2_ui_onkey_modes(int ch) {
	if (ch == '1') w2_send_mode(W2_M_MAZE);
	if (ch == '2') w2_send_mode(W2_M_GRID);
	if (ch == '3') w2_send_mode(W2_M_HALT);
	if (ch == '4') w2_send_mode(W2_M_CHRG);
	if (ch == '5') w2_send_mode(W2_M_SPIN);
	if (ch == '6') w2_send_mode(W2_M_SCAL);

	if (ch == '0') w2_send_mode(W2_M_PREV);
}

void w2_ui_tab_modes(bool first) { w2_wmvaddstr(g_w2_ui_pad_body, 0, 0, W2_UI_MODES_INFO); }
