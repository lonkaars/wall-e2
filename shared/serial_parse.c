#include <stdbool.h>

#include "consts.h"
#include "serial_parse.h"

void w2_serial_parse(uint8_t byte) {
	static uint8_t current_message[W2_SERIAL_READ_BUFFER_SIZE] = {0};
	static uint8_t current_message_index					   = 0;
	static uint8_t complete_message_length					   = 2;

	static bool attentive = false;
	static bool listening = false;

	if (byte == W2_SERIAL_START_BYTE) {
		attentive = !attentive;
		// if (attentive && listening) {
		// 	current_message[current_message_index++] = byte;
		// }
	} else {
		// activate listen after non-0xff byte after 0xff
		if (attentive && !listening) {
			attentive = false;
			listening = true;
		}
	}

	if (!listening) return;
	current_message[current_message_index++] = byte;

	complete_message_length = w2_scmd_length(current_message, current_message_index);

	if (current_message_index == complete_message_length) {
		w2_scmd_handler(current_message, current_message_index);

		memset(&current_message, 0, W2_SERIAL_READ_BUFFER_SIZE);
		current_message_index	= 0;
		complete_message_length = 1;
		attentive				= false;
		listening				= false;
		return;
	}
}
