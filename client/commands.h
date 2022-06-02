#pragma once

#include "../shared/bin.h"
#include "../shared/modes.h"
#include "serial.h"

void w2_send_info();
void w2_send_ping();
void w2_send_mode(w2_e_mode mode);
void w2_send_dirc(int left, int right);
