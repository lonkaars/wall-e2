#include "io.h"
#include "../shared/consts.h"
#include "modes.h"
#include "orangutan_shim.h"

w2_io_all g_w2_io;

void w2_io_main() {
	g_w2_io.button[0].pressed = get_single_debounced_button_press(BUTTON_A);
	g_w2_io.button[1].pressed = get_single_debounced_button_press(BUTTON_B);
	g_w2_io.button[2].pressed = get_single_debounced_button_press(BUTTON_C);
	g_w2_io.button[3].pressed = get_single_debounced_button_press(TOP_BUTTON);
	g_w2_io.button[4].pressed = get_single_debounced_button_press(BOTTOM_BUTTON);
	unsigned int sensor_values[5];
	qtr_read(sensor_values, QTR_EMITTERS_ON);
	for (int i = 0; i < 5; i++) {
		g_w2_io.qtr[i].range = sensor_values[i];
	}
	// TODO average voltage over mutiple samples sensor
	g_w2_io.battery.charge_level	 = analog_read(W2_BATTERY_PIN);
	g_w2_io.front_distance.detection = analog_read(W2_FRONT_SENSOR_PIN);
	g_w2_io.side_distance.detection	 = analog_read(W2_SIDE_SENSOR_PIN);

	set_motors(g_w2_io.motor_left.speed, g_w2_io.motor_right.speed);
	red_led(g_w2_io.led_red.on);
	green_led(g_w2_io.led_green.on);
	print(g_w2_io.lcd.text);
};

void w2_io_init() { w2_modes_call(W2_M_SCAL); }
