#pragma once
/**
 * helper file for binary data
 *
 * - fix endianness with functions inspired by UNIX arpa/inet.h
 * - convert uint16_t and uint32_t to w2_s_bin
 */

#include <stdint.h>

extern uint8_t g_w2_endianness;

typedef struct {
	uint16_t bytes;
	uint8_t data[];
} w2_s_bin;

/** allocate new w2_s_bin struct and fill with `*data` for `bytes` bytes */
w2_s_bin *w2_bin_s_alloc(uint16_t bytes, uint8_t *data);
/** concatenate 2 w2_s_bin structs, deallocates `a` and `b` */
w2_s_bin *w2_bin_s_cat(w2_s_bin *a, w2_s_bin *b);

w2_s_bin *w2_bin_from_uint8_t(uint8_t data);
w2_s_bin *w2_bin_from_uint16_t(uint16_t data);
w2_s_bin *w2_bin_from_uint32_t(uint32_t data);

/** convert 32-bit value from host endian to network (big-endian) */
uint32_t w2_bin_hton32(uint32_t h32);
/** convert 16-bit value from host endian to network (big-endian) */
uint16_t w2_bin_hton16(uint16_t h16);
/** convert 32-bit value from network (big-endian) to host endian */
uint32_t w2_bin_ntoh32(uint32_t n32);
/** convert 16-bit value from network (big-endian) to host endian */
uint16_t w2_bin_ntoh16(uint16_t n16);
