#include <string.h>

#include "consts.h"
#include "serial_parse.h"

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
