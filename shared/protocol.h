#pragma once

#include <memory.h>
#include <stdint.h>
#include <stdlib.h>

#include "bin.h"

#define W2_SERIAL_START_BYTE 0xff

#define W2_CMDDIR_RX 0
#define W2_CMDDIR_TX 1

#define W2_CMD_CODE_MASK (~1)
#define W2_CMD_DIRECTION_MASK (1)

enum w2_e_serial_commands {
	/** ping command */
	W2_CMD_PING = 0x00,
	/** exception command */
	W2_CMD_EXPT = 0x02,
	/** mode command */
	W2_CMD_MODE = 0x04,
	/** speed command */
	W2_CMD_SPED = 0x06,
	/** direct control command */
	W2_CMD_DIRC = 0x08,
	/** coordinate command */
	W2_CMD_CORD = 0x0a,
	/** backorder modify command */
	W2_CMD_BOMD = 0x0c,
	/** soft reset command */
	W2_CMD_SRES = 0x0e,
	/** map config command */
	W2_CMD_MCFG = 0x10,
	/** sensor data command */
	W2_CMD_SENS = 0x12,
	/** info command */
	W2_CMD_INFO = 0x14,
	/** display control command */
	W2_CMD_DISP = 0x16,
	/** play midi command */
	W2_CMD_PLAY = 0x18,
	/** control leds command */
	W2_CMD_CLED = 0x1a,
};

// TODO
// array met indicies die structs opslaan met eigenschappen over de protocol bericht
//
// belangrijke eigenschappen:
// lengte!!!
// generic struct (voor parsen)
// parse functie
// dump functie
//
//
// als het kan deze allemaal met macro's op deze manier definieren:
//
#define W2_PROTOCOL_CMD(name, direction, ...)
#define W2_PROTOCOL_DEFINE(a)
#define W2_PROTOCOL_DECLARE(a)
#define W2_PROTOCOL_PROP(type, name)

#define W2_CMDDIR_NAME_0 rx
#define W2_CMDDIR_NAME_1 tx

#define W2_CMDDIR(dir) W2_CMDDIR_NAME_##dir

#define W2_PROTOCOL_UINT8_T
#define W2_PROTOCOL_UINT16_T
#define W2_PROTOCOL_UINT32_T
#define W2_PROTOCOL_INT8_T
#define W2_PROTOCOL_INT16_T
#define W2_PROTOCOL_INT32_T

#define W2_PROTOCOL_UINT8_T_TYPE uint8_t
#define W2_PROTOCOL_UINT16_T_TYPE uint16_t
#define W2_PROTOCOL_UINT32_T_TYPE uint32_t
#define W2_PROTOCOL_INT8_T_TYPE int8_t
#define W2_PROTOCOL_INT16_T_TYPE int16_t
#define W2_PROTOCOL_INT32_T_TYPE int32_t

#define W2_PROTOCOL_UINT8_T_SIZE 1
#define W2_PROTOCOL_UINT16_T_SIZE 2
#define W2_PROTOCOL_UINT32_T_SIZE 4
#define W2_PROTOCOL_INT8_T_SIZE 1
#define W2_PROTOCOL_INT16_T_SIZE 2
#define W2_PROTOCOL_INT32_T_SIZE 4

#define W2_PROTOCOL_CMD_PING_RX                                                                    \
	W2_PROTOCOL_CMD(ping, W2_CMDDIR_RX,                                                            \
					W2_PROTOCOL_PROP(W2_PROTOCOL_UINT8_T, opcode)                                  \
						W2_PROTOCOL_PROP(W2_PROTOCOL_UINT8_T, id))

W2_PROTOCOL_DECLARE(W2_PROTOCOL_CMD_PING_RX)

typedef struct {
	uint8_t opcode;
	uint8_t id;
} w2_s_cmd_ping_rx;

w2_s_cmd_ping_rx *w2_protocol_parse_cmd_ping_rx(w2_s_bin *data);
