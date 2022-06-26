#include "main.h"
#include "../shared/consts.h"
#include "../shared/errcatch.h"
#include "commands.h"
#include "serial.h"
#include "setup.h"
#include "time.h"
#include "ui.h"

w2_s_client_state g_w2_state = {
	.ping_received = true,
	.map_height	   = W2_MAP_DEFAULT_HEIGHT,
	.map_width	   = W2_MAP_DEFAULT_WIDTH,
};

int main(int argc, char **argv) {
	w2_client_setup(argc, argv);

	while (1) {
		w2_serial_main();
		w2_errcatch_main();
		w2_ui_main();

		if (!g_w2_state.ping_received && w2_timer_end(W2_TIMER_PING) > W2_PING_TIMEOUT) {
			g_w2_state.ping_timeout = true;
			g_w2_state.connected	= false;
			w2_errcatch_throw(W2_E_WARN_PING_TIMEOUT);
		}

		if ((g_w2_state.ping_received && w2_timer_end(W2_TIMER_PING) > W2_PING_FREQUENCY) ||
			g_w2_state.ping_timeout) {
			g_w2_state.ping_timeout	 = false;
			g_w2_state.ping_received = false;
			w2_send_ping();
		}

		if (w2_timer_end(W2_TIMER_INFO) > W2_BATTERY_MEAS_FREQ) {
			w2_send_info();
			w2_timer_start(W2_TIMER_INFO);
		}
	}
}
