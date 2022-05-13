#include <stdlib.h>
#include <string.h>

#include "errcatch.h"

w2_s_error g_w2_error_buffer[W2_ERROR_BUFFER_SIZE] = {};
uint8_t g_w2_error_index						   = 0;
uint8_t g_w2_error_offset						   = 0;

void w2_errcatch_main() {
	while (g_w2_error_index != g_w2_error_offset) {
		// handle g_w2_error_buffer[g_w2_error_offset];

		g_w2_error_offset = (g_w2_error_offset + 1) % W2_ERROR_BUFFER_SIZE;
	}
}

w2_s_error *w2_alloc_error(enum w2_e_errorcodes code, uint16_t length, const char *message) {
	w2_s_error *error = calloc(sizeof(w2_s_error) + length, 1);
	memcpy(error, &(w2_s_error const){.code = code, .message_length = length}, sizeof(w2_s_error));
	strncpy(error->message, message, length);

	return error;
}

void w2_errcatch_throw_msg(enum w2_e_errorcodes code, uint16_t length, const char *message) {
	w2_s_error error					= *w2_alloc_error(code, length, message);
	g_w2_error_buffer[g_w2_error_index] = error;
	g_w2_error_index					= (g_w2_error_index)&W2_ERROR_BUFFER_SIZE;
}

void w2_errcatch_throw(enum w2_e_errorcodes code) { w2_errcatch_throw_msg(code, 0, ""); }
