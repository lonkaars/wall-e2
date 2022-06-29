#include "mode_scal.h"
#include "modes.h"
#include "orangutan_shim.h"
#include "io.h"

// callibrates the robot
void w2_mode_scal() {
	for (int counter = 0; counter < 80; counter++) {
		if (counter < 20 || counter >= 60) {
			w2_set_motors(40, -40);
		} else {
			w2_set_motors(-40, 40);
		}

		calibrate_line_sensors(IR_EMITTERS_ON);

		delay_ms(20);
	}

	w2_modes_call(W2_M_PREV);
}
