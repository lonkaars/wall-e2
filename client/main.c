#include "serial.h"

#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv) {
	if (argc < 2) {
		printf("usage: %s <serial port>\n", argv[0]);
		return 1;
	}

	if (w2_serial_open(argv[1]) == 0) {
		printf("serial port open fout");
		return 1;
	}

	printf("writing...\n");
	bool success = w2_serial_write("\xff\x14", 2);
	printf("writing %s\n", success ? "succeeded" : "failed");

	printf("reading...\n");
	while (1) {
		int res = w2_serial_read();
		if (res == -1) continue;

		printf("%02x ", (uint8_t)res);
		fflush(stdout);
	}
}
