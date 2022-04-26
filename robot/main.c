#include <pololu/orangutan.h>
#include <stdlib.h>

int main() {
	play("L50 c>c");
	serial_set_baud_rate(9600);

	char *buf = malloc(20);
	unsigned int counter = 0;

	while (1) {
		serial_receive_blocking(buf, 1, 65e3);

		switch (buf[0]) {
			case 0x7f: {
				counter--;
				lcd_goto_xy(counter, 0);
				print(" ");
				lcd_goto_xy(counter, 0);
				break;
			}
			default: {
				print(&buf[0]);
				counter++;
				if (counter > 20) {
					counter = 0;
					lcd_goto_xy(0, 0);
				}
			}
		}
	}

	return 0;
}
