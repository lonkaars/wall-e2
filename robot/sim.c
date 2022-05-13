#include <stdio.h>

#include "sim.h"

void time_reset() {
	return;
	printf("SIM: time_reset()\n");
}

unsigned long get_ms() {
	printf("SIM: get_ms()\n");
	return 0;
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
