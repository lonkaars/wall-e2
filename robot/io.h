#pragma once

/** @file io.h */

#include "../shared/bool.h"

extern uint16_t g_w2_io_battery_mv;
extern uint8_t g_w2_io_battery_percentage;
extern bool g_w2_io_object_detected;

/** @brief i/o module main */
void w2_io_main();

/** @brief pololu library `set_motors` override */
void w2_set_motors(int left, int right);
