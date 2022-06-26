#include <stdio.h>
#include <string.h>

#include "../shared/errcatch.h"
#include "modes.h"
#include "orangutan_shim.h"
#include "sercomm.h"

void w2_errcatch_display_error(uint8_t code) {
	if (code == W2_E_WARN_UNCAUGHT_ERROR) {
		lcd_goto_xy(5, 0);
		print("[u]");
	} else {
		char code_str[5];
		sprintf(code_str, "0x%02x", code);
		lcd_goto_xy(0, 0);
		print(code_str);
	}
}

void w2_errcatch_error_beep(uint8_t code) {
	if (code == W2_E_WARN_UNCAUGHT_ERROR) return;
	uint8_t severity = code & W2_E_TYPE_MASK;
	if ((severity ^ W2_E_TYPE_CRIT) == 0) {
		play("L70 O6 fRfRfRfRf");
	} else if ((severity ^ W2_E_TYPE_WARN) == 0) {
		play("L40 O5 eRe");
	}
}

void w2_errcatch_handle_error(w2_s_error *error) {
	uint8_t severity = error->code & W2_E_TYPE_MASK;

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
		case W2_E_WARN_PING_TIMEOUT:
			break;
		case W2_E_WARN_BATTERY_LOW:
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

	w2_errcatch_display_error(error->code);
	w2_errcatch_error_beep(error->code);

	return;
}
