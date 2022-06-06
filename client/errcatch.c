#include <stdlib.h>

#include "errcatch.h"

w2_s_error *g_w2_error_log[W2_ERRCATCH_LOG_SIZE] = {NULL};
unsigned int g_w2_error_log_index				 = 0;

void w2_errcatch_log_error(w2_s_error *error) {
	if (g_w2_error_log[g_w2_error_log_index] != NULL) free(g_w2_error_log[g_w2_error_log_index]);
	g_w2_error_log[g_w2_error_log_index] =
		w2_alloc_error(error->code, error->message_length, error->message);
	g_w2_error_log_index = (g_w2_error_log_index + 1) % W2_ERRCATCH_LOG_SIZE;
}

void w2_errcatch_handle_error(w2_s_error *error) { w2_errcatch_log_error(error); }
