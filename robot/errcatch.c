#include <string.h>

#include "../shared/errcatch.h"
#include "modes.h"
#include "orangutan_shim.h"
#include "sercomm.h"

void w2_errcatch_handle_error(w2_s_error *error) {
	uint8_t severity = error->code & W2_E_TYPE_MASK;

	// trigger emergency mode for critical errors
	if ((severity ^ W2_E_TYPE_CRIT) == 0) w2_modes_call(W2_M_HALT);

	// TODO: handle more error types
	switch (error->code) {
		case W2_E_WARN_UNCAUGHT_ERROR: {
			break;
		}
		default: {
			g_w2_error_uncaught = true;
#ifdef W2_SIM
			simwarn("Uncaught/unhandled error found with code 0x%02x\n", error->code);
#endif
		}
	}

	// forward error to sercomm
	size_t msg_size		  = sizeof(w2_s_cmd_expt_tx) + sizeof(uint8_t) * error->message_length;
	w2_s_cmd_expt_tx *msg = malloc(msg_size);
	msg->opcode			  = W2_CMD_EXPT | W2_CMDDIR_TX;
	msg->error			  = error->code;
	msg->length			  = error->message_length;
	memcpy(msg->message, error->message, error->message_length);
	w2_s_bin *msg_bin = w2_bin_s_alloc(msg_size, (uint8_t *)msg);
	w2_sercomm_append_msg(msg_bin);
	free(msg);
	free(msg_bin);

	return;
}
