#pragma once

#include "../shared/protocol.h"

typedef struct {
	unsigned int ping;
	w2_s_cmd_info_tx info;
	w2_s_cmd_sens_tx io;
} w2_s_client_state;

extern w2_s_client_state g_w2_state;

