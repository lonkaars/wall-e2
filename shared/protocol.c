#include "protocol.h"
#ifdef W2_SIM
#include "../robot/orangutan_shim.h"
#endif

void (*g_w2_cmd_handlers[W2_CMD_COUNT])(w2_s_bin *) = {0};
void w2_cmd_setup_handlers() {
	g_w2_cmd_handlers[W2_CMD_PING | W2_CMDDIR_RX] = w2_cmd_ping_rx;
	g_w2_cmd_handlers[W2_CMD_PING | W2_CMDDIR_TX] = w2_cmd_ping_tx;
	g_w2_cmd_handlers[W2_CMD_EXPT | W2_CMDDIR_TX] = w2_cmd_expt_tx;
	g_w2_cmd_handlers[W2_CMD_MODE | W2_CMDDIR_RX] = w2_cmd_mode_rx;
	g_w2_cmd_handlers[W2_CMD_MODE | W2_CMDDIR_TX] = w2_cmd_mode_tx;
	g_w2_cmd_handlers[W2_CMD_SPED | W2_CMDDIR_RX] = w2_cmd_sped_rx;
	g_w2_cmd_handlers[W2_CMD_DIRC | W2_CMDDIR_RX] = w2_cmd_dirc_rx;
	g_w2_cmd_handlers[W2_CMD_CORD | W2_CMDDIR_RX] = w2_cmd_cord_rx;
	g_w2_cmd_handlers[W2_CMD_CORD | W2_CMDDIR_TX] = w2_cmd_cord_tx;
	g_w2_cmd_handlers[W2_CMD_BOMD | W2_CMDDIR_RX] = w2_cmd_bomd_rx;
	g_w2_cmd_handlers[W2_CMD_BOMD | W2_CMDDIR_TX] = w2_cmd_bomd_tx;
	g_w2_cmd_handlers[W2_CMD_SRES | W2_CMDDIR_RX] = w2_cmd_sres_rx;
	g_w2_cmd_handlers[W2_CMD_MCFG | W2_CMDDIR_RX] = w2_cmd_mcfg_rx;
	g_w2_cmd_handlers[W2_CMD_INFO | W2_CMDDIR_RX] = w2_cmd_info_rx;
	g_w2_cmd_handlers[W2_CMD_INFO | W2_CMDDIR_TX] = w2_cmd_info_tx;
	g_w2_cmd_handlers[W2_CMD_DISP | W2_CMDDIR_RX] = w2_cmd_disp_rx;
	g_w2_cmd_handlers[W2_CMD_PLAY | W2_CMDDIR_RX] = w2_cmd_play_rx;
	g_w2_cmd_handlers[W2_CMD_CLED | W2_CMDDIR_RX] = w2_cmd_cled_rx;
	g_w2_cmd_handlers[W2_CMD_TARQ | W2_CMDDIR_RX] = w2_cmd_tarq_rx;
}

size_t w2_cmd_sizeof(uint8_t data[W2_SERIAL_READ_BUFFER_SIZE], uint8_t data_length) {
	if (data[0] == (W2_CMD_PING | W2_CMDDIR_RX)) return sizeof(w2_s_cmd_ping_rx);
	if (data[0] == (W2_CMD_PING | W2_CMDDIR_TX)) return sizeof(w2_s_cmd_ping_tx);

	if (data[0] == (W2_CMD_MODE | W2_CMDDIR_RX)) return sizeof(w2_s_cmd_mode_rx);
	if (data[0] == (W2_CMD_MODE | W2_CMDDIR_TX)) return sizeof(w2_s_cmd_mode_tx);

	if (data[0] == (W2_CMD_SPED | W2_CMDDIR_RX)) return sizeof(w2_s_cmd_sped_rx);

	if (data[0] == (W2_CMD_DIRC | W2_CMDDIR_RX)) return sizeof(w2_s_cmd_dirc_rx);

	if (data[0] == (W2_CMD_CORD | W2_CMDDIR_RX)) return sizeof(w2_s_cmd_cord_rx);
	if (data[0] == (W2_CMD_CORD | W2_CMDDIR_TX)) return sizeof(w2_s_cmd_cord_tx);

	if (data[0] == (W2_CMD_BOMD | W2_CMDDIR_RX)) return sizeof(w2_s_cmd_bomd_rx);
	if (data[0] == (W2_CMD_BOMD | W2_CMDDIR_TX)) return sizeof(w2_s_cmd_bomd_tx);

	if (data[0] == (W2_CMD_SRES | W2_CMDDIR_RX)) return sizeof(w2_s_cmd_sres_rx);

	if (data[0] == (W2_CMD_INFO | W2_CMDDIR_RX)) return sizeof(w2_s_cmd_info_rx);
	if (data[0] == (W2_CMD_INFO | W2_CMDDIR_TX)) return sizeof(w2_s_cmd_info_tx);

	if (data[0] == (W2_CMD_TARQ | W2_CMDDIR_RX)) return sizeof(w2_s_cmd_tarq_rx);

	w2_s_bin *copy = w2_bin_s_alloc(data_length, data);
	uint8_t length = 1;

	if (data[0] == (W2_CMD_EXPT | W2_CMDDIR_TX)) length = w2_cmd_expt_tx_sizeof(copy);
	if (data[0] == (W2_CMD_MCFG | W2_CMDDIR_RX)) length = w2_cmd_mcfg_rx_sizeof(copy);

	free(copy);

	return length;
}

#define W2_DYN_MEMBER_SIZEOF(struct_t, length_byte, trailing_type)                                 \
	sizeof(struct_t) +                                                                             \
		(data->bytes > length_byte ? (sizeof(trailing_type) * data->data[length_byte]) : 0)

size_t w2_cmd_expt_tx_sizeof(w2_s_bin *data) {
	return W2_DYN_MEMBER_SIZEOF(w2_s_cmd_expt_tx, 2, uint8_t);
}

size_t w2_cmd_mcfg_rx_sizeof(w2_s_bin *data) {
	return W2_DYN_MEMBER_SIZEOF(w2_s_cmd_mcfg_rx, 3, w2_s_cmd_mcfg_feature);
}
