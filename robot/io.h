#pragma once
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#define FRONT_SENSOR_PIN 5
#define SIDE_SENSOR_PIN 7
#define BATTERY_PIN 6  

//inputs

typedef struct {
    bool pressed;
} w2_s_io_push;

typedef struct {
    uint16_t range;
    
} w2_s_io_contrast;

typedef struct {
    uint16_t detection;
} w2_s_io_distance;

//outputs

typedef struct {
    int speed;
} w2_s_io_motor;

typedef struct {
    bool toggle;
} w2_s_io_led;

typedef struct {
    char text[16];
} w2_s_io_display;
typedef struct {
    uint8_t charged;
} w2_s_io_battery;

//all i/o

typedef struct {
    w2_s_i_push button[5];
    w2_s_i_contrast qtrSensor[5];
    w2_s_i_distance frontDetection;
    w2_s_i_distance sideDetection;
    w2_s_i_battery batteryLevel;


    w2_s_o_motor motor_left;
    w2_s_o_motor motor_right;
    w2_s_o_led led_red;
    w2_s_o_led led_green;
    w2_s_o_display lcd;
} w2_io_all;
