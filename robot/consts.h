#pragma once

#ifndef BUILD_STR
// should be defined with -DBUILD_STR in makefile
#define BUILD_STR ("????????")
#endif

#define W2_MAX_MODULE_CYCLE_MS (20)
#define W2_SERIAL_BAUD (9600)

#define W2_ERR_TYPE_CRIT (0b00 << 6)
#define W2_ERR_TYPE_WARN (0b01 << 6)
#define W2_ERR_TYPE_INFO (0b10 << 6)
#define W2_ERR_TYPE_VERB (0b11 << 6)

/**
 * enum storing all error codes
 *
 * error codes are between 0-63 because the two most significant bits are
 * reserved for error type checking
 */
enum w2_e_errorcodes {
	// critical error codes
	W2_ERR_CONN_LOST	   = 0x00 | W2_ERR_TYPE_CRIT,
	W2_ERR_COM_UNAVAILABLE = 0x01 | W2_ERR_TYPE_CRIT, // client-only
	W2_ERR_LINE_LOST	   = 0x02 | W2_ERR_TYPE_CRIT,
	W2_ERR_OBSTACLE_STUCK  = 0x03 | W2_ERR_TYPE_CRIT,

	// warnings
	W2_ERR_BATTERY_LOW		 = 0x00 | W2_ERR_TYPE_WARN,
	W2_ERR_OBSTACLE_DETECTED = 0x01 | W2_ERR_TYPE_WARN,
	W2_ERR_CYCLE_EXPIRED	 = 0x02 | W2_ERR_TYPE_WARN,
};
