#pragma once

#include <stdio.h>

#include "bool.h"

#pragma pack(push, 1)

/** momentary button input struct */
typedef struct {
	bool pressed;
} w2_s_i_push;

/** qtr contrast sensor input struct */
typedef struct {
	uint16_t range;
} w2_s_i_contrast;

/** distance sensor input struct */
typedef struct {
	uint16_t detection;
} w2_s_i_distance;

/** battery input struct */
typedef struct {
	uint16_t charge_level;
} w2_s_i_battery;

/** motor output struct */
typedef struct {
	int16_t speed;
} w2_s_o_motor;

/** underside led output struct */
typedef struct {
	bool on;
} w2_s_o_led;

/** lcd output struct */
typedef struct {
	char text[16];
} w2_s_o_display;

/** struct containing all i/o */
typedef struct {
	w2_s_i_push button[5];
	w2_s_i_contrast qtr[5];
	w2_s_i_distance front_distance;
	w2_s_i_distance side_distance;
	w2_s_i_battery battery;

	w2_s_o_motor motor_left;
	w2_s_o_motor motor_right;
	w2_s_o_led led_red;
	w2_s_o_led led_green;
	w2_s_o_display lcd;
} w2_s_io_all;

#pragma pack(pop)
