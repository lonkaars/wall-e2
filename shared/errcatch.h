#pragma once

/** @file errcatch.h */

#include <stdint.h>

#include "bool.h"
#include "consts.h"

#define W2_E_TYPE_MASK (0b11 << 6)

#define W2_E_TYPE_CRIT (0b00 << 6)
#define W2_E_TYPE_WARN (0b01 << 6)
#define W2_E_TYPE_INFO (0b10 << 6)
#define W2_E_TYPE_VERB (0b11 << 6)

/**
 * enum storing all error codes
 *
 * error codes are between 0-63 because the two most significant bits are
 * reserved for error type checking
 */
typedef enum {
	/** wireless connection lost from either robot or client-side */
	W2_E_CRIT_CONN_LOST = 0x00 | W2_E_TYPE_CRIT,
	/** serial COM-port unavalable. client-side only */
	W2_E_CRIT_COM_UNAVAILABLE = 0x01 | W2_E_TYPE_CRIT,
	/** line unable to be found automatically */
	W2_E_CRIT_LINE_LOST = 0x02 | W2_E_TYPE_CRIT,
	/** obstacle unavoidable, robot stuck */
	W2_E_CRIT_OBSTACLE_STUCK = 0x03 | W2_E_TYPE_CRIT,
	/** semver major version doesn't match */
	W2_E_CRIT_VERSION_INCOMPATIBLE = 0x04 | W2_E_TYPE_CRIT,

	/** battery low, returning to charging station */
	W2_E_WARN_BATTERY_LOW = 0x00 | W2_E_TYPE_WARN,
	/** obstacle detected, waiting then trying other route */
	W2_E_WARN_OBSTACLE_DETECTED = 0x01 | W2_E_TYPE_WARN,
	/** logic cycle took longer than `W2_MAX_MODULE_CYCLE_MS` */
	W2_E_WARN_CYCLE_EXPIRED = 0x02 | W2_E_TYPE_WARN,
	/** error thrown without handler, gets thrown on next cycle */
	W2_E_WARN_UNCAUGHT_ERROR = 0x03 | W2_E_TYPE_WARN,
	/** error buffer full, gets thrown on next cycle */
	W2_E_WARN_ERR_BUFFER_FULL = 0x04 | W2_E_TYPE_WARN,
	/** line lost, trying to calibrate */
	W2_E_WARN_LINE_LOST = 0x05 | W2_E_TYPE_WARN,
	/** serial buffer full, gets thrown on next cycle */
	W2_E_WARN_SERCOMM_BUFFER_FULL = 0x06 | W2_E_TYPE_WARN,
	/** semver minor version doesn't match */
	W2_E_WARN_VERSION_INCOMPATIBLE = 0x07 | W2_E_TYPE_WARN,
	/** unknown message encountered (noisy channel?) */
	W2_E_WARN_SERIAL_NOISY = 0x09 | W2_E_TYPE_WARN,
	/** mode history index out of bounds */
	W2_E_WARN_MODE_HISTORY_BUFFER_IOB = 0x0a | W2_E_TYPE_WARN,
	/** ping timeout reached */
	W2_E_WARN_PING_TIMEOUT = 0x0b | W2_E_TYPE_WARN,

	/** order reached */
	W2_E_INFO_ORDER_ARRIVED = 0x00 | W2_E_TYPE_INFO,
} w2_e_errorcode;

/**
 * error struct
 *
 * holds an error with type `code`, and an optional `message` with length
 * `message_length`
 */
typedef struct {
	w2_e_errorcode code;
	uint8_t message_length;
	char message[];
} w2_s_error;

/** error ring buffer */
extern w2_s_error *g_w2_error_buffer[W2_ERROR_BUFFER_SIZE];
/** stores head of ring buffer */
extern uint8_t g_w2_error_index;
/** stores start of ring buffer */
extern uint8_t g_w2_error_offset;
/** error buffer full flag */
extern bool g_w2_error_buffer_full;
/** uncaught error flag */
extern bool g_w2_error_uncaught;

/** error-handler module main */
void w2_errcatch_main();

/** handle error */
void w2_errcatch_handle_error(w2_s_error *error);

/** append error to error buffer */
void w2_errcatch_throw(w2_e_errorcode code);

/** append error to error buffer (with debug message) */
void w2_errcatch_throw_msg(w2_e_errorcode code, uint16_t length, const char *message);

/**
 * allocate and initialize error struct
 *
 * TODO: doesn't handle null pointers from malloc
 */
w2_s_error *w2_alloc_error(w2_e_errorcode code, uint16_t length, const char *message);
