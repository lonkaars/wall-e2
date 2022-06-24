#include "modes.h"
#include "../shared/errcatch.h"
#include "../shared/protocol.h"
#include "../shared/util.h"
#include "sercomm.h"

#include "mode_chrg.h"
#include "mode_dirc.h"
#include "mode_grid.h"
#include "mode_halt.h"
#include "mode_maze.h"
#include "mode_scal.h"
#include "mode_spin.h"

w2_e_mode g_w2_mode_history[W2_MODE_HISTORY_BUFFER_SIZE];
uint8_t g_w2_mode_history_index = 0;
void (*g_w2_modes[W2_MODE_COUNT])();

// all of the different modi
void w2_modes_init() {
	g_w2_modes[W2_M_CHRG] = &w2_mode_chrg;
	g_w2_modes[W2_M_DIRC] = &w2_mode_dirc;
	g_w2_modes[W2_M_GRID] = &w2_mode_grid;
	g_w2_modes[W2_M_HALT] = &w2_mode_halt;
	g_w2_modes[W2_M_MAZE] = &w2_mode_maze;
	g_w2_modes[W2_M_SCAL] = &w2_mode_scal;
	g_w2_modes[W2_M_SPIN] = &w2_mode_spin;
}

void w2_modes_main() { (*g_w2_modes[g_w2_mode_history[g_w2_mode_history_index]])(); }

void w2_modes_switch(w2_e_mode new_mode, bool replace) {
	int16_t next_history_index =
		g_w2_mode_history_index + (new_mode == W2_M_PREV ? -1 : 1) * (replace - 1);
	if (next_history_index == -1 || next_history_index == W2_MODE_HISTORY_BUFFER_SIZE - 1) {
		next_history_index = W2_RANGE(0, next_history_index, W2_MODE_HISTORY_BUFFER_SIZE);
		w2_errcatch_throw(W2_E_WARN_MODE_HISTORY_BUFFER_IOB);
	}

	if (new_mode == W2_M_PREV) {
		g_w2_mode_history_index = next_history_index;
	} else {
		g_w2_mode_history_index					   = next_history_index;
		g_w2_mode_history[g_w2_mode_history_index] = new_mode;
	}

	// forward mode change to sercomm
	W2_CREATE_MSG_BIN(w2_s_cmd_mode_tx, msg, msg_bin);
	msg->opcode = W2_CMD_MODE | W2_CMDDIR_TX;
	msg->mode	= g_w2_mode_history[g_w2_mode_history_index];

	w2_sercomm_append_msg(msg_bin);
	free(msg_bin);
}

void w2_modes_call(w2_e_mode mode) { w2_modes_switch(mode, false); }

void w2_modes_swap(w2_e_mode mode) { w2_modes_switch(mode, true); }
