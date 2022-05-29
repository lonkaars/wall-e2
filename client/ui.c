#include "ui.h"

void w2_ui_main() {
	w2_ui_update();
	w2_ui_paint();
}

void w2_ui_update() {
	// measure terminal width and height
}

void w2_ui_paint() { w2_ui_paint_statusbar(); }

void w2_ui_paint_statusbar() {}
