#pragma once

#include <ncurses.h>
#include <stdint.h>

extern WINDOW *g_w2_ui_win;
extern unsigned int g_w2_ui_width;
extern unsigned int g_w2_ui_height;

/** update terminal props */
void w2_ui_update();
/** clear screen */
void w2_ui_clear();
/** draw complete ui */
void w2_ui_paint();
/** update and paint */
void w2_ui_main();

/** draw status bar */
void w2_ui_paint_statusbar();
/** draw tab bar */
void w2_ui_paint_tabbar();
