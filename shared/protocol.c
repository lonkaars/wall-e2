#include <stdbool.h>

#include "protocol.h"
#ifdef W2_SIM
#include "../robot/orangutan_shim.h"
#endif

uint8_t w2_scmd_length(uint8_t data[W2_SERIAL_READ_BUFFER_SIZE], uint8_t data_length) {
	if ((data[0] & W2_CMD_CODE_MASK) == W2_CMD_PING) return 2;

	if (data[0] == (W2_CMD_MODE | W2_CMDDIR_RX)) return 2;
	if (data[0] == (W2_CMD_MODE | W2_CMDDIR_TX)) return 2;

	if (data[0] == (W2_CMD_SPED | W2_CMDDIR_RX)) return 2;

	if (data[0] == (W2_CMD_DIRC | W2_CMDDIR_RX)) return 5;

	if (data[0] == (W2_CMD_CORD | W2_CMDDIR_RX)) return 6;
	if (data[0] == (W2_CMD_CORD | W2_CMDDIR_TX)) return 6;

	if (data[0] == (W2_CMD_BOMD | W2_CMDDIR_RX)) return 9;
	if (data[0] == (W2_CMD_BOMD | W2_CMDDIR_TX)) return 6;

	if (data[0] == (W2_CMD_SRES | W2_CMDDIR_RX)) return 2;

	if (data[0] == (W2_CMD_SENS | W2_CMDDIR_RX)) return 1;
	if (data[0] == (W2_CMD_SENS | W2_CMDDIR_TX)) return 0;

	if (data[0] == (W2_CMD_INFO | W2_CMDDIR_RX)) return 1;
	if (data[0] == (W2_CMD_INFO | W2_CMDDIR_TX)) return 41;

	w2_s_bin *copy = w2_bin_s_alloc(data_length, data);
	uint8_t length = 1;

	if (data[0] == (W2_CMD_EXPT | W2_CMDDIR_TX)) length = w2_scmd_expt_tx_length(copy);
	if (data[0] == (W2_CMD_MCFG | W2_CMDDIR_RX)) length = w2_scmd_mcfg_rx_length(copy);

	free(copy);

	return length;
}

uint8_t w2_scmd_expt_tx_length(w2_s_bin *data) {
	return 3 + (data->bytes > 2 ? (sizeof(uint8_t) * data->data[2]) : 0);
}

uint8_t w2_scmd_mcfg_rx_length(w2_s_bin *data) {
	// TODO 3 = sizeof(feature) -> protocol.md
	return 4 + (data->bytes > 3 ? (3 * data->data[3]) : 0);
}

void w2_scmd_handler(uint8_t data[W2_SERIAL_READ_BUFFER_SIZE], uint8_t data_length) {
	w2_s_bin *copy = w2_bin_s_alloc(data_length, data);
	bool unknown   = false;

	switch (data[0]) {
		case W2_CMD_PING | W2_CMDDIR_RX: {
			w2_scmd_ping_rx(copy);
			break;
		}
		case W2_CMD_PING | W2_CMDDIR_TX: {
			w2_scmd_ping_tx(copy);
			break;
		}
		case W2_CMD_EXPT | W2_CMDDIR_TX: {
			w2_scmd_expt_tx(copy);
			break;
		}
		case W2_CMD_MODE | W2_CMDDIR_RX: {
			w2_scmd_mode_rx(copy);
			break;
		}
		case W2_CMD_MODE | W2_CMDDIR_TX: {
			w2_scmd_mode_tx(copy);
			break;
		}
		case W2_CMD_SPED | W2_CMDDIR_RX: {
			w2_scmd_sped_rx(copy);
			break;
		}
		case W2_CMD_DIRC | W2_CMDDIR_RX: {
			w2_scmd_dirc_rx(copy);
			break;
		}
		case W2_CMD_CORD | W2_CMDDIR_RX: {
			w2_scmd_cord_rx(copy);
			break;
		}
		case W2_CMD_CORD | W2_CMDDIR_TX: {
			w2_scmd_cord_tx(copy);
			break;
		}
		case W2_CMD_BOMD | W2_CMDDIR_RX: {
			w2_scmd_bomd_rx(copy);
			break;
		}
		case W2_CMD_BOMD | W2_CMDDIR_TX: {
			w2_scmd_bomd_tx(copy);
			break;
		}
		case W2_CMD_SRES | W2_CMDDIR_RX: {
			w2_scmd_sres_rx(copy);
			break;
		}
		case W2_CMD_MCFG | W2_CMDDIR_RX: {
			w2_scmd_mcfg_rx(copy);
			break;
		}
		case W2_CMD_SENS | W2_CMDDIR_RX: {
			w2_scmd_sens_rx(copy);
			break;
		}
		case W2_CMD_SENS | W2_CMDDIR_TX: {
			w2_scmd_sens_tx(copy);
			break;
		}
		case W2_CMD_INFO | W2_CMDDIR_RX: {
			w2_scmd_info_rx(copy);
			break;
		}
		case W2_CMD_INFO | W2_CMDDIR_TX: {
			w2_scmd_info_tx(copy);
			break;
		}
		case W2_CMD_DISP | W2_CMDDIR_RX: {
			w2_scmd_disp_rx(copy);
			break;
		}
		case W2_CMD_PLAY | W2_CMDDIR_RX: {
			w2_scmd_play_rx(copy);
			break;
		}
		case W2_CMD_CLED | W2_CMDDIR_RX: {
			w2_scmd_cled_rx(copy);
			break;
		}
		default: {
#ifdef W2_SIM
			simwarn("unknown serial message with code 0x%02x\n", data[0]);
#endif
			unknown = true;
		}
	}

#ifdef W2_SIM
	if (!unknown) w2_sim_print_serial(copy);
#endif

	free(copy);
}
