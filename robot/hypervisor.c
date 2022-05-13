#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>

#include "consts.h"
#include "errcatch.h"
#include "hypervisor.h"
#include "io.h"
#include "modes.h"
#include "sercomm.h"
#include "orangutan_shim.h"

void w2_hypervisor_main() {
	time_reset();

	w2_sercomm_main();
	unsigned long sercomm_time = get_ms();
	w2_errcatch_main();
	unsigned long errcatch_time = get_ms() - sercomm_time;
	w2_io_main();
	unsigned long io_time = get_ms() - errcatch_time;
	w2_modes_main();
	unsigned long mode_time = get_ms() - io_time;

	char* message = malloc(80);
	sprintf(message, "sercomm: %lums  ", sercomm_time);
	serial_send(message, 80);
	sprintf(message, "errcatch: %lums ", errcatch_time);
	serial_send(message, 80);
	sprintf(message, "io: %lums       ", io_time);
	serial_send(message, 80);
	sprintf(message, "mode: %lums     ", mode_time);
	serial_send(message, 80);
	sprintf(message, "                ");
	serial_send(message, 80);
	free(message);

	usleep(100e3);

	if (mode_time > W2_MAX_MODULE_CYCLE_MS) w2_errcatch_throw(W2_ERR_CYCLE_EXPIRED);
}
