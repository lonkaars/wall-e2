#include <stdlib.h>
#include <string.h>

#include "../shared/bin.h"
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

	while (serial_get_received_bytes() != g_w2_serial_buffer_index) {
		uint8_t byte = g_w2_serial_buffer[g_w2_serial_buffer_index];
#ifdef W2_SIM
		simprintf("serial byte: %02x\n", byte);
#endif
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
	w2_s_bin *data_copy = malloc(sizeof(w2_s_bin) + sizeof(uint8_t) * data->bytes);
	memcpy(&data_copy->data, data->data, data->bytes);
	data_copy->bytes						= data->bytes;
	g_w2_sercomm_buffer[g_w2_sercomm_index] = data_copy;
	if (g_w2_sercomm_buffer_full) return;
	g_w2_sercomm_index = next_index;
}
