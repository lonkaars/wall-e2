#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "ui.h"
#include "errcatch.h"
#include "../shared/util.h"
#include "../shared/bin.h"
#include "../shared/protocol.h"
#include "i18n.h"
#include "commands.h"
#include "main.h"

#define W2_IS_CMD(cmd) strncmp(g_w2_command_buffer, cmd, sizeof(cmd) - 1) == 0
#define W2_UI_ORDERS_PRINT_CONST(text) \
	w2_wmvaddstr(g_w2_ui_pad_body, g_w2_order_line, 0, text); \
	g_w2_order_line += w2_newline_count(text, sizeof(text));

char g_w2_command_buffer[W2_UI_ORDER_CMD_BUFFER_SIZE] = { 0x00 };
int g_w2_command_buffer_index = 0;
int g_w2_order_line = 0;
bool g_w2_order_recording = false;
bool g_w2_order_saved = false;
uint16_t g_w2_order_buffer[W2_UI_ORDER_BUFFER_SIZE] = { 0 };
int g_w2_order_buffer_index = 0;

void w2_ui_orders_cmd_error() {
	W2_UI_ORDERS_PRINT_CONST(W2_UI_ORDER_MSG_ERROR);
}

void w2_ui_orders_cmd_help() {
	W2_UI_ORDERS_PRINT_CONST(W2_UI_ORDER_MSG_HELP);
}

void w2_ui_orders_cmd_start() {
	if (g_w2_order_recording) {
		W2_UI_ORDERS_PRINT_CONST(W2_UI_ORDER_MSG_ORDER_START_ERR);
	} else {
		W2_UI_ORDERS_PRINT_CONST(W2_UI_ORDER_MSG_ORDER_START_OK);
		g_w2_order_buffer_index = 0;
	}
	g_w2_order_recording = true;
}

void w2_ui_orders_cmd_coordinate() {
	if (!g_w2_order_recording) {
		W2_UI_ORDERS_PRINT_CONST(W2_UI_ORDER_MSG_ORDER_APPEND_ERR);
		return;
	}
	unsigned int x, y;
	if (sscanf(g_w2_command_buffer, W2_UI_ORDER_CMD_COORDINATE " %u %u", &x, &y) != 2)
		return w2_ui_orders_cmd_error();
	g_w2_order_buffer[g_w2_order_buffer_index++] = y * g_w2_state.map_width + x;
	W2_UI_ORDERS_PRINT_CONST(W2_UI_ORDER_MSG_ORDER_APPEND_OK);
}

void w2_ui_orders_cmd_done() {
	if (g_w2_order_recording) {
		W2_UI_ORDERS_PRINT_CONST(W2_UI_ORDER_MSG_ORDER_DONE_OK);
	} else {
		W2_UI_ORDERS_PRINT_CONST(W2_UI_ORDER_MSG_ORDER_DONE_ERR);
	}
	g_w2_order_saved = true;
	g_w2_order_recording = false;
}

void w2_ui_orders_cmd_send() {
	for (int i = 0; i < g_w2_order_buffer_index; i++) {
		W2_CREATE_MSG_BIN(w2_s_cmd_bomd_rx, msg, bin);

		msg->position = w2_bin_hton16(g_w2_order_buffer[i]);
		msg->id = rand();

		w2_send_bin(bin);
		free(bin);
	}
	W2_UI_ORDERS_PRINT_CONST(W2_UI_ORDER_MSG_ORDER_SENT);
}

void w2_ui_orders_process_cmd() {
	if (g_w2_command_buffer_index == 0) return w2_ui_orders_cmd_error();
	if (W2_IS_CMD(W2_UI_ORDER_CMD_HELP)) return w2_ui_orders_cmd_help();
	if (W2_IS_CMD(W2_UI_ORDER_CMD_START)) return w2_ui_orders_cmd_start();
	if (W2_IS_CMD(W2_UI_ORDER_CMD_COORDINATE)) return w2_ui_orders_cmd_coordinate();
	if (W2_IS_CMD(W2_UI_ORDER_CMD_DONE)) return w2_ui_orders_cmd_done();
	if (W2_IS_CMD(W2_UI_ORDER_CMD_SEND)) return w2_ui_orders_cmd_send();
	return w2_ui_orders_cmd_error();
}

void w2_ui_onkey_orders(int ch) {
	if (ch >= 'A' && ch <= 'Z') ch += 0x20; // convert uppercase to lowercase
	if ((ch >= 'a' && ch <= 'z') || (ch >= '0' && ch <= '9') || (ch == ' ')) {
		g_w2_command_buffer[g_w2_command_buffer_index] = ch;
		g_w2_command_buffer_index = W2_MIN(g_w2_command_buffer_index + 1, W2_UI_ORDER_CMD_BUFFER_SIZE - 1);
	} else if (ch == KEY_BACKSPACE) {
		g_w2_command_buffer_index = W2_MAX(g_w2_command_buffer_index - 1, 0);
		g_w2_command_buffer[g_w2_command_buffer_index] = 0x00;
	} else if (ch == 0x0a) {
		// clear cursor
		wmove(g_w2_ui_pad_body, g_w2_order_line, g_w2_command_buffer_index + 2);
		waddstr(g_w2_ui_pad_body, " ");

		g_w2_order_line += 1;
		w2_ui_orders_process_cmd();
		memset(g_w2_command_buffer, 0x00, W2_UI_ORDER_CMD_BUFFER_SIZE);
		g_w2_command_buffer_index = 0;
	}
}

void w2_ui_tab_orders(bool first) {
	if (first) g_w2_order_line = 0;
	char temp[100];
	sprintf(temp, "> %s_ ", g_w2_command_buffer);
	w2_wmvaddstr(g_w2_ui_pad_body, g_w2_order_line, 0, temp);
}

