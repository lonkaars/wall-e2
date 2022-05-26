#pragma once

#include <stdint.h>

extern int16_t g_w2_mode_dirc_motor_l;
extern int16_t g_w2_mode_dirc_motor_r;

/**
 * direct control mode
 *
 * respond to DIRC commands
 */
void w2_mode_dirc();
