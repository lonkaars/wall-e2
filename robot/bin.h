#pragma once

#include <stdint.h>

typedef struct {
	uint16_t bytes;
	uint8_t data[];
} w2_s_bin;

extern uint8_t g_w2_endianness;


/**
 * helper file for binary data
 *
 * - fix endianness with functions inspired by UNIX arpa/inet.h
 */

/** convert 32-bit value from host endian to network (big-endian) */
uint32_t w2_bin_hton32(uint32_t h32);
/** convert 16-bit value from host endian to network (big-endian) */
uint16_t w2_bin_hton16(uint16_t h16);
/** convert 32-bit value from network (big-endian) to host endian */
uint32_t w2_bin_ntoh32(uint32_t n32);
/** convert 16-bit value from network (big-endian) to host endian */
uint16_t w2_bin_ntoh16(uint16_t n16);

