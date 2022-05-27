#include <stdlib.h>
#include <string.h>

#include "../shared/bin.h"
#include "../shared/serial_parse.h"
#include "errcatch.h"
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
		w2_serial_parse(g_w2_serial_buffer[g_w2_serial_buffer_index]);
		g_w2_serial_buffer_index = (g_w2_serial_buffer_index + 1) % W2_SERIAL_READ_BUFFER_SIZE;
	}

	// send data
	while (g_w2_sercomm_offset != g_w2_sercomm_index) {
		w2_s_bin *data	= g_w2_sercomm_buffer[g_w2_sercomm_offset];
		char *data_cast = malloc(data->bytes);
		memcpy(data_cast, data->data, data->bytes);
		serial_send(data_cast, data->bytes);
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

void w2_cmd_handler(uint8_t data[W2_SERIAL_READ_BUFFER_SIZE], uint8_t data_length) {
	w2_s_bin *copy				= w2_bin_s_alloc(data_length, data);
	void (*handler)(w2_s_bin *) = g_w2_cmd_handlers[data[0]];

	if (handler == NULL) {
#ifdef W2_SIM
		// TODO throw warning
		simwarn("unknown serial message with code 0x%02x\n", data[0]);
#endif
		w2_errcatch_throw(W2_E_WARN_SERIAL_NOISY);
	} else {
#ifdef W2_SIM
		w2_sim_print_serial(copy);
#endif
		handler(copy);
	}

	free(copy);
}

void w2_cmd_ping_rx(w2_s_bin *data) {
	w2_s_cmd_ping_rx *message = malloc(w2_cmd_sizeof(data->data, data->bytes));
	memcpy(message, data->data, data->bytes);

	size_t return_size				 = sizeof(w2_s_cmd_ping_tx);
	w2_s_cmd_ping_tx *return_message = malloc(return_size);
	return_message->opcode			 = W2_CMD_PING | W2_CMDDIR_TX;
	return_message->id				 = message->id;

	w2_s_bin *return_message_bin = w2_bin_s_alloc(return_size, (uint8_t *)return_message);

	w2_sercomm_append_msg(return_message_bin);

	free(message);
	free(return_message);
	free(return_message_bin);
}

void w2_cmd_mode_rx(w2_s_bin *data) {
	w2_s_cmd_mode_rx *message = malloc(w2_cmd_sizeof(data->data, data->bytes));
	memcpy(message, data->data, data->bytes);

	w2_modes_swap(message->mode);
}

void w2_cmd_sped_rx(w2_s_bin *data) { return; }

void w2_cmd_dirc_rx(w2_s_bin *data) {
	w2_s_cmd_dirc_rx *message = malloc(w2_cmd_sizeof(data->data, data->bytes));
	memcpy(message, data->data, data->bytes);

	g_w2_mode_dirc_motor_l = w2_bin_ntoh16(message->left);
	g_w2_mode_dirc_motor_r = w2_bin_ntoh16(message->right);
}

void w2_cmd_cord_rx(w2_s_bin *data) { return; }

void w2_cmd_bomd_rx(w2_s_bin *data) { return; }

void w2_cmd_sres_rx(w2_s_bin *data) { return; }

void w2_cmd_mcfg_rx(w2_s_bin *data) { return; }

void w2_cmd_sens_rx(w2_s_bin *data) {
	w2_s_cmd_sens_rx *message = malloc(w2_cmd_sizeof(data->data, data->bytes));
	memcpy(message, data->data, data->bytes);

	size_t return_size				 = sizeof(w2_s_cmd_sens_tx);
	w2_s_cmd_sens_tx *return_message = malloc(return_size);
	return_message->opcode			 = W2_CMD_SENS | W2_CMDDIR_TX;
	memcpy((uint8_t *)&return_message->io, (uint8_t *)&g_w2_io, sizeof(w2_s_io_all));

	for (int i = 0; i < 5; i++) w2_bin_repl_hton16(&return_message->io.qtr[i].range);
	w2_bin_repl_hton16(&return_message->io.front_distance.detection);
	w2_bin_repl_hton16(&return_message->io.side_distance.detection);
	w2_bin_repl_hton16(&return_message->io.battery.charge_level);
	w2_bin_repl_hton16((uint16_t *)&return_message->io.motor_left.speed);
	w2_bin_repl_hton16((uint16_t *)&return_message->io.motor_right.speed);

	w2_s_bin *return_message_bin = w2_bin_s_alloc(return_size, (uint8_t *)return_message);

	w2_sercomm_append_msg(return_message_bin);

	free(message);
	free(return_message);
	free(return_message_bin);
}

void w2_cmd_info_rx(w2_s_bin *data) {
	w2_s_cmd_info_rx *message = malloc(w2_cmd_sizeof(data->data, data->bytes));
	memcpy(message, data->data, data->bytes);

	size_t return_size				 = sizeof(w2_s_cmd_info_tx);
	w2_s_cmd_info_tx *return_message = malloc(return_size);
	return_message->opcode			 = W2_CMD_INFO | W2_CMDDIR_TX;
	strncpy((char *)return_message->build_str, W2_BUILD_STR, sizeof(return_message->build_str));
	return_message->errcatch_ms = (uint8_t)g_w2_hypervisor_ema_errcatch_ms;
	return_message->io_ms		= (uint8_t)g_w2_hypervisor_ema_io_ms;
	return_message->sercomm_ms	= (uint8_t)g_w2_hypervisor_ema_sercomm_ms;
	return_message->mode_ms		= (uint8_t)g_w2_hypervisor_ema_mode_ms;
	return_message->uptime_s	= w2_bin_hton32((uint32_t)(g_w2_hypervisor_uptime_ms / 1e3));

	w2_s_bin *return_message_bin = w2_bin_s_alloc(return_size, (uint8_t *)return_message);

	w2_sercomm_append_msg(return_message_bin);

	free(message);
	free(return_message);
	free(return_message_bin);
}

void w2_cmd_disp_rx(w2_s_bin *data) { return; }

void w2_cmd_play_rx(w2_s_bin *data) { return; }

void w2_cmd_cled_rx(w2_s_bin *data) { return; }

void w2_cmd_ping_tx(w2_s_bin *data) {}
void w2_cmd_expt_tx(w2_s_bin *data) {}
void w2_cmd_mode_tx(w2_s_bin *data) {}
void w2_cmd_cord_tx(w2_s_bin *data) {}
void w2_cmd_bomd_tx(w2_s_bin *data) {}
void w2_cmd_sens_tx(w2_s_bin *data) {}
void w2_cmd_info_tx(w2_s_bin *data) {}
