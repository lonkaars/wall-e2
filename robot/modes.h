#pragma once

/** @file modes.h */

#include <stdint.h>

#include "../shared/consts.h"
#include "../shared/modes.h"

extern w2_e_mode g_w2_mode_history[W2_MODE_HISTORY_BUFFER_SIZE];
extern uint8_t g_w2_mode_history_index;

/** setup g_w2_modes array */
void w2_modes_init();

/**
 * mode logic
 *
 * executes mode in g_w2_current_mode
 */
void w2_modes_main();

/** switch current mode (allow switching back to previous mode) */
void w2_modes_call(w2_e_mode mode);
/** switch current mode (replace current mode keeping history index) */
void w2_modes_swap(w2_e_mode mode);
