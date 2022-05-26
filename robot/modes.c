#include "modes.h"
#include "sercomm.h"

void (*g_w2_current_mode)() = &w2_mode_halt;

void w2_modes_main() { (*g_w2_current_mode)(); }

void w2_modes_switch(w2_e_mode new_mode) {
	if (new_mode == W2_M_PREV) {
		// TODO implement previous mode buffer
	} else {
		g_w2_current_mode = W2_MODES[new_mode];
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
