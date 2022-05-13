#include <stdlib.h>

#include "orangutan_shim.h"
#include "consts.h"
#include "halt.h"
#include "modes.h"
#include "setup.h"

void w2_setup_main() {
	serial_set_baud_rate(W2_SERIAL_BAUD);

	// reset underside leds
	red_led(0);
	green_led(0);

	// clear lcd
	clear();

	// indicate startup done
	play("L50 c>c");
}
