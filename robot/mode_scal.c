#include "mode_scal.h"
#include "modes.h"
#include "orangutan_shim.h"

void w2_mode_scal() {
	pololu_3pi_init(2000);
	for (int counter = 0; counter < 80; counter++) {
		if (counter < 20 || counter >= 60) {
			set_motors(40, -40);
		} else {
			set_motors(-40, 40);
		}

		calibrate_line_sensors(IR_EMITTERS_ON);

		delay_ms(20);
	}

	w2_modes_call(W2_M_PREV);
}
