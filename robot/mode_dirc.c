#include "mode_dirc.h"
#include "../shared/util.h"
#include "hypervisor.h"
#include "io.h"
#include "modes.h"
#include "orangutan_shim.h"

#include "../shared/errcatch.h"
#include <string.h>

int16_t g_w2_mode_dirc_motor_l = 0;
int16_t g_w2_mode_dirc_motor_r = 0;
uint8_t g_w2_mode_dirc_power   = 100;

void w2_mode_dirc() {
	if (g_w2_connected == 1)
		g_w2_mode_dirc_power = 100;
	else
		g_w2_mode_dirc_power = W2_MAX(0, g_w2_mode_dirc_power - 1);

	if (g_w2_mode_dirc_power == 0) w2_modes_call(W2_M_HALT);

	set_motors(g_w2_mode_dirc_motor_l * g_w2_mode_dirc_power / 100,
			   g_w2_mode_dirc_motor_r * g_w2_mode_dirc_power / 100);
}
