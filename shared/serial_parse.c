#include <stdbool.h>

#include "bin.h"
#include "consts.h"
#include "serial_parse.h"
#ifdef W2_SIM
#include "../robot/orangutan_shim.h"
#endif

void w2_serial_handle(w2_s_bin *code) {
#ifdef W2_SIM
	serial_send((char *)code->data, code->bytes);
	// simprintf("yeah: %02x\n", code);
#endif
}

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

	if (current_message_index == complete_message_length) {
		w2_s_bin *copy = w2_bin_s_alloc(current_message_index, current_message);
		w2_serial_handle(copy);
		free(copy);

		memset(&current_message, 0, W2_SERIAL_READ_BUFFER_SIZE);
		current_message_index	= 0;
		complete_message_length = 1;
		attentive				= false;
		listening				= false;
		return;
	}
}
