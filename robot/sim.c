#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>

#include "sim.h"
#include "../shared/consts.h"
#include "../shared/protocol.h"
#include "sercomm.h"
#include "../shared/errcatch.h"

struct timespec reference_time; // NOLINT

static const char* const W2_CMD_NAMES[] = {
	"PING",
	"EXPT",
	"MODE",
	"SPED",
	"DIRC",
	"CORD",
	"BOMD",
	"SRES",
	"MCFG",
	"SENS",
	"INFO",
	"DISP",
	"PLAY",
	"CLED",
};

static const char* const W2_CMD_DIRECTIONS[] = {
	"RX",
	"TX",
};

void time_reset() {
	simprintfunc("time_reset", "");
#ifdef W2_HOST_LINUX
	clock_gettime(CLOCK_MONOTONIC, &reference_time);
#endif
}

unsigned long get_ms() {
	simprintfunc("get_ms", "");
#ifdef W2_HOST_LINUX
	struct timespec elapsed;
	clock_gettime(CLOCK_MONOTONIC, &elapsed);
	return ((elapsed.tv_sec * 1000) + (elapsed.tv_nsec / 1000000)) -
		((reference_time.tv_sec * 1000) + (reference_time.tv_nsec / 1000000));
#endif
	return 0;
}

void red_led(unsigned char on) {
	simprintfunc("red_led", "%i", on);
}

void green_led(unsigned char on) {
	simprintfunc("green_led", "%i", on);
}

void clear() {
	simprintfunc("clear", "");
}

void play(const char* melody) {
	simprintfunc("play", "\"%s\"", melody);
}

void serial_set_baud_rate(unsigned int rate) {
	simprintfunc("serial_set_baud_rate", "%u", rate);
}

void serial_send_blocking(char* message, unsigned int length) {
	for (unsigned int byte = 0; byte < length; byte++)
		putc(message[byte] & 0xff, stdout);
	fflush(stdout);
	return;

	simprintfunc("serial_send", "0x%02x", (uint8_t) message[0]);
}

void serial_receive_ring(char* buffer, unsigned char size) {
	simprintfunc("serial_receive_ring", "0x%016lx, %u", (uint64_t) buffer, size);
}

unsigned char serial_get_received_bytes() {
	simprintfunc("serial_get_received_bytes", "");
	return g_w2_serial_buffer_head;
}

void w2_sim_setup() {
	// disable echo and enable raw mode
	fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);
	struct termios term;
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHO | ICANON);
	term.c_cc[VTIME] = 0;
	term.c_cc[VMIN] = 1;
	tcsetattr(STDIN_FILENO, 0, &term);

	// debug error
	// w2_errcatch_throw(W2_E_WARN_BATTERY_LOW);
}

void w2_sim_cycle_begin() {
	fflush(stdout);

	// read bytes from stdin
	while(read(STDIN_FILENO, (g_w2_serial_buffer + sizeof(char) * g_w2_serial_buffer_head), 1) > 0)
		g_w2_serial_buffer_head = (g_w2_serial_buffer_head + 1) % W2_SERIAL_READ_BUFFER_SIZE;
}

void w2_sim_print_serial(w2_s_bin *data) {
	simprintf(COL_GRN "[%s_%s]" COL_RST, W2_CMD_NAMES[data->data[0] >> 1], W2_CMD_DIRECTIONS[data->data[0] & W2_CMD_DIRECTION_MASK]);
	for (int i = 0; i < data->bytes; i++)
		fprintf(stderr, " %02x", data->data[i]);
	fprintf(stderr, "\n");
}

void set_motors(int left, int right) {
	simprintfunc("set_motors", "%i, %i", left, right);
}

static const char* const W2_BUTTON_NAMES[] = {
	"BUTTON_A",
	"BUTTON_B",
	"BUTTON_C",
	"TOP_BUTTON",
	"BOTTOM_BUTTON",
};

unsigned char get_single_debounced_button_press(unsigned char buttons) {
	simprintfunc("get_single_debounced_button_press", "%s", W2_BUTTON_NAMES[buttons]);
	return false;
}

void qtr_read(unsigned int* sensor_values, unsigned char read_mode) {
	simprintfunc("qtr_read", "0x%016lx, %s", (uint64_t) sensor_values, read_mode == QTR_EMITTERS_ON ? "QTR_EMITTERS_ON" : "???");
	sensor_values[0] = 0;
	sensor_values[1] = 0;
	sensor_values[2] = 0;
	sensor_values[3] = 0;
	sensor_values[4] = 0;
}

unsigned int analog_read(unsigned char channel) {
	simprintfunc("analog_read", "ADC%i", channel);
	return 0;
}

void print(const char* str) {
	simprintfunc("print", "\"%s\"", str);
}

