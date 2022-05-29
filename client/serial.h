#pragma once

#include "../shared/bool.h"

/** @file serial.h */

/**
 * read byte from serial port
 *
 * @return -1 if read fails, else char read
 */
int w2_serial_read();
/** write `data` with length `length` to serial port */
bool w2_serial_write(char *data, uint8_t length);
/** open serial port */
bool w2_serial_open(const char *port_name);
/** close serial port */
void w2_serial_close();
