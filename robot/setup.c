#include <pololu/orangutan.h>

#include "consts.h"
#include "setup.h"

void w2_setup_main() {
	serial_set_baud_rate(W2_SERIAL_BAUD);

	// indicate startup done
	play("L50 c>c");
}
