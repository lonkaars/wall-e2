#pragma once

/** @file serial_parse.h */

#include <stdint.h>

#include "bool.h"
#include "protocol.h"

#define W2_SERIAL_READ_SUCCESS true
#define W2_SERIAL_READ_FAILURE false

/**
 * parse serial data byte by byte
 * @return true if read success, false if read fails
 */
bool w2_serial_parse(uint8_t byte);
