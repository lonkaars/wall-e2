#include <string.h>

#include "consts.h"
#include "serial_parse.h"
#include "errcatch.h"
#ifdef W2_SIM
#include "../robot/orangutan_shim.h"
#endif

bool w2_serial_parse(uint8_t byte) {
	static uint8_t current_message[W2_SERIAL_READ_BUFFER_SIZE] = {0};
	static uint8_t current_message_index					   = 0;
	static uint8_t complete_message_length					   = 2;

	static bool attentive = false;
	static bool listening = false;

	if (byte == W2_SERIAL_START_BYTE) {
		attentive = !attentive;
		if (attentive && listening) return W2_SERIAL_READ_SUCCESS;
	} else if (attentive) {
		attentive = false;
		listening = !listening;
		if (!listening) return W2_SERIAL_READ_FAILURE;
	}

	if (!listening) return W2_SERIAL_READ_SUCCESS;
	current_message[current_message_index++] = byte;

	complete_message_length = w2_cmd_sizeof(current_message, current_message_index);

	if (current_message_index == complete_message_length) {
		w2_cmd_handler(current_message, current_message_index);

		memset(&current_message, 0, W2_SERIAL_READ_BUFFER_SIZE);
		current_message_index	= 0;
		complete_message_length = 1;
		attentive				= false;
		listening				= false;
		return W2_SERIAL_READ_SUCCESS;
	}

	return W2_SERIAL_READ_SUCCESS;
}

void w2_cmd_handler(uint8_t data[W2_SERIAL_READ_BUFFER_SIZE], uint8_t data_length) {
	w2_s_bin *copy				= w2_bin_s_alloc(data_length, data);
	void (*handler)(w2_s_bin *) = g_w2_cmd_handlers[data[0]];

	if (handler == NULL) {
		w2_errcatch_throw(W2_E_WARN_SERIAL_NOISY);
	} else {
#ifdef W2_SIM
		w2_sim_print_serial(copy);
#endif
		handler(copy);
	}

	free(copy);
}

