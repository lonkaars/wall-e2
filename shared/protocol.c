#include "protocol.h"

W2_PROTOCOL_DEFINE(W2_PROTOCOL_CMD_PING_RX)

w2_s_cmd_ping_rx *w2_protocol_parse_cmd_ping_rx(w2_s_bin *data) {
	w2_s_cmd_ping_rx *parsed = malloc(data->bytes);
	memcpy(parsed, data->data, data->bytes);
	return parsed;
}

