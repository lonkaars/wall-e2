#include "mode_maze.h"
#include "orangutan_shim.h"
void full_rotation(){
	set_motors(0,0);
	delay_ms(500);
	set_motors(60,-60);
	delay_ms(540);
	set_motors(0,0);
	position = read_line(sensors,IR_EMITTERS_ON);
	delay_ms(500);
	

}

void half_rotation_left(){
	set_motors(0,0);
	set_motors(50,50);
	delay_ms(150);
	set_motors(-30,30);
	delay_ms(600);
	set_motors(0,0);
	position = read_line(sensors,IR_EMITTERS_ON);
	delay_ms(500);
		
}
void half_rotation_right(){
	set_motors(0,0);
	set_motors(50,50);
	delay_ms(150);
	set_motors(30,-30);
	delay_ms(600);
	set_motors(0,0);
	set_motors(50,50);
	delay_ms(150);
	position = read_line(sensors,IR_EMITTERS_ON);
	delay_ms(500);
}
void crossway_detection(){
	half_rotation_left();
}
void intersection_detection(){
	half_rotation_left();
}
void w2_mode_maze() {
    while(1)
	{    
		// Get the position of the line.  Note that we *must* provide
		// the "sensors" argument to read_line() here, even though we
		// are not interested in the individual sensor readings.
		position = read_line(sensors,IR_EMITTERS_ON);

		// The "proportional" term should be 0 when we are on the line.
		int proportional = ((int)position) - 2000;

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
		int power_difference = proportional/20 + integral/10000 + derivative*3/2;

		// Compute the actual motor settings.  We never set either motor
		// to a negative value.
		 
		const int max = 60;
		if(power_difference > max)
			power_difference = max;
		if(power_difference < -max)
			power_difference = -max;
		
		if(sensors[0] < 100 && sensors[1] <100 && sensors[2] < 100 &&  sensors[3] < 100 && sensors[4] < 100){
			// grid detectie
            /*set_motors(0,0);      
			delay_ms(450);
			set_motors(50,50);
			delay_ms(180);
			if ( sensors[2] >= 100 || sensors[3] >= 100 || sensors[1] >= 100 || sensors[0] >= 100 || sensors[4] >= 100)
			{
				set_motors(0,0);				
				delay_ms(15000);
				set_motors(50,50);
				delay_ms(180);
				if (sensors[2] >= 100 || sensors[3] >= 100 || sensors[1] >= 100 || sensors[0] >= 100 || sensors[4] >= 100 )
				{
					set_motors(0,0);
					delay_ms(1500);
					set_motors(50,50);
					delay_ms(180);
					if (sensors[2] >= 100 || sensors[3] >= 100 || sensors[1] >= 100 || sensors[0] >= 100 || sensors[4] >= 100)
					{
						print("GRID!");	
						set_motors(0,0);
						delay_ms(10000);
						
					}					
				}
				
			}
			else if(sensors[0] < 100 && sensors[1] <100 && sensors[2] < 100 &&  sensors[3] < 100 && sensors[4] < 100){*/
			full_rotation();
			//}
			
		}
		else if(sensors[0] >= 500 && sensors[1] >= 250  && sensors[2] >= 500  &&  sensors[3] >= 250  &&sensors[4] >= 500){
			crossway_detection();
		}
		//else if(sensors[0] >= 500  && sensors[2] < 50 &&sensors[4] >= 500){ 
			//intersection_detection();
		//}
		else if (sensors[0] >= 500 && sensors[1] >= 200 && sensors[4] < 100){
			half_rotation_left();
		}
		//else if(sensors[4] >= 500 && sensors[3] >= 200 && sensors[0] < 100){
			//half_rotation_right();
		//}
		else{ 
			if(power_difference < 0 && (sensors[2] > 100 || sensors[3] > 100 || sensors[1] > 100) )
				set_motors(max+power_difference, max);
			else if( power_difference > 0 && ( sensors[2] > 100 || sensors[3] > 100 || sensors[1] > 100)  )
				set_motors(max, max-power_difference);
			
		}
		       		
	}

	// This part of the code is never reached.  A robot should
	// never reach the end of its program, or unpredictable behavior
	// will result as random code starts getting executed.  If you
	// really want to stop all actions at some point, set your motors
	// to 0,0 and run the following command to loop forever:
	//
	// while(1);
}
}
