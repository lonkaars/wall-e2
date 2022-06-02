#include "mode_dirc.h"
#include "io.h"

#include "orangutan_shim.h"

int16_t g_w2_mode_dirc_motor_l = 0;
int16_t g_w2_mode_dirc_motor_r = 0;

void w2_mode_dirc() {
	set_motors(g_w2_mode_dirc_motor_l, g_w2_mode_dirc_motor_r);
	g_w2_io.motor_left.speed  = g_w2_mode_dirc_motor_l;
	g_w2_io.motor_right.speed = g_w2_mode_dirc_motor_r;
}
