#include "mode_maze.h"
#include "orangutan_shim.h"
#include "movement.h"
#include "mode_grid.h"

unsigned int g_w2_last_proportional = 0;
long g_w2_integral					= 0;

void w2_mode_maze() {
	// PID controller
	g_w2_position = read_line(g_w2_sensors, IR_EMITTERS_ON);
	int proportional = ((int)g_w2_position) - 2000;
	int derivative = proportional - g_w2_last_proportional;
	g_w2_integral += proportional;
	g_w2_last_proportional = proportional;
	int power_difference = proportional / 20 + g_w2_integral / 10000 + derivative * 3 / 2;

	const int max = 60;
	if (power_difference > max) power_difference = max;
	if (power_difference < -max) power_difference = -max;

	if (g_w2_sensors[0] < 100 && g_w2_sensors[1] < 100 && g_w2_sensors[2] < 100 &&
		g_w2_sensors[3] < 100 && g_w2_sensors[4] < 100) {
		w2_crosswalk_stroll();
	} else if (g_w2_sensors[0] >= 500 && g_w2_sensors[1] >= 250 && g_w2_sensors[2] >= 500 &&
			   g_w2_sensors[3] >= 250 && g_w2_sensors[4] >= 500) {
		w2_maze_rotation_half_left();
	} else if (g_w2_sensors[0] >= 500 && g_w2_sensors[1] >= 200 && g_w2_sensors[4] < 100) {
		w2_maze_rotation_half_left();
	} else {
		if (power_difference < 0 &&
			(g_w2_sensors[2] > 100 || g_w2_sensors[3] > 100 || g_w2_sensors[1] > 100))
			set_motors(max + power_difference, max);
		else if (power_difference > 0 &&
				 (g_w2_sensors[2] > 100 || g_w2_sensors[3] > 100 || g_w2_sensors[1] > 100))
			set_motors(max, max - power_difference);
	}
}
