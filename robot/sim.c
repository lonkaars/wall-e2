#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdint.h>
#include <termios.h>
#include <unistd.h>

#include "sim.h"
#include "../shared/consts.h"
#include "sercomm.h"

struct timespec reference_time; // NOLINT
bool g_w2_sim_headless = false;

void time_reset() {
	simprintfunc("time_reset", "");
	clock_gettime(CLOCK_MONOTONIC, &reference_time);
	return;
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
	return;
}

void green_led(unsigned char on) {
	simprintfunc("green_led", "%i", on);
	return;
}

void clear() {
	simprintfunc("clear", "");
	return;
}

void play(const char* melody) {
	simprintfunc("play", "\"%s\"", melody);
	return;
}

void serial_set_baud_rate(unsigned int rate) {
	simprintfunc("serial_set_baud_rate", "%u", rate);
	return;
}

void serial_send(char* message, unsigned int length) {
	if (g_w2_sim_headless) {
		for (unsigned int byte = 0; byte < length; byte++)
			putc(message[byte] & 0xff, stdout);
		return;
	}
	if (!DBG_ENABLE_PRINTFUNC) return;
	simprintfunc("serial_send", "<see below>, %u", length);
	unsigned int bytes = 0;
	simprintf("");
	for (unsigned int byte = 0; byte < length; byte++) {
		if (bytes > DBG_BYTES_PER_LINE) {
			bytes = 0;
			printf("\n");
			simprintf("");
		}
		printf("%02x ", message[byte] & 0xff);
		bytes++;
	}
	printf("\n");
	return;
}

void serial_receive_ring(char* buffer, unsigned char size) {
	simprintfunc("serial_receive_ring", "0x%016lx, %u", (unsigned long) buffer, size);
	return;
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

	return;
}

void w2_sim_cycle_begin() {
	// read bytes from stdin
	while(read(STDIN_FILENO, (g_w2_serial_buffer + sizeof(char) * g_w2_serial_buffer_head), 1) > 0)
		g_w2_serial_buffer_head = (g_w2_serial_buffer_head + 1) % W2_SERIAL_READ_BUFFER_SIZE;

	return;
}

