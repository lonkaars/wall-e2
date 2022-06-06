#include <stdlib.h>

#include "../shared/bin.h"
#include "../shared/consts.h"
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

	// clear lcd
	clear();

	// modes array
	w2_modes_init();

	// start serial i/o
	w2_cmd_setup_handlers();
	serial_set_baud_rate(W2_SERIAL_BAUD);
	serial_receive_ring(g_w2_serial_buffer, W2_SERIAL_READ_BUFFER_SIZE);

	// reset timer
	time_reset();

	// set default mode
	w2_modes_swap(W2_M_MAZE);
	w2_modes_call(W2_M_HALT);

	// send info
	w2_cmd_info_rx(NULL);

	// indicate startup done
	play("L50 c>c");
}
