#include <stdio.h>
#include <time.h>
#include <string.h>

#include "sim.h"

struct timespec reference_time; // NOLINT

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
	simprintfunc("serial_send", "<see below>, %u", length);
	unsigned int bytes = 0;
	simprintf("");
	for (unsigned int byte = 0; byte < length; byte++) {
		if (bytes > DBG_BYTES_PER_LINE) {
			bytes = 0;
			printf("\n");
			simprintf("");
		}
		printf("%02x ", message[byte]);
		bytes++;
	}
	printf("\n");
	return;
}

