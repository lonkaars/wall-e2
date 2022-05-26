#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "bin.h"
#include "consts.h"

#define W2_SERIAL_START_BYTE 0xff

#define W2_CMDDIR_RX 0
#define W2_CMDDIR_TX 1

#define W2_CMD_CODE_MASK (~1)
#define W2_CMD_DIRECTION_MASK (1)

#define W2_CMD_COUNT 28
typedef enum {
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
} w2_e_scmds;

#pragma pack(push, 1)

/** momentary button input struct */
typedef struct {
	bool pressed;
} w2_s_i_push;

/** qtr contrast sensor input struct */
typedef struct {
	uint16_t range;
} w2_s_i_contrast;

/** distance sensor input struct */
typedef struct {
	uint16_t detection;
} w2_s_i_distance;

/** battery input struct */
typedef struct {
	uint16_t charge_level;
} w2_s_i_battery;

/** motor output struct */
typedef struct {
	int speed;
} w2_s_o_motor;

/** underside led output struct */
typedef struct {
	bool on;
} w2_s_o_led;

/** lcd output struct */
typedef struct {
	char text[16];
} w2_s_o_display;

/** struct containing all i/o */
typedef struct {
	w2_s_i_push button[5];
	w2_s_i_contrast qtr[5];
	w2_s_i_distance front_distance;
	w2_s_i_distance side_distance;
	w2_s_i_battery battery;

	w2_s_o_motor motor_left;
	w2_s_o_motor motor_right;
	w2_s_o_led led_red;
	w2_s_o_led led_green;
	w2_s_o_display lcd;
} w2_s_io_all;

typedef struct {
	uint8_t opcode;
	uint8_t id;
} w2_s_cmd_ping_rx;

typedef struct {
	uint8_t opcode;
	uint8_t id;
} w2_s_cmd_ping_tx;

typedef struct {
	uint8_t opcode;
	uint8_t error;
	uint8_t length;
	uint8_t message[];
} w2_s_cmd_expt_tx;

typedef struct {
	uint8_t opcode;
	uint8_t mode;
} w2_s_cmd_mode_rx;

typedef struct {
	uint8_t opcode;
	uint8_t mode;
} w2_s_cmd_mode_tx;

typedef struct {
	uint8_t opcode;
	uint8_t speed;
} w2_s_cmd_sped_rx;

typedef struct {
	uint8_t opcode;
	uint16_t left;
	uint16_t right;
} w2_s_cmd_dirc_rx;

typedef struct {
	uint8_t opcode;
	uint32_t position;
	uint8_t orientation;
} w2_s_cmd_cord_rx;

typedef struct {
	uint8_t opcode;
	uint32_t position;
	uint8_t orientation;
} w2_s_cmd_cord_tx;

typedef struct {
	uint8_t opcode;
	uint32_t id;
	uint32_t position;
} w2_s_cmd_bomd_rx;

typedef struct {
	uint8_t opcode;
	uint32_t id;
	uint8_t status;
} w2_s_cmd_bomd_tx;

typedef struct {
	uint8_t opcode;
	uint8_t type;
} w2_s_cmd_sres_rx;

typedef struct {
	uint16_t position;
	uint8_t kind;
} w2_s_cmd_mcfg_feature;

typedef struct {
	uint8_t opcode;
	uint8_t width;
	uint8_t height;
	uint8_t length;
	w2_s_cmd_mcfg_feature features[];
} w2_s_cmd_mcfg_rx;

typedef struct {
	uint8_t opcode;
} w2_s_cmd_sens_rx;

typedef struct {
	uint8_t opcode;
	w2_s_io_all io;
} w2_s_cmd_sens_tx;

typedef struct {
	uint8_t opcode;
} w2_s_cmd_info_rx;

typedef struct {
	uint8_t opcode;
	uint8_t build_str[32];
	uint8_t errcatch_ms;
	uint8_t io_ms;
	uint8_t sercomm_ms;
	uint8_t mode_ms;
	uint32_t uptime_s;
} w2_s_cmd_info_tx;

typedef struct {
} w2_s_cmd_disp_rx;

typedef struct {
} w2_s_cmd_play_rx;

typedef struct {
} w2_s_cmd_cled_rx;

#pragma pack(pop)

/** stores message handlers in array with opcode as index */
extern void (*g_w2_cmd_handlers[W2_CMD_COUNT])(w2_s_bin *);
/** fills g_w2_cmd_handlers with functions */
void w2_cmd_setup_handlers();

/** global handler for complete messages */
void w2_cmd_handler(uint8_t data[W2_SERIAL_READ_BUFFER_SIZE], uint8_t length);
/** calculate message length */
size_t w2_cmd_sizeof(uint8_t data[W2_SERIAL_READ_BUFFER_SIZE], uint8_t length);

/** handler for ping_rx (on complete message) */
void w2_cmd_ping_rx(w2_s_bin *data);
/** handler for ping_tx (on complete message) */
void w2_cmd_ping_tx(w2_s_bin *data);
/** handler for expt_tx (on complete message) */
void w2_cmd_expt_tx(w2_s_bin *data);
/** handler for mode_rx (on complete message) */
void w2_cmd_mode_rx(w2_s_bin *data);
/** handler for mode_tx (on complete message) */
void w2_cmd_mode_tx(w2_s_bin *data);
/** handler for sped_rx (on complete message) */
void w2_cmd_sped_rx(w2_s_bin *data);
/** handler for dirc_rx (on complete message) */
void w2_cmd_dirc_rx(w2_s_bin *data);
/** handler for cord_rx (on complete message) */
void w2_cmd_cord_rx(w2_s_bin *data);
/** handler for cord_tx (on complete message) */
void w2_cmd_cord_tx(w2_s_bin *data);
/** handler for bomd_rx (on complete message) */
void w2_cmd_bomd_rx(w2_s_bin *data);
/** handler for bomd_tx (on complete message) */
void w2_cmd_bomd_tx(w2_s_bin *data);
/** handler for sres_rx (on complete message) */
void w2_cmd_sres_rx(w2_s_bin *data);
/** handler for mcfg_rx (on complete message) */
void w2_cmd_mcfg_rx(w2_s_bin *data);
/** handler for sens_rx (on complete message) */
void w2_cmd_sens_rx(w2_s_bin *data);
/** handler for sens_tx (on complete message) */
void w2_cmd_sens_tx(w2_s_bin *data);
/** handler for info_rx (on complete message) */
void w2_cmd_info_rx(w2_s_bin *data);
/** handler for info_tx (on complete message) */
void w2_cmd_info_tx(w2_s_bin *data);
/** handler for disp_rx (on complete message) */
void w2_cmd_disp_rx(w2_s_bin *data);
/** handler for play_rx (on complete message) */
void w2_cmd_play_rx(w2_s_bin *data);
/** handler for cled_rx (on complete message) */
void w2_cmd_cled_rx(w2_s_bin *data);

/** calculate message length for expt_tx (incomplete message) */
size_t w2_cmd_expt_tx_sizeof(w2_s_bin *data);
/** calculate message length for mcfg_rx (incomplete message) */
size_t w2_cmd_mcfg_rx_sizeof(w2_s_bin *data);
