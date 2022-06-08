#include "mode_grid.h"
#include "modes.h"
#include "movement.h"
#include "orangutan_shim.h"

int g_w2_order_number;

int g_w2_maze_status = 0;

w2_s_grid_coordinate g_w2_order[16] = {
	{0, 0},
	{3, 4},
	{2, 1},
	{4, 2},
};
unsigned int g_w2_order_index = 4;
w2_s_grid_coordinate g_w2_location;
w2_s_grid_coordinate g_w2_destination;
w2_e_orientation g_w2_direction;

int g_w2_detection = 0;
int g_w2_transition;	//used for the crosswalk, used to count black lines
char g_w2_x_location = 0; //current location in grid
char g_w2_y_location = 0;


//used for the crosswalk from maze to grid
void w2_crosswalk_stroll() {
	while (g_w2_sensors[0] < 100 && g_w2_sensors[1] < 100 && g_w2_sensors[2] < 100 &&
		   g_w2_sensors[3] < 100 && g_w2_sensors[4] < 100) {
		set_motors(15, 15);
		delay(290);
		g_w2_position = read_line(g_w2_sensors, IR_EMITTERS_ON);
		if (g_w2_sensors[2] > 100 || g_w2_sensors[3] > 100 || g_w2_sensors[1] > 100) {
			set_motors(0, 0);
			g_w2_transition++;
			if (g_w2_transition == 3) {
				set_motors(40, 40);
				delay(600);
				g_w2_transition = 0;
				w2_modes_swap(W2_M_GRID);
				return;
			}
		}

		else {
			g_w2_transition = 0;
			w2_maze_rotation_full();
		}
	}
}

void w2_grid_crossway_detection() {
	set_motors(50, 50);
	delay_ms(150);
	set_motors(10, 10);
	g_w2_position = read_line(g_w2_sensors, IR_EMITTERS_ON);
}

//main function for grid mode
void w2_grid_follow_line() {
	unsigned int last_proportional = 0;
	long integral				   = 0;

	while (1) {
		g_w2_position	 = read_line(g_w2_sensors, IR_EMITTERS_ON);
		int proportional = ((int)g_w2_position) - 2000;
		int derivative	 = proportional - last_proportional;
		integral += proportional;
		last_proportional	 = proportional;
		int power_difference = proportional / 20 + integral / 10000 + derivative * 3 / 2;

		const int max = 60;
		if (power_difference > max) power_difference = max;
		if (power_difference < -max) power_difference = -max;

		if (g_w2_sensors[0] >= 500 && g_w2_sensors[1] >= 250 && g_w2_sensors[2] >= 500 &&
			g_w2_sensors[3] >= 250 && g_w2_sensors[4] >= 500) { //crossways/intersections
			break;
		} else if (g_w2_sensors[0] >= 500 && g_w2_sensors[1] >= 200 && g_w2_sensors[4] < 100) { //left corners
			break;
		} else if (g_w2_sensors[4] >= 500 && g_w2_sensors[3] >= 200 &&
				   g_w2_sensors[0] < 100) { // for the south and west borders of the grid
			break;
		} else if (g_w2_sensors[4] >= 500 && g_w2_sensors[3] >= 200 && g_w2_sensors[2] < 100 &&
				   g_w2_sensors[0] < 100) { // sharp right corners
			break;
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
}

//begin location when entering the grid
void w2_begin_location() {
	g_w2_location.x = 4;
	g_w2_location.y = 0;
	g_w2_direction	= W2_ORT_WEST;
}


//location of grid exit
void w2_end_destination() {
	g_w2_destination.x = 4;
	g_w2_destination.y = 4;
}


//turns are used to get the correct orientation when picking up orders
void w2_turn_north() {
	switch (g_w2_direction) {
		case W2_ORT_NORTH:
			break;

		case W2_ORT_EAST:
			w2_grid_rotation_half_left();
			break;

		case W2_ORT_SOUTH:
			w2_grid_rotation_full();
			break;

		case W2_ORT_WEST:
			w2_grid_rotation_half_right();
			break;
	}

	g_w2_direction = W2_ORT_NORTH;
}

void w2_turn_west() {
	switch (g_w2_direction) {
		case W2_ORT_WEST:
			break;

		case W2_ORT_NORTH:
			w2_grid_rotation_half_left();
			break;

		case W2_ORT_EAST:
			w2_grid_rotation_full();
			break;

		case W2_ORT_SOUTH:
			w2_grid_rotation_half_right();
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
			w2_grid_rotation_half_left();
			break;

		case W2_ORT_NORTH:
			w2_grid_rotation_full();
			break;

		case W2_ORT_EAST:
			w2_grid_rotation_half_right();
			break;
	}

	g_w2_direction = W2_ORT_SOUTH;
}

void w2_turn_east() {
	switch (g_w2_direction) {
		case W2_ORT_EAST:
			break;

		case W2_ORT_SOUTH:
			w2_grid_rotation_half_left();
			break;

		case W2_ORT_WEST:
			w2_grid_rotation_full();
			break;

		case W2_ORT_NORTH:
			w2_grid_rotation_half_right();
			;
			break;
	}

	g_w2_direction = W2_ORT_EAST;
}


//signals when the product is picked
void w2_arrived_message() {
	if (g_w2_location.x == g_w2_destination.x && g_w2_location.y == g_w2_destination.y) {
		play_frequency(400, 500, 7);
		delay(500);
	}
}


//go to correct x coordinate
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

//go to correct y coordinate
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

//main function for grid mode
void w2_mode_grid() {
	set_motors(0, 0);
	delay(500);

	w2_begin_location();

	// TODO: orders read here
	for (int i = 0; i < g_w2_order_index; i++) {
		g_w2_order_number = i + 1;

		g_w2_destination.x = g_w2_order[i].x;
		g_w2_destination.y = g_w2_order[i].y;

		delay(1000);
		w2_go_to_x();
		w2_go_to_y();
		w2_arrived_message();
	}
	w2_end_destination();

	delay(1000);
	w2_go_to_y();
	w2_go_to_x();
	w2_turn_east();
	w2_modes_swap(W2_M_CHRG);
}
