#pragma once

#include <stdint.h>

#include "../shared/bool.h"

typedef struct {
	unsigned int width;
	unsigned int height;
	unsigned int cursor_pos;
} w2_s_ui_tty_canvas;

typedef enum {
	W2_UI_COL_BLK,
	W2_UI_COL_RED,
	W2_UI_COL_GRN,
	W2_UI_COL_YEL,
	W2_UI_COL_BLU,
	W2_UI_COL_MAG,
	W2_UI_COL_CYN,
	W2_UI_COL_WHT,
	W2_UI_COL_RST,
} w2_e_colors;

typedef enum {
	W2_UI_ALIGN_LEFT,
	W2_UI_ALIGN_CENTER,
	W2_UI_ALIGN_RIGHT,
} w2_e_alignment;

extern bool g_w2_ui_enable_color;
extern w2_s_ui_tty_canvas g_w2_ui_canvas;

/** update terminal props */
void w2_ui_update();
/** clear screen */
void w2_ui_clear();
/** draw complete ui */
void w2_ui_paint();
/** draw status bar */
void w2_ui_paint_statusbar();
/** update and paint */
void w2_ui_main();

/** get ansi color code for foreground color */
char *w2_ui_set_fg(w2_e_colors color);
/** get ansi color code for background color */
char *w2_ui_set_bg(w2_e_colors color);

/** align `text` `align` with `text` buffer length `length` */
void w2_ui_align(char *text, w2_e_alignment align, unsigned int length);

/**
 * trim spaces from `top` and overlay on top of `bottom`
 * both strings should be at least `length` long
 */
void w2_ui_overlay(char *bottom, char *top, unsigned int length);
