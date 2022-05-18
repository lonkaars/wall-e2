#include <stdlib.h>

#include "bin.h"
#include "consts.h"
#include "halt.h"
#include "modes.h"
#include "orangutan_shim.h"
#include "setup.h"

// pointers for endianness check
static const uint16_t _test	 = 1;
static const uint8_t *_ptest = (uint8_t *)&_test;
uint8_t g_w2_endianness;

void w2_setup_main() {
	// check endianness
	g_w2_endianness = *_ptest;

	serial_set_baud_rate(W2_SERIAL_BAUD);

	// reset underside leds
	red_led(0);
	green_led(0);

	// clear lcd
	clear();

	// indicate startup done
	play("L50 c>c");

#ifdef W2_SIM
#include "sercomm.h"
	w2_s_bin *data = malloc(sizeof(w2_s_bin) + sizeof(uint8_t) * 20);
	data->bytes	   = 20;
	data->data[0]  = 0x00;
	data->data[1]  = 0x01;
	data->data[2]  = 0x00;
	data->data[3]  = 0x01;
	data->data[4]  = 0x00;
	data->data[5]  = 0x01;
	data->data[6]  = 0x00;
	data->data[7]  = 0x01;
	data->data[8]  = 0xde;
	data->data[9]  = 0xad;
	data->data[10] = 0xbe;
	data->data[11] = 0xef;
	data->data[12] = 0xff;
	data->data[13] = 0xff;
	data->data[14] = 0x00;
	data->data[15] = 0x00;
	data->data[16] = 0xff;
	data->data[17] = 0xff;
	data->data[18] = 0x00;
	data->data[19] = 0x69;
	w2_sercomm_append_msg(data);
#endif
}
