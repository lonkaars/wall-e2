#include "mode_grid.h"

void w2_mode_grid() {

    initialize(); //only keep this when using this module on its own
    
    set_motors(0,0);

    //int gridMode = 0; //robot is in the grid

    //coordinates of the orders
    orderOne();
    orderTwo();
    orderThree();
    orderFour();
    
    beginLocation();

    for (int i = 0; i < 4; i++ ){
        
        destination.x = order[i].x;
        destination.y = order[i].y;
        
        locationMessage();
        delay(1000);    
        
        if (location.x != destination.x ){
            while(location.x != destination.x ){
                if (location.x > destination.x){
                    turn_West();
                    gridFollowLine();
                    grid_crossway_detection();
                    location.x--;
                    locationMessage();
                    if (location.x == destination.x){
                        arrivedMessage();
                    }
                }
                
                else if(location.x < destination.x){
                    turn_East();
                    
                    gridFollowLine();
                    grid_crossway_detection();
                    location.x++;
                    locationMessage();
                    if (location.x == destination.x){
                        arrivedMessage();
                    }
                }
            }
        }
            
        if (location.y != destination.y ){
            while(location.y != destination.y ){
                if (location.y > destination.y){
                    turn_South();
                    gridFollowLine();
                    grid_crossway_detection();
                    location.y--;
                    locationMessage();
                    if (location.y == destination.y){
                        arrivedMessage();
                    }
                }
                
                else if(location.y < destination.y){
                    turn_North();
                    gridFollowLine();
                    grid_crossway_detection();
                    location.y++;
                    locationMessage();
                    if (location.y == destination.y){
                        arrivedMessage();
                    }
                }
            }
        }
    }
}

void full_rotation(){
    delay_ms(500);
    set_motors(60,-60);
    delay_ms(540);
    set_motors(0,0);
    position = read_line(sensors,IR_EMITTERS_ON);
    delay_ms(500);
}

void grid_rotation_left(){
    delay_ms(500);
    set_motors(-30,30);
    delay_ms(600);
    set_motors(0,0);
    position = read_line(sensors,IR_EMITTERS_ON);
    delay_ms(500);
}

void grid_rotation_right(){
    delay_ms(500);
    set_motors(30,-30);
    delay_ms(600);
    set_motors(0,0);
    position = read_line(sensors,IR_EMITTERS_ON);
    delay_ms(500);
}

void grid_crossway_detection(){
    set_motors(0,0);
    set_motors(50,50);
    delay_ms(150);  //150
    set_motors(0,0);
    position = read_line(sensors,IR_EMITTERS_ON);
    delay_ms(500);
}

//variation on "void w2_mode_maze()" 
void gridFollowLine(){
    unsigned int last_proportional=0;
    long integral=0;

    // This is the "main loop" - it will run forever.
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
        
        if(sensors[0] >= 500 && sensors[1] >= 250  && sensors[2] >= 500  &&  sensors[3] >= 250  &&sensors[4] >= 500){
            break;
        }
        else if (sensors[0] >= 500 && sensors[1] >= 200 && sensors[4] < 100){
            break;
        }
        else if(sensors[4] >= 500 && sensors[3] >= 200 && sensors[0] < 100){ //for the south and west borders of the grid
            break;
        }
        else if(sensors[4] >= 500 && sensors[3] >= 200 && sensors[2] <100 && sensors[0] < 100){
            break;
        }

        else{ 
            if(power_difference < 0 && (sensors[2] > 100 || sensors[3] > 100 || sensors[1] > 100) ){
                set_motors(max+power_difference, max);}
            else if( power_difference > 0 && ( sensors[2] > 100 || sensors[3] > 100 || sensors[1] > 100)){
                set_motors(max, max-power_difference);} 
        }                   
    }
}

//coördinates of the orders
void orderOne(){
    order[0].x = 1; //1
    order[0].y = 3; //0
}

void orderTwo(){
    order[1].x = 3; //2
    order[1].y = 2; //2
}

void orderThree(){
    order[2].x = 1; //0
    order[2].y = 4; //4
}

void orderFour(){
    order[3].x = 0; //3
    order[3].y = 0; //1
}

//setting coördinate and direction when entering the grid from the maze
void beginLocation(){
    location.x = 4;
    location.y = 0;
    direction = West;
}

void turn_North()
{
    clear();
    print("North");

    switch (direction)
    {
        case North:
        break;
        
        case East:
        grid_rotation_left(); 
        break;
        
        case South: 
        full_rotation();
        break;
        
        case West:
        grid_rotation_right();
        break;
    }   
    direction = North;
}

void turn_West()
{
    clear();
    print("West");
    
    switch (direction)
    {
        case West:
        break;
        
        case North:
        grid_rotation_left(); 
        break;
        
        case East:
        full_rotation();
        break;
        
        case South:
        grid_rotation_right();; 
        break;
    }   
    direction = West;
}

void turn_South()
{
    clear();
    print("South");

    switch (direction)
    {
        case South:
        break;
        
        case West:
        grid_rotation_left();
        break;
        
        case North: 
        full_rotation();
        break;
        
        case East:
        grid_rotation_right();; 
        break;
    }
    direction = South;
}

