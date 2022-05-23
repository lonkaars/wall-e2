#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// debug fine-tuning
#define DBG_ENABLE_PRINTFUNC (1)
#define DBG_ENABLE_SIMWARN (1)
#define DBG_ENABLE_SIMINFO (1)
#define DBG_ENABLE_CYCLEINFO (0)

// debug print options
#define DBG_BYTES_PER_LINE 16

// debug colors
#define COL_BLK "\e[0;30m"
#define COL_RED "\e[0;31m"
#define COL_GRN "\e[0;32m"
#define COL_YEL "\e[0;33m"
#define COL_BLU "\e[0;34m"
#define COL_MAG "\e[0;35m"
#define COL_CYN "\e[0;36m"
#define COL_WHT "\e[0;37m"
#define COL_RST "\e[0m"

// debug stdout print macros
#define simprintf(message, ...) printf(COL_RED "[SIM] " COL_RST message, ##__VA_ARGS__)
#define simprint(message) simprintf(message "\n")
#define simprintfunc(name, fmt, ...) if (DBG_ENABLE_PRINTFUNC) { simprintf(COL_BLU "[FUNC] " \
		COL_CYN name COL_RST "(" COL_YEL fmt COL_RST ")\n", ##__VA_ARGS__); }
#define simwarn(message, ...) if (DBG_ENABLE_SIMWARN) { simprintf(COL_YEL "[WARN] " COL_RST message, ##__VA_ARGS__); }
#define siminfo(message, ...) if (DBG_ENABLE_SIMINFO) { simprintf(COL_MAG "[INFO] " COL_RST message, ##__VA_ARGS__); }

/**
 * simulates pololu library functions for local testing
 * NOLINT is so clang-tidy doesn't correct function names
 */
void time_reset(); // NOLINT
unsigned long get_ms(); // NOLINT
void red_led(unsigned char on); // NOLINT
void green_led(unsigned char on); // NOLINT
void clear(); // NOLINT
void play(const char* melody); // NOLINT
void serial_set_baud_rate(unsigned int rate); // NOLINT
void serial_send(char* message, unsigned int length); // NOLINT
void serial_receive_ring(char* buffer, unsigned char size); // NOLINT
unsigned char serial_get_received_bytes(); // NOLINT
