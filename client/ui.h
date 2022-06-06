#pragma once

#include <ncurses.h>
#include <stdint.h>

#define W2_UI_UPDATE_FPS (60)

extern WINDOW *g_w2_ui_win;
extern WINDOW *g_w2_ui_pad_tabbar;
extern WINDOW *g_w2_ui_pad_body;
extern unsigned int g_w2_ui_width;
extern unsigned int g_w2_ui_height;
extern void (*g_w2_ui_current_tab)(bool first);

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

void w2_ui_dirc(bool first);

void w2_wmvaddstr(WINDOW *win, unsigned int y, unsigned int x, char *str);
void w2_wmvaddnstr(WINDOW *win, unsigned int y, unsigned int x, char *str, unsigned int len);
