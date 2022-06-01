#pragma once

#include "../shared/bin.h"
#include "../shared/modes.h"
#include "serial.h"

w2_s_bin *w2_send_mode(w2_e_mode mode);
w2_s_bin *w2_send_dirc(uint16_t left, uint16_t right);
w2_s_bin *w2_send_info();
w2_s_bin *w2_send_ping();
