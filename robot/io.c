#include <stdio.h>

#include "../shared/consts.h"
#include "../shared/errcatch.h"
#include "../shared/util.h"
#include "hypervisor.h"
#include "io.h"
#include "modes.h"
#include "orangutan_shim.h"

uint16_t g_w2_io_battery_mv		   = 0;
uint8_t g_w2_io_battery_percentage = 0;
bool g_w2_io_object_detected	   = false;

void w2_io_object_detection() {
	unsigned int front_distance = analog_read(W2_SIDE_SENSOR_PIN);

	if (g_w2_mode_history[g_w2_mode_history_index] == W2_M_HALT) return;

	if (!g_w2_io_object_detected && front_distance >= W2_IO_DISTANCE_CLOSE_THRESHOLD) {
		g_w2_io_object_detected = true;
		w2_hypervisor_time_start(W2_TIMER_OBJECT_DETECTION);
		w2_errcatch_throw(W2_E_WARN_OBSTACLE_DETECTED);
	}

	if (g_w2_io_object_detected) {
		if (front_distance <= W2_IO_DISTANCE_FAR_THRESHOLD) g_w2_io_object_detected = false;
		if (w2_hypervisor_time_end(W2_TIMER_OBJECT_DETECTION) >= W2_IO_DISTANCE_TOO_CLOSE_TIMEOUT)
			w2_errcatch_throw(W2_E_CRIT_OBSTACLE_STUCK);

		set_motors(0, 0);
	}
}

void w2_io_battery_logic() {
	if (w2_hypervisor_time_end(W2_TIMER_BATTERY_MEASUREMENT) <= W2_BATTERY_MEAS_FREQ) return;
	w2_hypervisor_time_start(W2_TIMER_BATTERY_MEASUREMENT);

	g_w2_io_battery_mv = 0;
	for (int i = 0; i < W2_BATTERY_SAMPLES; i++)
		g_w2_io_battery_mv += read_battery_millivolts() / W2_BATTERY_SAMPLES;
	g_w2_io_battery_percentage = W2_RANGE(
		0, (g_w2_io_battery_mv - W2_BATTERY_EMPTY) * 100 / (W2_BATTERY_FULL - W2_BATTERY_EMPTY),
		100);

	char battery_percent[9];
	sprintf(battery_percent, "%i%%  ", g_w2_io_battery_percentage);
	lcd_goto_xy(0, 1);
	print(battery_percent);

	if (g_w2_io_battery_percentage <= W2_BATTERY_PERCENTAGE_LOW &&
		g_w2_target_area != W2_AREA_CHRG) {
		w2_errcatch_throw(W2_E_WARN_BATTERY_LOW);
		g_w2_target_area = W2_AREA_CHRG;
	}
}

void w2_io_main() {
	w2_io_object_detection();
	w2_io_battery_logic();

	return;
}
