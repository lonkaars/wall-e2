#pragma once

#include "../shared/bin.h"
#include "../shared/consts.h"
#include "../shared/protocol.h"

/** sercomm ring buffer */
extern w2_s_bin *g_w2_sercomm_buffer[W2_SERCOMM_BUFFER_SIZE];
/** stores head of ring buffer */
extern uint8_t g_w2_sercomm_index;
/** stores start of ring buffer */
extern uint8_t g_w2_sercomm_offset;

/** serial input (receive) buffer */
extern char g_w2_serial_buffer[W2_SERIAL_READ_BUFFER_SIZE];
/** serial input (receive) buffer current position */
extern uint8_t g_w2_serial_buffer_index;
/** serial input (receive) buffer head (sim only) */
extern uint8_t g_w2_serial_buffer_head;

/**
 * serial pc-robot communication module
 *
 * - reads and parses incoming serial data
 * - sends all data in the message buffer
 */
void w2_sercomm_main();

/** append binary message to send buffer */
void w2_sercomm_append_msg(w2_s_bin *data);