void turn_East()
{
    clear();
    print("East");

    switch (direction)
    {
        case East:
        break;
        
        case South:
        grid_rotation_left(); 
        break;
        
        case West:
        full_rotation();
        break;
        
        case North:
        grid_rotation_right();; 
        break;
    }
    direction = East;
}

void locationMessage(){
    clear();
    print_long(location.x);
    print(",");
    print_long(location.y);
    delay(200); //1000
}

void arrivedMessage(){
    clear();
    print("ARRIVED");
}

//!UNDER THIS CAN ALL BE TAKEN AWAY, THIS IS USED IN MODE_MAZE & Callibration!

// Initializes the 3pi, displays a welcome message, calibrates, and
// plays the initial music.
// Initializes the 3pi, displays a welcome message, calibrates, and
// plays the initial music.
void initialize()
{
    unsigned int counter; // used as a simple timer
    
    // This must be called at the beginning of 3pi code, to set up the
    // sensors.  We use a value of 2000 for the timeout, which
    // corresponds to 2000*0.4 us = 0.8 ms on our 20 MHz processor.
    pololu_3pi_init(2000);
    load_custom_characters(); // load the custom characters
    
    // Play welcome music and display a message
    print_from_program_space(welcome_line1);
    lcd_goto_xy(0,1);
    print_from_program_space(welcome_line2);
    play_from_program_space(welcome);
    delay_ms(1000);

    clear();
    print_from_program_space(demo_name_line1);
    lcd_goto_xy(0,1);
    print_from_program_space(demo_name_line2);
    delay_ms(1000);

    // Display battery voltage and wait for button press
    while(!button_is_pressed(BUTTON_B))
    {
        int bat = read_battery_millivolts();

        clear();
        print_long(bat);
        print("mV");
        lcd_goto_xy(0,1);
        print("Press B");

        delay_ms(100);
    }

    // Always wait for the button to be released so that 3pi doesn't
    // start moving until your hand is away from it.
    wait_for_button_release(BUTTON_B);
    delay_ms(1000);

    // Auto-calibration: turn right and left while calibrating the
    // sensors.
    for(counter=0;counter<80;counter++)
    {
        if(counter < 20 || counter >= 60)
        set_motors(40,-40);
        else
        set_motors(-40,40);

        // This function records a set of sensor readings and keeps
        // track of the minimum and maximum values encountered.  The
        // IR_EMITTERS_ON argument means that the IR LEDs will be
        // turned on during the reading, which is usually what you
        // want.
        calibrate_line_sensors(IR_EMITTERS_ON);

        // Since our counter runs to 80, the total delay will be
        // 80*20 = 1600 ms.
        delay_ms(20);
    }
    set_motors(0,0);

    // Display calibrated values as a bar graph.
    while(!button_is_pressed(BUTTON_B))
    {
        // Read the sensor values and get the position measurement.
        unsigned int position = read_line(sensors,IR_EMITTERS_ON);

        // Display the position measurement, which will go from 0
        // (when the leftmost sensor is over the line) to 4000 (when
        // the rightmost sensor is over the line) on the 3pi, along
        // with a bar graph of the sensor readings.  This allows you
        // to make sure the robot is ready to go.
        clear();
        print_long(position);
        lcd_goto_xy(0,1);
        display_readings(sensors);

        delay_ms(100);
    }
    wait_for_button_release(BUTTON_B);

    clear();

    print("Go!");

    // Play music and wait for it to finish before we start driving.
    play_from_program_space(go);
    while(is_playing());
}

// This function loads custom characters into the LCD.  Up to 8
// characters can be loaded; we use them for 7 levels of a bar graph.
void load_custom_characters()
{
    lcd_load_custom_character(levels+0,0); // no offset, e.g. one bar
    lcd_load_custom_character(levels+1,1); // two bars
    lcd_load_custom_character(levels+2,2); // etc...
    lcd_load_custom_character(levels+3,3);
    lcd_load_custom_character(levels+4,4);
    lcd_load_custom_character(levels+5,5);
    lcd_load_custom_character(levels+6,6);
    clear(); // the LCD must be cleared for the characters to take effect
}

// This function displays the sensor readings using a bar graph.
void display_readings(const unsigned int *calibrated_values)
{
    unsigned char i;

    for(i=0;i<5;i++) {
        // Initialize the array of characters that we will use for the
        // graph.  Using the space, an extra copy of the one-bar
        // character, and character 255 (a full black box), we get 10
        // characters in the array.
        const char display_characters[10] = {' ',0,0,1,2,3,4,5,6,255};

        // The variable c will have values from 0 to 9, since
        // calibrated values are in the range of 0 to 1000, and
        // 1000/101 is 9 with integer math.
        char c = display_characters[calibrated_values[i]/101];

        // Display the bar graph character.
        print_character(c);
    }
}

void full_rotation(){
    set_motors(0,0);
    delay_ms(500);
    set_motors(60,-60);
    delay_ms(540);
    set_motors(0,0);
    position = read_line(sensors,IR_EMITTERS_ON);
    delay_ms(500);
}
