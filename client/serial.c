#include <memory.h>

#include "../shared/protocol.h"
#include "../shared/serial_parse.h"
#include "main.h"
#include "serial.h"
#include "time.h"

void w2_serial_main() {
	int temp;
	while ((temp = w2_serial_read()) != -1) w2_serial_parse(temp);
}

void w2_cmd_ping_tx(w2_s_bin *data) {
	W2_CAST_BIN(w2_s_cmd_ping_tx, data, cast);

	if (g_w2_state.ping_received) return;
	if (g_w2_state.ping_id != cast->id) return;
	g_w2_state.ping			 = w2_timer_end(W2_TIMER_PING);
	g_w2_state.ping_received = true;

	printf("ping measured, %ims\n", g_w2_state.ping);
}

void w2_cmd_expt_tx(w2_s_bin *data) { printf("w2_cmd_expt_tx()\n"); }
void w2_cmd_mode_tx(w2_s_bin *data) { printf("w2_cmd_mode_tx()\n"); }
void w2_cmd_cord_tx(w2_s_bin *data) { printf("w2_cmd_cord_tx()\n"); }
void w2_cmd_bomd_tx(w2_s_bin *data) { printf("w2_cmd_bomd_tx()\n"); }
void w2_cmd_sens_tx(w2_s_bin *data) { printf("w2_cmd_sens_tx()\n"); }

void w2_cmd_info_tx(w2_s_bin *data) {
	memcpy(&g_w2_state.info, data->data, sizeof(w2_s_cmd_info_tx));
}

void w2_cmd_ping_rx(w2_s_bin *data) { return; }
void w2_cmd_mode_rx(w2_s_bin *data) { return; }
void w2_cmd_sped_rx(w2_s_bin *data) { return; }
void w2_cmd_dirc_rx(w2_s_bin *data) { return; }
void w2_cmd_cord_rx(w2_s_bin *data) { return; }
void w2_cmd_bomd_rx(w2_s_bin *data) { return; }
void w2_cmd_sres_rx(w2_s_bin *data) { return; }
void w2_cmd_mcfg_rx(w2_s_bin *data) { return; }
void w2_cmd_sens_rx(w2_s_bin *data) { return; }
void w2_cmd_info_rx(w2_s_bin *data) { return; }
void w2_cmd_disp_rx(w2_s_bin *data) { return; }
void w2_cmd_play_rx(w2_s_bin *data) { return; }
void w2_cmd_cled_rx(w2_s_bin *data) { return; }
