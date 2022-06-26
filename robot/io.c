#include "io.h"
#include "../shared/consts.h"
#include "../shared/errcatch.h"
#include "hypervisor.h"
#include "modes.h"
#include "orangutan_shim.h"

bool g_w2_io_object_detected = false;

#include <stdio.h>

void w2_io_object_detection() {
	unsigned int front_distance = analog_read(W2_SIDE_SENSOR_PIN);

	if (g_w2_mode_history[g_w2_mode_history_index] == W2_M_HALT) return;

	if (!g_w2_io_object_detected && front_distance >= W2_IO_DISTANCE_CLOSE_THRESHOLD) {
		g_w2_io_object_detected = true;
		w2_hypervisor_time_start(W2_TIMER_OBJECT_DETECTION);
		lcd_goto_xy(0, 0);
		print("detected");
	}

	if (g_w2_io_object_detected) {
		if (front_distance <= W2_IO_DISTANCE_FAR_THRESHOLD) {
			g_w2_io_object_detected = false;
			lcd_goto_xy(0, 0);
			print("        ");
		}
		if (w2_hypervisor_time_end(W2_TIMER_OBJECT_DETECTION) >= W2_IO_DISTANCE_TOO_CLOSE_TIMEOUT) {
			w2_errcatch_throw(W2_E_CRIT_OBSTACLE_STUCK);
			lcd_goto_xy(0, 0);
			print("unavoid ");
		}

		set_motors(0, 0);
	}
}

void w2_io_main() {
	w2_io_object_detection();
	// TODO: battery status

	return;
}
