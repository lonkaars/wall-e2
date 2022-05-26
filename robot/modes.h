#pragma once

#include "../shared/consts.h"

#include "mode_chrg.h"
#include "mode_dirc.h"
#include "mode_grid.h"
#include "mode_halt.h"
#include "mode_lcal.h"
#include "mode_maze.h"
#include "mode_scal.h"
#include "mode_spin.h"

/**
 * mode logic
 *
 * executes mode in g_w2_current_mode
 */
void w2_modes_main();

/** mode constants */
typedef enum {
	W2_M_PREV = -1,
	W2_M_MAZE = 0,
	W2_M_GRID = 1,
	W2_M_HALT = 2,
	W2_M_LCAL = 3,
	W2_M_CHRG = 4,
	W2_M_DIRC = 5,
	W2_M_SPIN = 6,
	W2_M_SCAL = 7,
} w2_e_mode;

/** array that maps w2_e_mode to mode function pointers */
static const void(*const W2_MODES[]) = {
	&w2_mode_maze, &w2_mode_grid, &w2_mode_grid, &w2_mode_halt,
	&w2_mode_chrg, &w2_mode_dirc, &w2_mode_spin, &w2_mode_scal,
};

/** switch current mode (allow switching back to previous mode) */
void w2_modes_call(w2_e_mode mode);
/** switch current mode (replace current mode keeping history index) */
void w2_modes_swap(w2_e_mode mode);
