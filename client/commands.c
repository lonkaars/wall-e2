#include <stdlib.h>

#include "../shared/bin.h"
#include "../shared/protocol.h"
#include "commands.h"
#include "main.h"
#include "time.h"

void w2_send_bin(w2_s_bin *data) {
	w2_serial_write("\xff", 1);
	for (uint8_t i = 0; i < data->bytes; i++) {
		uint8_t byte = data->data[i];
		byte == 0xff ? w2_serial_write("\xff\xff", 2) : w2_serial_write((char *)&byte, 1);
	}
}

void w2_send_info() {
	W2_CREATE_MSG_BIN(w2_s_cmd_info_rx, msg, msg_bin);
	msg->opcode = W2_CMD_INFO | W2_CMDDIR_RX;

	w2_send_bin(msg_bin);
	free(msg_bin);
}

void w2_send_ping() {
	g_w2_state.ping_id = (uint8_t)rand();
	W2_CREATE_MSG_BIN(w2_s_cmd_ping_rx, msg, msg_bin);
	msg->opcode = W2_CMD_PING | W2_CMDDIR_RX;
	msg->id		= g_w2_state.ping_id;

	w2_send_bin(msg_bin);
	free(msg_bin);

	w2_timer_start(W2_TIMER_PING);
}

void w2_send_mode(w2_e_mode mode) {
	W2_CREATE_MSG_BIN(w2_s_cmd_mode_rx, msg, msg_bin);
	msg->opcode = W2_CMD_MODE | W2_CMDDIR_RX;
	msg->mode	= mode;

	w2_send_bin(msg_bin);
	free(msg_bin);
}

void w2_send_dirc(int left, int right) {
	W2_CREATE_MSG_BIN(w2_s_cmd_dirc_rx, msg, msg_bin);
	msg->opcode = W2_CMD_DIRC | W2_CMDDIR_RX;
	msg->left	= w2_bin_hton16((uint16_t)left);
	msg->right	= w2_bin_hton16((uint16_t)right);

	w2_send_bin(msg_bin);
	free(msg_bin);
}
