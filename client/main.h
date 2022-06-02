#pragma once

#include "../shared/protocol.h"

typedef struct {
	unsigned int ping;
	uint8_t ping_id;
	bool ping_received;
	bool ping_timeout;

	bool connected;
	uint8_t battery_level;

	uint8_t mode;

	w2_s_cmd_info_tx info;
	w2_s_cmd_sens_tx io;
} w2_s_client_state;

extern w2_s_client_state g_w2_state;
