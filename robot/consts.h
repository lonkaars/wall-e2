#pragma once

#ifndef W2_BUILD_STR
// is defined by CFLAGS += -DW2_BUILD_STR in makefile
#define W2_BUILD_STR ("????????")
#endif

/** max logic module execution time in milliseconds */
#define W2_MAX_MODULE_CYCLE_MS (20)
/** serial baud rate (bit/s) */
#define W2_SERIAL_BAUD (9600)
/** size of the error handling buffer (in errors, not bytes) */
#define W2_ERROR_BUFFER_SIZE (16)
/** size of the serial communication buffer (in messages, not bytes) */
#define W2_SERCOMM_BUFFER_SIZE (16)
/** size of input (receive) buffer (in bytes) */
#define W2_SERIAL_READ_BUFFER_SIZE (255)
