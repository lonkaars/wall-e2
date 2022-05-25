#pragma once

#define W2_CMDDIR_RX (0)
#define W2_CMDDIR_TX (1)

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
