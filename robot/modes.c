#include "modes.h"
#include "../shared/errcatch.h"
#include "../shared/protocol.h"
#include "../shared/util.h"
#include "sercomm.h"

/** function pointer to current mode */
// static void (*g_w2_current_mode)() = &w2_mode_halt;

static void (*g_w2_mode_history[W2_MODE_HISTORY_BUFFER_SIZE])();
static uint8_t g_w2_mode_history_index = 0;

void w2_modes_main() { (*g_w2_mode_history[g_w2_mode_history_index])(); }

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
		g_w2_mode_history[g_w2_mode_history_index] = W2_MODES[new_mode];
	}

	// forward mode change to sercomm
	size_t msg_size		  = sizeof(w2_s_cmd_mode_tx);
	w2_s_cmd_mode_tx *msg = malloc(msg_size);
	msg->opcode			  = W2_CMD_MODE | W2_CMDDIR_TX;
	msg->mode			  = (uint8_t)new_mode;
	w2_s_bin *msg_bin	  = w2_bin_s_alloc(msg_size, (uint8_t *)msg);
	w2_sercomm_append_msg(msg_bin);
	free(msg);
	free(msg_bin);
}

void w2_modes_call(w2_e_mode mode) { w2_modes_switch(mode, false); }

void w2_modes_swap(w2_e_mode mode) { w2_modes_switch(mode, true); }
