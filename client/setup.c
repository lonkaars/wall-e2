#include <stdio.h>
#include <stdlib.h>

#include "../shared/bin.h"
#include "../shared/protocol.h"
#include "commands.h"
#include "serial.h"
#include "setup.h"

// pointers for endianness check
static const uint16_t _test	 = 1;
static const uint8_t *_ptest = (uint8_t *)&_test;
uint8_t g_w2_endianness;

void w2_client_setup(int argc, char **argv) {
	if (argc < 2) {
		printf("usage: %s <serial port>\n", argv[0]);
		exit(1);
	}

	if (w2_serial_open(argv[1]) == 0) {
		printf("serial port open fout\n");
		exit(1);
	}

	w2_cmd_setup_handlers();

	w2_send_info();
	w2_send_ping();

	// check endianness
	g_w2_endianness = *_ptest;
}
