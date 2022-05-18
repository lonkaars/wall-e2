#pragma once
/**
 * helper file for binary data
 *
 * - fix endianness with functions inspired by UNIX arpa/inet.h
 * - convert uint16_t and uint32_t to w2_s_bin
 */

#include <stdint.h>

extern uint8_t g_w2_endianness;

#define W2_T_UINT8_T (0)
#define W2_T_UINT16_T (1)
#define W2_T_UINT32_T (2)

enum w2_e_struct_types {
	W2_ST_UINT8_T,
	W2_ST_UINT16_T,
	W2_ST_UINT32_T,
};

extern const uint8_t W2_STRUCT_T_SIZES[];

typedef struct {
	uint16_t bytes;
	uint8_t data[];
} w2_s_bin;

typedef struct {
	enum w2_e_struct_types type;
	uint16_t length;
	const uint8_t *data;
} w2_s_struct_property;

typedef struct {
	uint16_t length;
	w2_s_struct_property *properties[];
} w2_s_property_list;

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
