#include "main.h"
#include "../shared/errcatch.h"
#include "serial.h"
#include "setup.h"
#include "ui.h"

w2_s_client_state g_w2_state;

int main(int argc, char **argv) {
	w2_client_setup(argc, argv);

	while (1) {
		w2_serial_main();
		w2_errcatch_main();
		w2_ui_main();
	}
}
