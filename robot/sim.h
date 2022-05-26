#pragma once

/** @file sim.h */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../shared/bin.h"
#include "../shared/protocol.h"

extern bool g_w2_sim_headless;

// debug fine-tuning
#define DBG_ENABLE_PRINTFUNC (1)
#define DBG_ENABLE_SIMWARN (1)
#define DBG_ENABLE_SIMINFO (1)
#define DBG_ENABLE_CYCLEINFO (0)
#define DBG_ENABLE_SERIAL (1)

#define DBG_MAX_CYCLES (10)

// debug print options
#define DBG_BYTES_PER_LINE 16

// debug colors
#ifdef W2_HOST_LINUX
#define COL_BLK "\e[0;30m"
#define COL_RED "\e[0;31m"
#define COL_GRN "\e[0;32m"
#define COL_YEL "\e[0;33m"
#define COL_BLU "\e[0;34m"
#define COL_MAG "\e[0;35m"
#define COL_CYN "\e[0;36m"
#define COL_WHT "\e[0;37m"
#define COL_RST "\e[0m"
#endif
#ifdef W2_HOST_WIN32
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
#define simprintf(message, ...) if (!g_w2_sim_headless) printf(COL_RED "[SIM] " COL_RST message, ##__VA_ARGS__)
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
void serial_send(char *message, unsigned int length); // NOLINT
void serial_receive_ring(char *buffer, unsigned char size); // NOLINT
unsigned char serial_get_received_bytes(); // NOLINT
void set_motors(int left, int right); // NOLINT
unsigned char get_single_debounced_button_press(unsigned char buttons); // NOLINT
void qtr_read(unsigned int* sensor_values, unsigned char read_mode); // NOLINT
unsigned int analog_read(unsigned char channel); // NOLINT
void print(const char* str); // NOLINT

void w2_sim_setup(int argc, char **argv);
void w2_sim_cycle_begin();
void w2_sim_print_serial(w2_s_bin *data);

