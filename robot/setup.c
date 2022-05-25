#include <stdlib.h>

#include "../shared/bin.h"
#include "../shared/consts.h"
#include "halt.h"
#include "modes.h"
#include "orangutan_shim.h"
#include "sercomm.h"
#include "setup.h"

// pointers for endianness check
static const uint16_t _test	 = 1;
static const uint8_t *_ptest = (uint8_t *)&_test;
uint8_t g_w2_endianness;

void w2_setup_main() {
	// check endianness
	g_w2_endianness = *_ptest;

	// reset underside leds
	red_led(0);
	green_led(0);

	// clear lcd
	clear();

	// start serial i/o
	serial_set_baud_rate(W2_SERIAL_BAUD);
	serial_receive_ring(g_w2_serial_buffer, W2_SERIAL_READ_BUFFER_SIZE);

	// indicate startup done
	play("L50 c>c");
}
