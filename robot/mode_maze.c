#include "mode_maze.h"
#include "orangutan_shim.h"
#include "movement.h"
#include "transition.h"

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
		// grid detectie
		/*set_motors(0,0);
		delay_ms(450);
		set_motors(50,50);
		delay_ms(180);
		if ( g_w2_sensors[2] >= 100 || g_w2_sensors[3] >= 100 || g_w2_sensors[1] >= 100 ||
		g_w2_sensors[0] >= 100 || g_w2_sensors[4] >= 100)
		{
			set_motors(0,0);
			delay_ms(15000);
			set_motors(50,50);
			delay_ms(180);
			if (g_w2_sensors[2] >= 100 || g_w2_sensors[3] >= 100 || g_w2_sensors[1] >= 100 ||
		g_w2_sensors[0] >= 100
		|| g_w2_sensors[4] >= 100 )
			{
				set_motors(0,0);
				delay_ms(1500);
				set_motors(50,50);
				delay_ms(180);
				if (g_w2_sensors[2] >= 100 || g_w2_sensors[3] >= 100 || g_w2_sensors[1] >= 100 ||
		g_w2_sensors[0] >= 100 || g_w2_sensors[4] >= 100)
				{
					print("GRID!");
					set_motors(0,0);
					delay_ms(10000);

				}
			}

		}
		else if(g_w2_sensors[0] < 100 && g_w2_sensors[1] <100 && g_w2_sensors[2] < 100 &&
		g_w2_sensors[3] < 100 && g_w2_sensors[4] < 100){*/
		w2_full_rotation();
		//}

	} else if (g_w2_sensors[0] >= 500 && g_w2_sensors[1] >= 250 && g_w2_sensors[2] >= 500 &&
			   g_w2_sensors[3] >= 250 && g_w2_sensors[4] >= 500) {
		w2_crossway_detection();
	}
	// else if(g_w2_sensors[0] >= 500  && g_w2_sensors[2] < 50 &&g_w2_sensors[4] >= 500){
	// intersection_detection();
	//}
	else if (g_w2_sensors[0] >= 500 && g_w2_sensors[1] >= 200 && g_w2_sensors[4] < 100) {
		w2_half_rotation_left();
	}
	// else if(g_w2_sensors[4] >= 500 && g_w2_sensors[3] >= 200 && g_w2_sensors[0] < 100){
	// half_rotation_right();
	//}
	else {
		if (power_difference < 0 &&
			(g_w2_sensors[2] > 100 || g_w2_sensors[3] > 100 || g_w2_sensors[1] > 100))
			set_motors(max + power_difference, max);
		else if (power_difference > 0 &&
				 (g_w2_sensors[2] > 100 || g_w2_sensors[3] > 100 || g_w2_sensors[1] > 100))
			set_motors(max, max - power_difference);
	}
}
