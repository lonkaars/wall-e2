#pragma once

#include <stdint.h>

#include "consts.h"

/** error-handler module main */
void w2_errcatch_main();

/** append error to error buffer */
void w2_errcatch_throw(enum w2_e_errorcodes code);

/** append error to error buffer (with debug message) */
void w2_errcatch_throw_msg(enum w2_e_errorcodes code, uint16_t length, const char *message);

/**
 * error struct
 *
 * holds an error with type `code`, and an optional `message` with length
 * `message_length`
 */
typedef struct {
	enum w2_e_errorcodes code;
	uint8_t message_length;
	uint8_t message[];
} w2_s_error;

/** error ring buffer */
extern w2_s_error g_w2_error_buffer[W2_ERROR_BUFFER_SIZE];
/** stores head of ring buffer */
extern uint8_t g_w2_error_index;
/** stores start of ring buffer */
extern uint8_t g_w2_error_offset;
