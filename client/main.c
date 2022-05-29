#include "setup.h"
#include "../shared/errcatch.h"
#include "main.h"
#include "serial.h"
#include "ui.h"

int main(int argc, char **argv) {
	w2_client_setup(argc, argv);

	while (1) {
		w2_serial_main();
		w2_errcatch_main();
		w2_ui_main();
	}
}
