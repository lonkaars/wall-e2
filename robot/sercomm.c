#include <stdlib.h>
#include <string.h>

#include "../shared/bin.h"
#include "../shared/serial_parse.h"
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
	// send data
	while (g_w2_sercomm_offset != g_w2_sercomm_index) {
		w2_s_bin *data	= g_w2_sercomm_buffer[g_w2_sercomm_offset];
		char *data_cast = malloc(data->bytes);
		memcpy(data_cast, data->data, data->bytes);
		serial_send(data_cast, data->bytes);
		g_w2_sercomm_offset = (g_w2_sercomm_offset + 1) % W2_SERCOMM_BUFFER_SIZE;
	}

	// read and parse data
	while (serial_get_received_bytes() != g_w2_serial_buffer_index) {
		w2_serial_parse(g_w2_serial_buffer[g_w2_serial_buffer_index]);
		g_w2_serial_buffer_index = (g_w2_serial_buffer_index + 1) % W2_SERIAL_READ_BUFFER_SIZE;
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

void w2_scmd_ping_rx(w2_s_bin *data) {
	return;
}

void w2_scmd_mode_rx(w2_s_bin *data) {
	return;
}

void w2_scmd_sped_rx(w2_s_bin *data) {
	return;
}

void w2_scmd_dirc_rx(w2_s_bin *data) {
	return;
}

void w2_scmd_cord_rx(w2_s_bin *data) {
	return;
}

void w2_scmd_bomd_rx(w2_s_bin *data) {
	return;
}

void w2_scmd_sres_rx(w2_s_bin *data) {
	return;
}

void w2_scmd_mcfg_rx(w2_s_bin *data) {
	return;
}

void w2_scmd_sens_rx(w2_s_bin *data) {
	return;
}

void w2_scmd_info_rx(w2_s_bin *data) {
	return;
}

void w2_scmd_disp_rx(w2_s_bin *data) {
	return;
}

void w2_scmd_play_rx(w2_s_bin *data) {
	return;
}

void w2_scmd_cled_rx(w2_s_bin *data) {
	return;
}

void w2_scmd_ping_tx(w2_s_bin *data) { }
void w2_scmd_expt_tx(w2_s_bin *data) { }
void w2_scmd_mode_tx(w2_s_bin *data) { }
void w2_scmd_cord_tx(w2_s_bin *data) { }
void w2_scmd_bomd_tx(w2_s_bin *data) { }
void w2_scmd_sens_tx(w2_s_bin *data) { }
void w2_scmd_info_tx(w2_s_bin *data) { }

