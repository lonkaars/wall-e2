#pragma once

#include <stdint.h>

#include "protocol.h"

/** parse serial data byte by byte */
void w2_serial_parse(uint8_t byte);
