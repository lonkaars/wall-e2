#pragma once

#include <stdint.h>

#include "consts.h"

/** error-handler module main */
void w2_errcatch_main();

/** append error to error buffer */
void w2_errcatch_throw(enum w2_e_errorcodes code);

/** append error to error buffer (with debug message) */
void w2_errcatch_throw_msg(enum w2_e_errorcodes code, uint16_t length, const char *message);
