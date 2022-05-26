#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdint.h>
#include <termios.h>
#include <unistd.h>

#include "sim.h"
#include "../shared/consts.h"
#include "../shared/protocol.h"
#include "sercomm.h"
#include "errcatch.h"

struct timespec reference_time; // NOLINT
bool g_w2_sim_headless = false;

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
	clock_gettime(CLOCK_MONOTONIC, &reference_time);
}

unsigned long get_ms() {
	simprintfunc("get_ms", "");
	struct timespec elapsed;
	clock_gettime(CLOCK_MONOTONIC, &elapsed);
	return ((elapsed.tv_sec * 1000) + (elapsed.tv_nsec / 1000000)) -
		((reference_time.tv_sec * 1000) + (reference_time.tv_nsec / 1000000));
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

void serial_send(char* message, unsigned int length) {
	if (g_w2_sim_headless) {
		for (unsigned int byte = 0; byte < length; byte++)
			putc(message[byte] & 0xff, stdout);
		return;
	}

	if (DBG_ENABLE_PRINTFUNC) simprintfunc("serial_send", "<see below>, %u", length);

	if (!DBG_ENABLE_SERIAL) return;
	w2_s_bin *bin = w2_bin_s_alloc(length, (uint8_t*) message);
	w2_sim_print_serial(bin);
	free(bin);
}

void serial_receive_ring(char* buffer, unsigned char size) {
	simprintfunc("serial_receive_ring", "0x%016lx, %u", (unsigned long) buffer, size);
}

unsigned char serial_get_received_bytes() {
	simprintfunc("serial_get_received_bytes", "");
	return g_w2_serial_buffer_head;
}

void w2_sim_setup(int argc, char **argv) {
	if (argc > 1 && strcmp(argv[1], "headless") == 0)
		g_w2_sim_headless = true;

	// disable echo and enable raw mode
	struct termios term;
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHO | ICANON);
	term.c_cc[VTIME] = 0;
	term.c_cc[VMIN] = 0;
	tcsetattr(STDIN_FILENO, 0, &term);

	// debug error
	// w2_errcatch_throw(W2_E_WARN_BATTERY_LOW);
}

void w2_sim_cycle_begin() {
	// read bytes from stdin
	while(read(STDIN_FILENO, (g_w2_serial_buffer + sizeof(char) * g_w2_serial_buffer_head), 1) > 0)
		g_w2_serial_buffer_head = (g_w2_serial_buffer_head + 1) % W2_SERIAL_READ_BUFFER_SIZE;
}

void w2_sim_print_serial(w2_s_bin *data) {
	if (g_w2_sim_headless) return;
	simprintf(COL_GRN "[%s_%s]" COL_RST, W2_CMD_NAMES[data->data[0] >> 1], W2_CMD_DIRECTIONS[data->data[0] & W2_CMD_DIRECTION_MASK]);
	for (int i = 0; i < data->bytes; i++)
		printf(" %02x", data->data[i]);
	printf("\n");
}

