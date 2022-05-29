#include <stdlib.h>
#include <string.h>

#include "../shared/bin.h"
#include "../shared/serial_parse.h"
#include "../shared/errcatch.h"
#include "hypervisor.h"
#include "io.h"
#include "mode_dirc.h"
#include "modes.h"
#include "orangutan_shim.h"
#include "sercomm.h"

w2_s_bin *g_w2_sercomm_buffer[W2_SERCOMM_BUFFER_SIZE] = {0};
uint8_t g_w2_sercomm_index							  = 0;
uint8_t g_w2_sercomm_offset							  = 0;
uint8_t g_w2_sercomm_buffer_full					  = 0;

char g_w2_serial_buffer[W2_SERIAL_READ_BUFFER_SIZE] = {0};
uint8_t g_w2_serial_buffer_index					= 0;
uint8_t g_w2_serial_buffer_head						= 0;

void w2_sercomm_main() {
#ifdef W2_SIM
	simprintfunc("w2_sercomm_main", "");
#endif
	// read and parse data
	while (serial_get_received_bytes() != g_w2_serial_buffer_index) {
		if (!w2_serial_parse(g_w2_serial_buffer[g_w2_serial_buffer_index]))
			w2_errcatch_throw(W2_E_WARN_SERIAL_NOISY);
		g_w2_serial_buffer_index = (g_w2_serial_buffer_index + 1) % W2_SERIAL_READ_BUFFER_SIZE;
	}

	// send data
	while (g_w2_sercomm_offset != g_w2_sercomm_index) {
		w2_s_bin *data = g_w2_sercomm_buffer[g_w2_sercomm_offset];
#ifdef W2_SIM
		w2_sim_print_serial(data);
#endif
		serial_send("\xff", 1);
		for (uint8_t i = 0; i < data->bytes; i++) {
			uint8_t byte = data->data[i];
			byte == 0xff ? serial_send("\xff\xff", 2) : serial_send((char *)&byte, 1);
		}
		g_w2_sercomm_offset = (g_w2_sercomm_offset + 1) % W2_SERCOMM_BUFFER_SIZE;
	}
}

void w2_sercomm_append_msg(w2_s_bin *data) {
#ifdef W2_SIM
	simprintfunc("w2_sercomm_append_msg", "");
#endif
	uint8_t next_index		 = (g_w2_sercomm_index + 1) % W2_SERCOMM_BUFFER_SIZE;
	g_w2_sercomm_buffer_full = next_index == g_w2_sercomm_offset;
	free(g_w2_sercomm_buffer[g_w2_sercomm_index]);
	g_w2_sercomm_buffer[g_w2_sercomm_index] = w2_bin_s_alloc(data->bytes, data->data);
	if (g_w2_sercomm_buffer_full) return;
	g_w2_sercomm_index = next_index;
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Warray-bounds"

void w2_cmd_ping_rx(w2_s_bin *data) {
	W2_CAST_BIN(w2_s_cmd_ping_rx, data, req);

	W2_CREATE_MSG_BIN(w2_s_cmd_ping_tx, res_msg, res_bin);
	res_msg->opcode			 = W2_CMD_PING | W2_CMDDIR_TX;
	res_msg->id				 = req->id;

	w2_sercomm_append_msg(res_bin);
	free(res_bin);
}

void w2_cmd_mode_rx(w2_s_bin *data) {
	W2_CAST_BIN(w2_s_cmd_mode_rx, data, req);
	w2_modes_swap(req->mode);
}

void w2_cmd_sped_rx(w2_s_bin *data) { return; }

void w2_cmd_dirc_rx(w2_s_bin *data) {
	W2_CAST_BIN(w2_s_cmd_dirc_rx, data, req);

	g_w2_mode_dirc_motor_l = w2_bin_ntoh16(req->left);
	g_w2_mode_dirc_motor_r = w2_bin_ntoh16(req->right);
}

void w2_cmd_cord_rx(w2_s_bin *data) { return; }

void w2_cmd_bomd_rx(w2_s_bin *data) { return; }

void w2_cmd_sres_rx(w2_s_bin *data) {
	W2_CAST_BIN(w2_s_cmd_sres_rx, data, req);

	switch (req->type) {
		case W2_CMD_SRES_RX_TYPE_REINITGS: {
			// TODO: soft-reset
			break;
		}
		case W2_CMD_SRES_RX_TYPE_PREVMODE: {
			w2_modes_call(W2_M_PREV);
			break;
		}
		default: {
			w2_errcatch_throw(W2_E_WARN_SERIAL_NOISY);
		}
	}
}

void w2_cmd_mcfg_rx(w2_s_bin *data) { return; }

void w2_cmd_sens_rx(w2_s_bin *data) {
	W2_CREATE_MSG_BIN(w2_s_cmd_sens_tx, res_msg, res_bin);
	res_msg->opcode			 = W2_CMD_SENS | W2_CMDDIR_TX;
	memcpy((uint8_t *)&res_msg->io, (uint8_t *)&g_w2_io, sizeof(w2_s_io_all));

	for (int i = 0; i < 5; i++) w2_bin_repl_hton16(&res_msg->io.qtr[i].range);
	w2_bin_repl_hton16(&res_msg->io.front_distance.detection);
	w2_bin_repl_hton16(&res_msg->io.side_distance.detection);
	w2_bin_repl_hton16(&res_msg->io.battery.charge_level);
	w2_bin_repl_hton16((uint16_t *)&res_msg->io.motor_left.speed);
	w2_bin_repl_hton16((uint16_t *)&res_msg->io.motor_right.speed);

	w2_sercomm_append_msg(res_bin);
	free(res_bin);
}

void w2_cmd_info_rx(w2_s_bin *data) {
	W2_CREATE_MSG_BIN(w2_s_cmd_info_tx, res_msg, res_bin);
	res_msg->opcode			 = W2_CMD_INFO | W2_CMDDIR_TX;
	strncpy((char *)res_msg->build_str, W2_BUILD_STR, sizeof(res_msg->build_str));
	res_msg->errcatch_ms = (uint8_t)g_w2_hypervisor_ema_errcatch_ms;
	res_msg->io_ms		= (uint8_t)g_w2_hypervisor_ema_io_ms;
	res_msg->sercomm_ms	= (uint8_t)g_w2_hypervisor_ema_sercomm_ms;
	res_msg->mode_ms		= (uint8_t)g_w2_hypervisor_ema_mode_ms;
	res_msg->uptime_s	= w2_bin_hton32((uint32_t)(g_w2_hypervisor_uptime_ms / 1e3));

	w2_sercomm_append_msg(res_bin);
	free(res_bin);
}

void w2_cmd_disp_rx(w2_s_bin *data) { return; }

void w2_cmd_play_rx(w2_s_bin *data) { return; }

void w2_cmd_cled_rx(w2_s_bin *data) { return; }

#pragma GCC diagnostic pop

void w2_cmd_ping_tx(w2_s_bin *data) {}
void w2_cmd_expt_tx(w2_s_bin *data) {}
void w2_cmd_mode_tx(w2_s_bin *data) {}
void w2_cmd_cord_tx(w2_s_bin *data) {}
void w2_cmd_bomd_tx(w2_s_bin *data) {}
void w2_cmd_sens_tx(w2_s_bin *data) {}
void w2_cmd_info_tx(w2_s_bin *data) {}
