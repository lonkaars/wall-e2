#pragma once

/**
 * simulates pololu library functions for local testing
 */

void time_reset(); // NOLINT
unsigned long get_ms(); // NOLINT
void red_led(unsigned char on); // NOLINT
void green_led(unsigned char on); // NOLINT
void clear(); // NOLINT
void play(const char* melody); // NOLINT
void serial_set_baud_rate(unsigned int rate); // NOLINT
