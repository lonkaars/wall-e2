#include "io.h"
#include <pololu/orangutan.h>


w2_io_all global;

void w2_io_main() {
    global.button[0] = get_single_debounced_button_press(BUTTON_A);
    global.button[1] = get_single_debounced_button_press(BUTTON_B);
    global.button[2] = get_single_debounced_button_press(BUTTON_C);
    global.button[3] = get_single_debounced_button_press(TOP_BUTTON);
    global.button[4] = get_single_debounced_button_press(BOTTOM_BUTTON);
    unsigned int sensor_values[5];
    qtr_read(sensor_values, QTR_EMITTERS_ON);
    for(int i = 0; i <5; i++){
         global.qtrSensor[i] = sensor_values[i];
    }
    // TODO average voltage over mutiple samples sensor
    global.batteryLevel = analog_read(BATTERY_PIN);  
    global.frontDetection = analog_read(FRONT_SENSOR_PIN); 
    global.sideDetection = analog_read(SIDE_SENSOR_PIN);

    set_motors(global.motor_left, global.motor_right);
    red_led(global.led_red);
    green_led(global.led_green);
    print_character(global.lcd);   
};

void w2_io_init(){
     pololu_3pi_init(2000):

     for(counter=0;counter<80;counter++)
        {
            if(counter < 20 || counter >= 60)
                {
                    global.motor_left=40;
                    global.motor_right=-40;
                }
            else
                {
                   global.motor_left=-40;
                   global.motor_right=40;    
                }

              calibrate_
              line_sensors(IR_EMITTERS_ON);
        
            delay_ms(20);
        }
    global.motor_left=0;
    global.motor_right=0;
}