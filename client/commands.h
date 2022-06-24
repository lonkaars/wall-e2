#pragma once

#include "../shared/bin.h"
#include "../shared/modes.h"
#include "../shared/protocol.h"
#include "serial.h"

void w2_send_bin(w2_s_bin *data);

void w2_send_info();
void w2_send_ping();
void w2_send_mode(w2_e_mode mode);
void w2_send_dirc(uint16_t left, uint16_t right);
void w2_send_tarq(w2_e_target_area target_area);
