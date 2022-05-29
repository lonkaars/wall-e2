#ifdef W2_HOST_LINUX

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

#include "../shared/consts.h"
#include "serial.h"

struct termios g_w2_tty;
struct termios g_w2_tty_old;
int g_w2_serial_handle;

char g_w2_serial_buffer[W2_SERIAL_READ_BUFFER_SIZE];
uint8_t g_w2_serial_buffer_index;
uint8_t g_w2_serial_buffer_head;

speed_t w2_baud_map(int baud) {
	switch (baud) {
		case 9600:
			return B9600;
		case 19200:
			return B19200;
		case 38400:
			return B38400;
		case 57600:
			return B57600;
		case 115200:
			return B115200;
		case 230400:
			return B230400;
		case 460800:
			return B460800;
		case 500000:
			return B500000;
		case 576000:
			return B576000;
		case 921600:
			return B921600;
		case 1000000:
			return B1000000;
		case 1152000:
			return B1152000;
		case 1500000:
			return B1500000;
		case 2000000:
			return B2000000;
		case 2500000:
			return B2500000;
		case 3000000:
			return B3000000;
		case 3500000:
			return B3500000;
		case 4000000:
			return B4000000;
		default:
			return B0;
	}
}

int w2_serial_read() {
	int return_val;
	int bytes = read(g_w2_serial_handle, &return_val, 1);
	return bytes != 1 ? -1 : (uint8_t)return_val;
}

bool w2_serial_write(char *data, uint8_t length) {
	return write(g_w2_serial_handle, data, length) == length;
}

bool w2_serial_open(const char *port_name) {
	g_w2_serial_handle = open(port_name, O_RDWR | O_NONBLOCK);
	if (g_w2_serial_handle < 0 || tcgetattr(g_w2_serial_handle, &g_w2_tty) != 0) return false;

	g_w2_tty_old = g_w2_tty;

	speed_t baud = w2_baud_map(W2_SERIAL_BAUD);
	cfsetospeed(&g_w2_tty, baud);
	cfsetispeed(&g_w2_tty, baud);

	g_w2_tty.c_cc[VMIN]	 = 0;
	g_w2_tty.c_cc[VTIME] = 0;

	cfmakeraw(&g_w2_tty);

	tcflush(g_w2_serial_handle, TCIFLUSH);

	if (tcsetattr(g_w2_serial_handle, TCSANOW, &g_w2_tty) != 0) return false;

	return true;
}

void w2_serial_close() { close(g_w2_serial_handle); }

#endif
