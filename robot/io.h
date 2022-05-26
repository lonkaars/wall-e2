#pragma once
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct {
	bool pressed;
} w2_s_i_push;

typedef struct {
	uint16_t range;
} w2_s_i_contrast;

typedef struct {
	uint16_t detection;
} w2_s_i_distance;

typedef struct {
	uint16_t charge_level;
} w2_s_i_battery;

typedef struct {
	int speed;
} w2_s_o_motor;

typedef struct {
	bool on;
} w2_s_o_led;

typedef struct {
	char text[17]; // 16 chars + '\0'
} w2_s_o_display;

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
} w2_io_all;
