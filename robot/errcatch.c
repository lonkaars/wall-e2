#include <string.h>

#include "../shared/errcatch.h"
#include "modes.h"
#include "orangutan_shim.h"
#include "sercomm.h"

// #include <stdio.h>
// unsigned int g_w2_err_index = 0;
// unsigned int g_w2_err_disp[4] = {0};

void w2_errcatch_handle_error(w2_s_error *error) {
	uint8_t severity = error->code & W2_E_TYPE_MASK;

// 	clear();
// 	g_w2_err_disp[g_w2_err_index++] = error->code;
// 	char disp[32];
// 	sprintf(disp, "%02x %02x", g_w2_err_disp[0], g_w2_err_disp[1]);
// 	print(disp);
// 	lcd_goto_xy(0, 1);
// 	sprintf(disp, "%02x %02x", g_w2_err_disp[2], g_w2_err_disp[3]);
// 	print(disp);

	// trigger emergency mode for critical errors
	if ((severity ^ W2_E_TYPE_CRIT) == 0) w2_modes_call(W2_M_HALT);

	// TODO: handle more error types
	switch (error->code) {
		case W2_E_WARN_UNCAUGHT_ERROR:
			break;
		case W2_E_WARN_OBSTACLE_DETECTED:
			break;
		case W2_E_CRIT_OBSTACLE_STUCK:
			break;
		case W2_E_WARN_MODE_HISTORY_BUFFER_IOB:
			break;
		default: {
			g_w2_error_uncaught = true;
#ifdef W2_SIM
			simwarn("Uncaught/unhandled error found with code 0x%02x", error->code);
			if (error->message_length > 0)
				fprintf(stderr, " and message \"%.*s\"", error->message_length, error->message);
			fprintf(stderr, "\n");
#endif
		}
	}

	// forward error to sercomm
	W2_CREATE_MSG_SIZE_BIN(w2_s_cmd_expt_tx,
						   sizeof(w2_s_cmd_expt_tx) + sizeof(uint8_t) * error->message_length, msg,
						   msg_bin);
	msg->opcode = W2_CMD_EXPT | W2_CMDDIR_TX;
	msg->error	= error->code;
	msg->length = error->message_length;
	memcpy(msg->message, error->message, error->message_length);

	w2_sercomm_append_msg(msg_bin);
	free(msg_bin);

	return;
}
