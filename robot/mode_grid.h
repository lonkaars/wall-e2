#pragma once

/** @file mode_grid.h */

/**
 * warehouse mode
 *
 * processes orders from the order buffer
 */

enum orientation{
    North,
    East,
    South,
    West
} direction;

typedef struct {
    int x;
    int y;
} coordinates;

coordinates order[4];
coordinates location;
coordinates destination;

char xLocation;
char yLocation;

//LINE 25-68 CAN BE TAKEN AWAY WHEN USED WITH MODE_MAZE

// The 3pi include file must be at the beginning of any program that
// uses the Pololu AVR library and 3pi.
#include <pololu/3pi.h>

// This include file allows data to be stored in program space.  The
// ATmega168 has 16k of program space compared to 1k of RAM, so large
// pieces of static data should be stored in program space.
#include <avr/pgmspace.h>

unsigned int sensors[5]; // an array to hold sensor values
unsigned int position;
// Introductory messages.  The "PROGMEM" identifier causes the data to
// go into program space.
const char welcome_line1[] PROGMEM = " Pololu";
const char welcome_line2[] PROGMEM = "3\xf7 Robot";
const char demo_name_line1[] PROGMEM = "PID Line";
const char demo_name_line2[] PROGMEM = "follower";

// A couple of simple tunes, stored in program space.
const char welcome[] PROGMEM = ">g32>>c32";
const char go[] PROGMEM = "L16 cdegreg4";

// Data for generating the characters used in load_custom_characters
// and display_readings.  By reading levels[] starting at various
// offsets, we can generate all of the 7 extra characters needed for a
// bargraph.  This is also stored in program space.
const char levels[] PROGMEM = {
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b11111
};

void w2_mode_grid();
void full_rotation();
void grid_rotation_left();
void grid_rotation_right();
void grid_crossway_detection();
void gridFollowLine();
void orderOne();
void orderTwo();
void orderThree()
void orderFour()
void beginLocation()
void turn_North()
void turn_West()
void turn_South()
void turn_East()
void locationMessage()
void arrivedMessage()

