#include <stdlib.h>
#include <string.h>

#include "i18n.h"
#include "strings.h"
#include "errcatch.h"
#include "ui.h"

unsigned int g_w2_errcatch_log_line = 0;

unsigned int w2_newline_count(char* str, unsigned int len) {
	unsigned int newlines = 0;
	for (unsigned int i = 0; i < len; i++)
		if (str[i] == '\n') newlines++;
	return newlines;
}

char *w2_err_format(w2_s_error *error) {
	const char* type = g_w2_error_type_strings[error->code >> 6];
	const char* internal = g_w2_error_internal_strings[error->code];
	const char* user = g_w2_error_user_strings[error->code];
	if (internal == NULL || user == NULL) {
		internal = W2_UI_ERROR_INT_W2_E_UNKNOWN;
		user = W2_UI_ERROR_USR_W2_E_UNKNOWN;
	}
	size_t errdesc_len = strlen(type) + strlen(internal) + strlen(user) + 8;
	size_t msg_indent = strlen(type) + 3;
	char *ret_str = malloc(errdesc_len + (error->message_length > 0 ? error->message_length + msg_indent : 0) + 1);
	sprintf(ret_str, "[%s] %02x#%s: %s", type, error->code, internal, user);
	if (error->message_length > 0) {
		sprintf(ret_str + errdesc_len, "\n%*c%s", (int) msg_indent, ' ', error->message);
		g_w2_errcatch_log_line += 1 + w2_newline_count(error->message, error->message_length);
	}
	return ret_str;
}

void w2_ui_tab_errcatch(bool first) {
	g_w2_errcatch_log_line = 0;
	g_w2_ui_pad_body_scroll = 5 - g_w2_ui_height;
	for (unsigned int x = 0; x < W2_ERRCATCH_LOG_SIZE; x++) {
		unsigned int i = (x + g_w2_error_log_index) % W2_ERRCATCH_LOG_SIZE;
		if (g_w2_error_log[i] == NULL) continue;

		wmove(g_w2_ui_pad_body, g_w2_errcatch_log_line, 0);
		char *err_str = w2_err_format(g_w2_error_log[i]);
		waddstr(g_w2_ui_pad_body, err_str);
		free(err_str);

		g_w2_errcatch_log_line++;
	}
	g_w2_ui_pad_body_scroll += g_w2_errcatch_log_line;
}
