#include "mode_grid.h"
#include "orangutan_shim.h"
#include "modes.h"
#include "movement.h"
#include "transition.h"

int g_w2_order_number;

int g_w2_maze_status = 0;

w2_s_grid_coordinate g_w2_order[4];
w2_s_grid_coordinate g_w2_location;
w2_s_grid_coordinate g_w2_destination;
w2_e_orientation g_w2_direction;

int g_w2_detection = 0;
char g_w2_x_location = 0;
char g_w2_y_location = 0;

void w2_crosswalk_detection() {
	while (g_w2_sensors[0] < 100 && g_w2_sensors[1] < 100 && g_w2_sensors[2] < 100 && g_w2_sensors[3] < 100 &&
		   g_w2_sensors[4] < 100) {
		set_motors(15, 15);
		delay(300);
		g_w2_position = read_line(g_w2_sensors, IR_EMITTERS_ON);
		if (g_w2_sensors[2] > 100 || g_w2_sensors[3] > 100 || g_w2_sensors[1] > 100) {
			set_motors(0, 0);
			clear();
			print("WALK");
			g_w2_transition++;
			if (g_w2_transition == 3) {
				set_motors(40, 40);
				delay(600);
				g_w2_transition	= 0;
				w2_modes_swap(W2_M_GRID);
			}
		}

		else {
			g_w2_transition = 0;
			w2_full_rotation();
		}
	}
}

void w2_grid_rotation_full() {
	set_motors(60, -60);
	delay_ms(540);
	set_motors(10, 10);
	g_w2_position = read_line(g_w2_sensors, IR_EMITTERS_ON);
}

void w2_grid_rotation_left() {
	set_motors(-30, 30);
	delay_ms(600);
	set_motors(10, 10);
	g_w2_position = read_line(g_w2_sensors, IR_EMITTERS_ON);
}

void w2_grid_rotation_right() {
	set_motors(30, -30);
	delay_ms(600);
	set_motors(10, 10);
	g_w2_position = read_line(g_w2_sensors, IR_EMITTERS_ON);
}

void w2_grid_crossway_detection() {
	set_motors(50, 50);
	delay_ms(150);
	set_motors(10, 10);
	g_w2_position = read_line(g_w2_sensors, IR_EMITTERS_ON);
}

void w2_grid_follow_line() {
	static unsigned int last_proportional = 0;
	static long integral				   = 0;

	g_w2_position = read_line(g_w2_sensors, IR_EMITTERS_ON);
	int proportional = ((int)g_w2_position) - 2000;
	int derivative = proportional - last_proportional;
	integral += proportional;
	last_proportional = proportional;
	int power_difference = proportional / 20 + integral / 10000 + derivative * 3 / 2;

	const int max = 60;
	if (power_difference > max) power_difference = max;
	if (power_difference < -max) power_difference = -max;

	if (g_w2_sensors[0] >= 500 && g_w2_sensors[1] >= 250 && g_w2_sensors[2] >= 500 && g_w2_sensors[3] >= 250 &&
		g_w2_sensors[4] >= 500) {
		return;
	} else if (g_w2_sensors[0] >= 500 && g_w2_sensors[1] >= 200 && g_w2_sensors[4] < 100) {
		return;
	} else if (g_w2_sensors[4] >= 500 && g_w2_sensors[3] >= 200 &&
			   g_w2_sensors[0] < 100) { // for the south and west borders of the grid
		return;
	} else if (g_w2_sensors[4] >= 500 && g_w2_sensors[3] >= 200 && g_w2_sensors[2] < 100 &&
			   g_w2_sensors[0] < 100) { // sharp right corners
		return;
	}

	else {
		if (power_difference < 0 &&
			(g_w2_sensors[2] > 100 || g_w2_sensors[3] > 100 || g_w2_sensors[1] > 100)) {
			set_motors(max + power_difference, max);
		} else if (power_difference > 0 &&
				   (g_w2_sensors[2] > 100 || g_w2_sensors[3] > 100 || g_w2_sensors[1] > 100)) {
			set_motors(max, max - power_difference);
		}
	}
}

void w2_begin_location() {
	g_w2_location.x = 4;
	g_w2_location.y = 0;
	g_w2_direction  = W2_ORT_WEST;
}

void w2_end_destination() {
	g_w2_destination.x = 4;
	g_w2_destination.y = 4;
}

void w2_turn_north() {
	switch (g_w2_direction) {
		case W2_ORT_NORTH:
			break;

		case W2_ORT_EAST:
			w2_grid_rotation_left();
			break;

		case W2_ORT_SOUTH:
			w2_grid_rotation_full();
			break;

		case W2_ORT_WEST:
			w2_grid_rotation_right();
			break;
	}

	g_w2_direction = W2_ORT_NORTH;
}

