#include "mode_chrg.h"
#include "mode_grid.h"
#include "orangutan_shim.h"
#include "movement.h"
#include "modes.h"

int g_w2_charged_status;

void w2_short_drive() {
	set_motors(50, 50);
	delay(150);
	set_motors(0, 0);
}

void w2_home() {
	set_motors(0, 0);
	delay_ms(150);
	clear();
	print("CHARGING");
	set_motors(30, 30);
	delay_ms(600);
	set_motors(0, 0);
	play_frequency(300, 500, 7);
	delay_ms(600);
	g_w2_position	  = read_line(g_w2_sensors, IR_EMITTERS_ON);
	g_w2_charged_status = 1;
	clear();
	delay_ms(2000);
}


void w2_charge_cross_walk() {
	while (g_w2_sensors[0] < 100 && g_w2_sensors[1] < 100 && g_w2_sensors[2] < 100 && g_w2_sensors[3] < 100 &&
		   g_w2_sensors[4] < 100) {
		set_motors(15, 15);
		delay(500);
		g_w2_position = read_line(g_w2_sensors, IR_EMITTERS_ON);
		if (g_w2_sensors[2] > 100 || g_w2_sensors[3] > 100 || g_w2_sensors[1] > 100) {
			set_motors(0, 0);
			clear();
			print("WALK");
			g_w2_transition++;
			if (g_w2_transition == 3) { //TODO: document g_w2_transition
				set_motors(40, 40);
				delay(600);
				set_motors(0, 0);

				g_w2_transition	= 0;
				w2_modes_swap(W2_M_MAZE);
				break;
			}
		} else {
			g_w2_transition = 0;
			w2_maze_rotation_full();
		}
	}
}


void w2_mode_chrg() {
	unsigned int last_proportional = 0;
	long integral				   = 0;
	// initialize();
	clear();
	print("CHARGE");

	while (1) {
		// Get the position of the line.  Note that we *must* provide
		// the "sensors" argument to read_line() here, even though we
		// are not interested in the individual sensor readings.
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

		if (g_w2_sensors[0] < 100 && g_w2_sensors[1] < 100 && g_w2_sensors[2] < 100 && g_w2_sensors[3] < 100 &&
			g_w2_sensors[4] < 100) {
			w2_charge_cross_walk();
			if (g_w2_mode_history[g_w2_mode_history_index] == W2_M_MAZE) {
				break;
			}
		}

		else if ((g_w2_sensors[0] >= 500 && g_w2_sensors[1] >= 500 && g_w2_sensors[2] >= 500 &&
				  g_w2_sensors[3] >= 500 && g_w2_sensors[4] >= 500) &&
				 g_w2_charged_status == 0) {
			w2_home();
			delay(200);
			w2_maze_rotation_full();
			w2_short_drive();
		} else if (g_w2_sensors[0] >= 500 && g_w2_sensors[1] >= 200 && g_w2_sensors[4] < 100) {
			clear();
			w2_maze_rotation_half_left();
		}

		else if (g_w2_sensors[0] >= 500 && g_w2_sensors[1] >= 250 && g_w2_sensors[2] >= 500 && g_w2_sensors[3] >= 250 &&
				 g_w2_sensors[4] >= 500) {
			clear();
			w2_maze_rotation_half_left();
		} else {
			if (power_difference < 0 &&
				(g_w2_sensors[2] > 100 || g_w2_sensors[3] > 100 || g_w2_sensors[1] > 100)) {
				set_motors(max + power_difference, max);
			} else if (power_difference > 0 &&
					   (g_w2_sensors[2] > 100 || g_w2_sensors[3] > 100 || g_w2_sensors[1] > 100)) {
				set_motors(max, max - power_difference);
			}
		}
	}
}
