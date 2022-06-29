#include "mode_chrg.h"
#include "io.h"
#include "../shared/bool.h"
#include "hypervisor.h"
#include "mode_grid.h"
#include "modes.h"
#include "movement.h"
#include "orangutan_shim.h"

#include <stdio.h>

void w2_short_drive() {
	w2_set_motors(50, 50);
	delay(150);
	w2_set_motors(0, 0);
}

// crosswalk from charging station back to maze
bool w2_charge_cross_walk() {
	if (g_w2_transition == 0) {
		w2_set_motors(-30, 30);
		delay(50);
	}
	while (g_w2_sensors[0] < 100 && g_w2_sensors[1] < 100 && g_w2_sensors[2] < 100 &&
		   g_w2_sensors[3] < 100 && g_w2_sensors[4] < 100) {
		w2_set_motors(15, 15);
		delay(W2_GRID_CROSSWALK_DISTANCE);
		g_w2_position = read_line(g_w2_sensors, IR_EMITTERS_ON);
		if (g_w2_sensors[2] > 100 || g_w2_sensors[3] > 100 || g_w2_sensors[1] > 100) {
			w2_set_motors(0, 0);
			g_w2_transition++;
			if (g_w2_transition == 3) { // TODO: document g_w2_transition
				w2_set_motors(40, 40);
				delay(W2_GRID_CROSSWALK_DISTANCE);
				w2_set_motors(0, 0);

				g_w2_transition = 0;
				w2_modes_swap(W2_M_MAZE);

				return true;
			}
		} else {
			g_w2_transition = 0;
			w2_maze_rotation_full();

			return false;
		}
	}
	return false;
}

// main function for charge mode
void w2_mode_chrg() {
	static unsigned int last_proportional = 0;
	static long integral				  = 0;
	static bool g_w2_chrg_aligned         = false;

	if (g_w2_chrg_aligned) {
		if (g_w2_target_area == W2_AREA_CHRG) return;

		delay(200);
		w2_maze_rotation_full();
		w2_short_drive();

		g_w2_chrg_aligned = false;
		return;
	}

	g_w2_position = read_line(g_w2_sensors, IR_EMITTERS_ON);

	// The "proportional" term should be 0 when we are on the line.
	int proportional = ((int)g_w2_position) - 2000;

	// Compute the derivative (change) and integral (sum) of the
	// position.
	int derivative = proportional - last_proportional;
	integral += proportional;

	// Remember the last position.
	last_proportional = proportional;

	// Compute the difference between the two motor power settings,
	// m1 - m2.  If this is a positive number the robot will turn
	// to the right.  If it is a negative number, the robot will
	// turn to the left, and the magnitude of the number determines
	// the sharpness of the turn.
	int power_difference = proportional / 20 + integral / 10000 + derivative * 3 / 2;

	// Compute the actual motor settings.  We never set either motor
	// to a negative value.
	
	const int max = 60;
	if (power_difference > max) power_difference = max;
	if (power_difference < -max) power_difference = -max;

	if (g_w2_sensors[0] < 100 && g_w2_sensors[1] < 100 && g_w2_sensors[2] < 100 &&
		g_w2_sensors[3] < 100 && g_w2_sensors[4] < 100) {
		bool success = w2_charge_cross_walk();
		if (success) return;
	}

	else if (g_w2_sensors[0] >= 500 && g_w2_sensors[1] >= 500 && g_w2_sensors[2] >= 500 &&
			 g_w2_sensors[3] >= 500 && g_w2_sensors[4] >= 500) {
		if (g_w2_target_area == W2_AREA_CHRG) {
			if (!g_w2_chrg_aligned) {
				w2_set_motors(0, 0);
				delay_ms(150);
				w2_set_motors(30, 30);
				delay_ms(600);
				w2_set_motors(0, 0);
				delay_ms(600);
				g_w2_chrg_aligned = true;
			}
		} else {
			w2_maze_rotation_half_left();
		}
	} else if (g_w2_sensors[0] >= 500 && g_w2_sensors[1] >= 200 && g_w2_sensors[4] < 100) {
		w2_maze_rotation_half_left();
	} else {
		if (power_difference < 0 &&
			(g_w2_sensors[2] > 100 || g_w2_sensors[3] > 100 || g_w2_sensors[1] > 100)) {
			w2_set_motors(max + power_difference, max);
		} else if (power_difference > 0 &&
				   (g_w2_sensors[2] > 100 || g_w2_sensors[3] > 100 || g_w2_sensors[1] > 100)) {
			w2_set_motors(max, max - power_difference);
		}
	}
}

