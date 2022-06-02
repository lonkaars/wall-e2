#include "mode_dirc.h"
#include "io.h"
#include "hypervisor.h"
#include "modes.h"
#include "../shared/util.h"
#include "orangutan_shim.h"

int16_t g_w2_mode_dirc_motor_l = 0;
int16_t g_w2_mode_dirc_motor_r = 0;
double g_w2_mode_dirc_power = 1.0;

void w2_mode_dirc() {
	// if (g_w2_connected) g_w2_mode_dirc_power = 1.0;
	// else g_w2_mode_dirc_power = W2_MAX(0, g_w2_mode_dirc_power - 0.01);

	// if (g_w2_mode_dirc_power == 0.0) w2_modes_call(W2_M_HALT);
	set_motors(g_w2_mode_dirc_motor_l * g_w2_mode_dirc_power, g_w2_mode_dirc_motor_r * g_w2_mode_dirc_power);
}
