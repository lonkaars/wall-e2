#pragma once

/** @file sim.h */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../shared/bin.h"
#include "../shared/protocol.h"

// debug fine-tuning
#define DBG_ENABLE_PRINTFUNC (0)
#define DBG_ENABLE_SIMWARN (1)
#define DBG_ENABLE_SIMINFO (1)
#define DBG_ENABLE_CYCLEINFO (0)
#define DBG_ENABLE_SERIAL (0)

#define DBG_CYCLE_DELAY (10e3)
#define DBG_MAX_CYCLES (-1)

// debug print options
#define DBG_BYTES_PER_LINE 16

// debug colors
#ifdef DBG_ENABLE_COLOR
#define COL_BLK "\e[0;30m"
#define COL_RED "\e[0;31m"
#define COL_GRN "\e[0;32m"
#define COL_YEL "\e[0;33m"
#define COL_BLU "\e[0;34m"
#define COL_MAG "\e[0;35m"
#define COL_CYN "\e[0;36m"
#define COL_WHT "\e[0;37m"
#define COL_RST "\e[0m"
#else
#define COL_BLK ""
#define COL_RED ""
#define COL_GRN ""
#define COL_YEL ""
#define COL_BLU ""
#define COL_MAG ""
#define COL_CYN ""
#define COL_WHT ""
#define COL_RST ""
#endif

// debug stdout print macros
#define simprintf(message, ...) fprintf(stderr, COL_RED "[SIM] " COL_RST message, ##__VA_ARGS__)
#define simprint(message) simprintf(message "\n")
#define simprintfunc(name, fmt, ...) if (DBG_ENABLE_PRINTFUNC) { simprintf(COL_BLU "[FUNC] " \
		COL_CYN name COL_RST "(" COL_YEL fmt COL_RST ")\n", ##__VA_ARGS__); }
#define simwarn(message, ...) if (DBG_ENABLE_SIMWARN) { simprintf(COL_YEL "[WARN] " COL_RST message, ##__VA_ARGS__); }
#define siminfo(message, ...) if (DBG_ENABLE_SIMINFO) { simprintf(COL_MAG "[INFO] " COL_RST message, ##__VA_ARGS__); }

#define BUTTON_A 0
#define BUTTON_B 1
#define BUTTON_C 2
#define TOP_BUTTON 3
#define BOTTOM_BUTTON 4
#define QTR_EMITTERS_ON 0
#define IR_EMITTERS_ON 0

/**
 * simulates pololu library functions for local testing
 * NOLINT is so clang-tidy doesn't correct function names
 */
void time_reset(); // NOLINT
unsigned long get_ms(); // NOLINT
void red_led(unsigned char on); // NOLINT
void green_led(unsigned char on); // NOLINT
void clear(); // NOLINT
void play(const char *melody); // NOLINT
void serial_set_baud_rate(unsigned int rate); // NOLINT
void serial_send_blocking(char *message, unsigned int length); // NOLINT
void serial_receive_ring(char *buffer, unsigned char size); // NOLINT
unsigned char serial_get_received_bytes(); // NOLINT
void set_motors(int left, int right); // NOLINT
unsigned char get_single_debounced_button_press(unsigned char buttons); // NOLINT
void qtr_read(unsigned int* sensor_values, unsigned char read_mode); // NOLINT
unsigned int analog_read(unsigned char channel); // NOLINT
void print(const char* str); // NOLINT
void lcd_goto_xy(unsigned int x, unsigned int y); // NOLINT
void delay(unsigned long duration); // NOLINT
void delay_ms(unsigned long duration); // NOLINT
int read_battery_millivolts(); // NOLINT
unsigned long get_ticks(); // NOLINT
unsigned long ticks_to_microseconds(unsigned long num_ticks); // NOLINT
int read_line(); // NOLINT
void play_frequency(unsigned int freq, unsigned int duration, unsigned char volume); // NOLINT
void calibrate_line_sensors(unsigned char read_mode); // NOLINT
unsigned char pololu_3pi_init(unsigned int line_sensor_timeout); // NOLINT

void w2_sim_setup();
void w2_sim_cycle_begin();
void w2_sim_print_serial(w2_s_bin *data);

