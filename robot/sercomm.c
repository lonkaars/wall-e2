#include <stdlib.h>
#include <string.h>

#include "bin.h"
#include "orangutan_shim.h"
#include "sercomm.h"

w2_s_bin *g_w2_sercomm_buffer[W2_SERCOMM_BUFFER_SIZE] = {};
uint8_t g_w2_sercomm_index							  = 0;
uint8_t g_w2_sercomm_offset							  = 0;
uint8_t g_w2_sercomm_buffer_full					  = 0;

void w2_sercomm_main() {
#ifdef W2_SIM
	simprintfunc("w2_sercomm_main", "");
#endif
	// send data
	while (g_w2_sercomm_index != g_w2_sercomm_offset) {
#ifdef W2_SIM
		simprint("line 0");
		w2_s_bin *data = g_w2_sercomm_buffer[g_w2_sercomm_index];
		simprint("line 1");

		simprintf("bytes: %i\n", data->bytes);
		char *data_cast = malloc(data->bytes);
		simprint("line 2");
		memcpy(data_cast, data->data, data->bytes);
		simprint("line 3");
		serial_send(data_cast, data->bytes);
		simprint("line 4");
		g_w2_sercomm_offset = (g_w2_sercomm_offset + 1) % W2_SERCOMM_BUFFER_SIZE;
		simprint("line 5");
#endif
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
	memcpy(&data_copy->bytes, data->data, data->bytes);
	g_w2_sercomm_buffer[g_w2_sercomm_index] = data_copy;
	if (g_w2_sercomm_buffer_full) return;
	g_w2_sercomm_index = next_index;
}
