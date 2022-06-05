#pragma once

/** @file errcatch.h */

#include <stdint.h>

#include "../shared/consts.h"
#include "../shared/errors.h"

/** error ring buffer */
extern w2_s_error *g_w2_error_buffer[W2_ERROR_BUFFER_SIZE];
/** stores head of ring buffer */
extern uint8_t g_w2_error_index;
/** stores start of ring buffer */
extern uint8_t g_w2_error_offset;

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
