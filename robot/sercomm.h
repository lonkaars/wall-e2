#pragma once

#include "bin.h"

#define W2_CMD_RX (0)
#define W2_CMD_TX (1)

enum w2_e_serial_commands {
	W2_E_CMD_PING = 0x00,
	W2_E_CMD_EXPT = 0x02,
	W2_E_CMD_MODE = 0x04,
	W2_E_CMD_SPED = 0x06,
	W2_E_CMD_DIRC = 0x08,
	W2_E_CMD_CORD = 0x0a,
	W2_E_CMD_BOMD = 0x0c,
	W2_E_CMD_SRES = 0x0e,
	W2_E_CMD_MCFG = 0x10,
	W2_E_CMD_SENS = 0x12,
	W2_E_CMD_INFO = 0x14,
	W2_E_CMD_DISP = 0x16,
	W2_E_CMD_PLAY = 0x18,
	W2_E_CMD_CLED = 0x1a,
};

/**
 * serial pc-robot communication module
 *
 * - reads and parses incoming serial data
 * - sends all data in the message buffer
 */
void w2_sercomm_main();

void w2_sercomm_append_msg(w2_s_bin data);

w2_s_bin w2_sercomm_rx_generic();
w2_s_bin w2_sercomm_tx_generic();

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
