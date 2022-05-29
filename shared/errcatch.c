#include <stdlib.h>
#include <string.h>

#include "errcatch.h"

w2_s_error *g_w2_error_buffer[W2_ERROR_BUFFER_SIZE] = {};
uint8_t g_w2_error_index							= 0;
uint8_t g_w2_error_offset							= 0;
bool g_w2_error_buffer_full							= 0;
bool g_w2_error_uncaught							= 0;

void w2_errcatch_main() {
	while (g_w2_error_offset != g_w2_error_index) {
		w2_s_error *error = g_w2_error_buffer[g_w2_error_offset];
		w2_errcatch_handle_error(error);
		g_w2_error_offset = (g_w2_error_offset + 1) % W2_ERROR_BUFFER_SIZE;
	}
	if (g_w2_error_buffer_full) {
		w2_errcatch_throw(W2_E_WARN_ERR_BUFFER_FULL);
		g_w2_error_buffer_full = 0;
	}
	if (g_w2_error_uncaught) {
		w2_errcatch_throw(W2_E_WARN_UNCAUGHT_ERROR);
		g_w2_error_uncaught = 0;
	}
}

w2_s_error *w2_alloc_error(w2_e_errorcode code, uint16_t length, const char *message) {
	w2_s_error *error = malloc(sizeof(w2_s_error) + length);
	memcpy(error, &(w2_s_error const){.code = code, .message_length = length}, sizeof(w2_s_error));
	strncpy(error->message, message, length);

	return error;
}

void w2_errcatch_throw(w2_e_errorcode code) { w2_errcatch_throw_msg(code, 0, ""); }
void w2_errcatch_throw_msg(w2_e_errorcode code, uint16_t length, const char *message) {
	uint8_t next_index	   = (g_w2_error_index + 1) % W2_ERROR_BUFFER_SIZE;
	g_w2_error_buffer_full = next_index == g_w2_error_offset;
	free(g_w2_error_buffer[g_w2_error_index]);
	w2_s_error *error					= w2_alloc_error(code, length, message);
	g_w2_error_buffer[g_w2_error_index] = error;
	if (g_w2_error_buffer_full) return;
	g_w2_error_index = next_index;
}
