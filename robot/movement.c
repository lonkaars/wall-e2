#include "movement.h"
#include "orangutan_shim.h"

unsigned int g_w2_sensors[5] = {0};		//IR sensors on the bottom of the robot
unsigned int g_w2_position	 = 0;		//position on the black line


//full rotation maze/charge
void w2_maze_rotation_full() {
	set_motors(0, 0);
	delay_ms(500);
	set_motors(60, -60);
	delay_ms(540);
	set_motors(0, 0);
	g_w2_position = read_line(g_w2_sensors, IR_EMITTERS_ON);
	delay_ms(500);
}

//left turn maze/charge
void w2_maze_rotation_half_left() {
	set_motors(0, 0);
	set_motors(50, 50);
	delay_ms(150);
	set_motors(-30, 30);
	delay_ms(600);
	set_motors(0, 0);
	g_w2_position = read_line(g_w2_sensors, IR_EMITTERS_ON);
	delay_ms(500);
}

//right turn maze/charge
void w2_maze_rotation_half_right() {
	set_motors(0, 0);
	set_motors(50, 50);
	delay_ms(150);
	set_motors(30, -30);
	delay_ms(600);
	set_motors(0, 0);
	set_motors(50, 50);
	delay_ms(150);
	g_w2_position = read_line(g_w2_sensors, IR_EMITTERS_ON);
	delay_ms(500);
}

//180 turn in grid
void w2_grid_rotation_full() {
	set_motors(60, -60);
	delay_ms(540);
	set_motors(10, 10);
	g_w2_position = read_line(g_w2_sensors, IR_EMITTERS_ON);
}

//left turn in grid
void w2_grid_rotation_half_left() {
	set_motors(-30, 30);
	delay_ms(600);
	set_motors(10, 10);
	g_w2_position = read_line(g_w2_sensors, IR_EMITTERS_ON);
}

//right turn in grid
void w2_grid_rotation_half_right() {
	set_motors(30, -30);
	delay_ms(600);
	set_motors(10, 10);
	g_w2_position = read_line(g_w2_sensors, IR_EMITTERS_ON);
}