void w2_turn_west() {
	switch (g_w2_direction) {
		case W2_ORT_WEST:
			break;

		case W2_ORT_NORTH:
			w2_grid_rotation_left();
			break;

		case W2_ORT_EAST:
			w2_grid_rotation_full();
			break;

		case W2_ORT_SOUTH:
			w2_grid_rotation_right();
			;
			break;
	}

	g_w2_direction = W2_ORT_WEST;
}

void w2_turn_south() {
	switch (g_w2_direction) {
		case W2_ORT_SOUTH:
			break;

		case W2_ORT_WEST:
			w2_grid_rotation_left();
			break;

		case W2_ORT_NORTH:
			w2_grid_rotation_full();
			break;

		case W2_ORT_EAST:
			w2_grid_rotation_right();
			;
			break;
	}

	g_w2_direction = W2_ORT_SOUTH;
}

void w2_turn_east() {
	switch (g_w2_direction) {
		case W2_ORT_EAST:
			break;

		case W2_ORT_SOUTH:
			w2_grid_rotation_left();
			break;

		case W2_ORT_WEST:
			w2_grid_rotation_full();
			break;

		case W2_ORT_NORTH:
			w2_grid_rotation_right();
			;
			break;
	}

	g_w2_direction = W2_ORT_EAST;
}

void w2_arrived_message() {
	if (g_w2_location.x == g_w2_destination.x && g_w2_location.y == g_w2_destination.y) {
		clear();
		print("ORDER ");
		print_long(g_w2_order_number);
		play_frequency(400, 500, 7);
		delay(500);
	}
}

void w2_go_to_x() {
	if (g_w2_location.x != g_w2_destination.x) {
		while (g_w2_location.x != g_w2_destination.x) {
			if (g_w2_location.x > g_w2_destination.x) {
				w2_turn_west();
				w2_grid_follow_line();
				w2_grid_crossway_detection();
				g_w2_location.x--;
			}

			else if (g_w2_location.x < g_w2_destination.x) {
				w2_turn_east();
				w2_grid_follow_line();
				w2_grid_crossway_detection();
				g_w2_location.x++;
			}
		}
	}
}

void w2_go_to_y() {
	if (g_w2_location.y != g_w2_destination.y) {
		while (g_w2_location.y != g_w2_destination.y) {
			if (g_w2_location.y > g_w2_destination.y) {
				w2_turn_south();
				w2_grid_follow_line();
				w2_grid_crossway_detection();
				g_w2_location.y--;
			}

			else if (g_w2_location.y < g_w2_destination.y) {
				w2_turn_north();
				w2_grid_follow_line();
				w2_grid_crossway_detection();
				g_w2_location.y++;
			}
		}
	}
}

void w2_mode_grid() {
	set_motors(0, 0);
	clear();
	print("GRID");
	delay(500);

	w2_begin_location();

	// TODO: orders read here
	for (int i = 0; i < 4; i++) {
		g_w2_order_number = i + 1;

		g_w2_destination.x = g_w2_order[i].x;
		g_w2_destination.y = g_w2_order[i].y;

		delay(1000);
		w2_go_to_x();
		w2_go_to_y();
	}
	w2_end_destination();

	delay(1000);
	w2_go_to_y();
	w2_go_to_x();
	w2_turn_east(); // this was uncommented (6.3)
	w2_modes_swap(W2_M_CHRG);
}

/*
void w2_mode_maze() {

	unsigned int last_proportional = 0;
	long integral				   = 0;

	// set up the 3pi
	if (g_w2_maze_status == 0) {
		w2_initialize();
	}
	clear();
	print("MAZE");

	g_w2_transition = 0;

	// This is the "main loop" - it will run forever.
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
			w2_cross_walk();
			if (g_w2_parcour_mode == gridMode) {
				break;
			}
			// full_rotation();
		} else if (g_w2_sensors[0] >= 500 && g_w2_sensors[1] >= 250 && g_w2_sensors[2] >= 500 &&
				   g_w2_sensors[3] >= 250 && g_w2_sensors[4] >= 500) {
			w2_crossway_detection();
		} else if (g_w2_sensors[0] >= 500 && g_w2_sensors[1] >= 200 && g_w2_sensors[4] < 100) {
			w2_half_rotation_left();
		} else {
			if (power_difference < 0 && (g_w2_sensors[2] > 100 || g_w2_sensors[3] > 100 || g_w2_sensors[1] > 100))
				set_motors(max + power_difference, max);
			else if (power_difference > 0 &&
					 (g_w2_sensors[2] > 100 || g_w2_sensors[3] > 100 || g_w2_sensors[1] > 100))
				set_motors(max, max - power_difference);
		}
	}
}
*/

