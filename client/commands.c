#include <stdlib.h>

#include "commands.h"
#include "time.h"
#include "main.h"
#include "../shared/bin.h"
#include "../shared/protocol.h"

void w2_send_bin(w2_s_bin *data) {
	w2_serial_write("\xff", 1);
	for (uint8_t i = 0; i < data->bytes; i++) {
		uint8_t byte = data->data[i];
		byte == 0xff ? w2_serial_write("\xff\xff", 2) : w2_serial_write((char *)&byte, 1);
	}
}

w2_s_bin* w2_send_info() {
	size_t msg_size		  = sizeof(w2_s_cmd_info_rx);
	w2_s_cmd_info_rx *msg = malloc(msg_size);
	msg->opcode			  = W2_CMD_INFO | W2_CMDDIR_RX;
	w2_s_bin *msg_bin = w2_bin_s_alloc(msg_size, (uint8_t *)msg);
	w2_send_bin(msg_bin);
	free(msg);
	free(msg_bin);
}

w2_s_bin* w2_send_ping() {
	g_w2_state.ping_id = (uint8_t) rand();
	size_t msg_size		  = sizeof(w2_s_cmd_ping_rx);
	w2_s_cmd_ping_rx *msg = malloc(msg_size);
	msg->opcode			  = W2_CMD_PING | W2_CMDDIR_RX;
	msg->id = g_w2_state.ping_id;
	w2_s_bin *msg_bin = w2_bin_s_alloc(msg_size, (uint8_t *)msg);
	w2_send_bin(msg_bin);
	free(msg);
	free(msg_bin);

	w2_timer_start(W2_TIMER_PING);
}

