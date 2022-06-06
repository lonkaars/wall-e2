#pragma once

#define W2_MODE_COUNT 7

/** mode constants */
typedef enum {
	W2_M_PREV = -1,
	W2_M_MAZE = 0,
	W2_M_GRID = 1,
	W2_M_HALT = 2,
	W2_M_CHRG = 3,
	W2_M_DIRC = 4,
	W2_M_SPIN = 5,
	W2_M_SCAL = 6,
} w2_e_mode;
