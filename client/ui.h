#pragma once

#include <ncurses.h>
#include <stdint.h>

#define W2_UI_UPDATE_FPS (60)

#define W2_UI_TAB_COUNT 2
typedef enum {
	W2_UI_TAB_START = 0,
	W2_UI_TAB_DIRC	= 1,
} w2_e_ui_tabs;

extern WINDOW *g_w2_ui_win;
extern WINDOW *g_w2_ui_pad_tabbar;
extern WINDOW *g_w2_ui_pad_body;
extern unsigned int g_w2_ui_width;
extern unsigned int g_w2_ui_height;
extern void (*g_w2_tab_ptrs[W2_UI_TAB_COUNT])(bool first);
extern w2_e_ui_tabs g_w2_ui_current_tab;

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

void w2_ui_tabbar_init();

void w2_ui_tab_dirc(bool first);
void w2_ui_tab_start(bool first);

void w2_wmvaddstr(WINDOW *win, unsigned int y, unsigned int x, char *str);
void w2_wmvaddnstr(WINDOW *win, unsigned int y, unsigned int x, char *str, unsigned int len);
