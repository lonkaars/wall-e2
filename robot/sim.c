#include <stdio.h>
#include <time.h>
#include <string.h>

#include "sim.h"

struct timespec reference_time; // NOLINT

void time_reset() {
	// printf("SIM: time_reset()\n");
	clock_gettime(CLOCK_MONOTONIC, &reference_time);
	return;
}

unsigned long get_ms() {
	// printf("SIM: get_ms()\n");
	struct timespec elapsed;
	clock_gettime(CLOCK_MONOTONIC, &elapsed);
	return ((elapsed.tv_sec * 1000) + (elapsed.tv_nsec / 1000000)) -
		((reference_time.tv_sec * 1000) + (reference_time.tv_nsec / 1000000));
}

void red_led(unsigned char on) {
	printf("SIM: red_led(%i)\n", on);
	return;
}

void green_led(unsigned char on) {
	printf("SIM: green_led(%i)\n", on);
	return;
}

void clear() {
	printf("SIM: clear()\n");
	return;
}

void play(const char* melody) {
	printf("SIM: play(\"%s\")\n", melody);
	return;
}

void serial_set_baud_rate(unsigned int rate) {
	printf("SIM: serial_set_baud_rate(%u)\n", rate);
	return;
}

// TODO: hexdump binary data
void serial_send(char* message, unsigned int length) {
	char message_copy[length];
	strncpy(message_copy, message, length);
	printf("SIM: serial_send(\"%s\", %u)\n", message_copy, length);
	return;
}

