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

void w2_sercomm_append_msg(w2_s_bin *data);

w2_s_bin w2_sercomm_struct_pack(w2_s_property_list generic_struct);

w2_s_bin w2_sercomm_rx_ping();
w2_s_bin w2_sercomm_tx_ping();
w2_s_bin w2_sercomm_tx_expt();
w2_s_bin w2_sercomm_rx_mode();
w2_s_bin w2_sercomm_tx_mode();
w2_s_bin w2_sercomm_rx_sped();
w2_s_bin w2_sercomm_rx_dirc();
w2_s_bin w2_sercomm_rx_cord();
w2_s_bin w2_sercomm_tx_cord();
w2_s_bin w2_sercomm_rx_bomd();
w2_s_bin w2_sercomm_tx_bomd();
w2_s_bin w2_sercomm_rx_sres();
w2_s_bin w2_sercomm_rx_mcfg();
w2_s_bin w2_sercomm_rx_sens();
w2_s_bin w2_sercomm_tx_sens();
w2_s_bin w2_sercomm_rx_info();
w2_s_bin w2_sercomm_tx_info();
w2_s_bin w2_sercomm_rx_disp();
w2_s_bin w2_sercomm_rx_play();
w2_s_bin w2_sercomm_rx_cled();
