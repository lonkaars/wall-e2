#pragma once

/** @file consts.h */

#ifndef W2_BUILD_STR
// is defined by CFLAGS += -DW2_BUILD_STR in makefile
#define W2_BUILD_STR ("????????")
#endif

#if !defined W2_HOST_WIN32 && !defined W2_HOST_LINUX
#define W2_HOST_UNKNOWN
#warning "host operating system unknown"
#endif

/** serial baud rate (bit/s) */
#define W2_SERIAL_BAUD (9600)
/** size of input (receive) buffer (in bytes) */
#define W2_SERIAL_READ_BUFFER_SIZE (255)

/** size of the error handling buffer (in errors, not bytes) */
#define W2_ERROR_BUFFER_SIZE (16)
/** size of the serial communication buffer (in messages, not bytes) */
#define W2_SERCOMM_BUFFER_SIZE (16)
/** size of mode history buffer */
#define W2_MODE_HISTORY_BUFFER_SIZE (4)

/** max logic module execution time in milliseconds */
#define W2_MAX_MODULE_CYCLE_MS (20)

/** exponential moving average new measurement weight (double 0-1) */
#define W2_EMA_WEIGHT (0.10)

/** minimal time between pings */
#define W2_PING_FREQUENCY (1e3)
/** max time between ping and answer */
#define W2_PING_TIMEOUT (5e3)

/** front-facing distance sensor pinout */
#define W2_FRONT_SENSOR_PIN 5
/** battery voltage sensor pinout */
#define W2_BATTERY_PIN 6
/** side-facing distance sensor pinout */
#define W2_SIDE_SENSOR_PIN 7
