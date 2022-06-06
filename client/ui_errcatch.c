#include <stdlib.h>

#include "errcatch.h"
#include "ui.h"

char *w2_err_format(w2_s_error *error) {
	char *ret_str = malloc(32);
	sprintf(ret_str, "hai, 0x%02x", error->code);
	return ret_str;
}

void w2_ui_tab_errcatch(bool first) {
	g_w2_ui_pad_body_scroll = 5 - g_w2_ui_height;
	unsigned int line		= 0;
	for (unsigned int x = 0; x < W2_ERRCATCH_LOG_SIZE; x++) {
		unsigned int i = (x + g_w2_error_log_index) % W2_ERRCATCH_LOG_SIZE;
		if (g_w2_error_log[i] == NULL) continue;

		wmove(g_w2_ui_pad_body, line, 0);
		char *err_str = w2_err_format(g_w2_error_log[i]);
		waddstr(g_w2_ui_pad_body, err_str);
		free(err_str);

		line++;
	}
	g_w2_ui_pad_body_scroll += line;
}
