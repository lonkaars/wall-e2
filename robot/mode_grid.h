#pragma once

/** @file mode_grid.h */

/**
 * warehouse mode
 *
 * processes orders from the order buffer
 */
void w2_mode_grid();

extern int g_w2_transition;

void w2_crosswalk_stroll();

typedef enum { W2_ORT_NORTH, W2_ORT_EAST, W2_ORT_SOUTH, W2_ORT_WEST } w2_e_orientation;

// enum w2_e_section { mazeMode, gridMode, chargeMode } g_w2_parcour_mode;

typedef struct {
	int x;
	int y;
} w2_s_grid_coordinate;

extern w2_s_grid_coordinate g_w2_order[4];
