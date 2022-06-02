#include "hypervisor.h"
#include "../shared/errcatch.h"
#include "../shared/util.h"
#include "io.h"
#include "modes.h"
#include "orangutan_shim.h"
#include "sercomm.h"

uint64_t g_w2_hypervisor_cycles							   = 0;
uint64_t g_w2_hypervisor_uptime_ms						   = 0;
unsigned long g_w2_hypervisor_ema_sercomm_ms			   = 0;
unsigned long g_w2_hypervisor_ema_errcatch_ms			   = 0;
unsigned long g_w2_hypervisor_ema_io_ms					   = 0;
unsigned long g_w2_hypervisor_ema_mode_ms				   = 0;
uint64_t g_w2_hypervisor_timers[W2_HYPERVISOR_TIMER_COUNT] = {0};

void w2_hypervisor_main() {
#ifdef W2_SIM
	w2_sim_cycle_begin();
	if (DBG_ENABLE_CYCLEINFO) siminfo("cycle start\n");
#endif

	g_w2_hypervisor_uptime_ms += get_ms();
	time_reset();

	w2_sercomm_main();
	unsigned long sercomm_time = get_ms();
	w2_errcatch_main();
	unsigned long errcatch_time = get_ms() - sercomm_time;
	// w2_io_main();
	unsigned long io_time = get_ms() - errcatch_time;
	w2_modes_main();
	unsigned long mode_time = get_ms() - io_time;

	// calculate exponential moving averages
	g_w2_hypervisor_ema_sercomm_ms =
		w2_util_exp_mov_avg(g_w2_hypervisor_ema_sercomm_ms, sercomm_time);
	g_w2_hypervisor_ema_errcatch_ms =
		w2_util_exp_mov_avg(g_w2_hypervisor_ema_errcatch_ms, errcatch_time);
	g_w2_hypervisor_ema_io_ms	= w2_util_exp_mov_avg(g_w2_hypervisor_ema_io_ms, io_time);
	g_w2_hypervisor_ema_mode_ms = w2_util_exp_mov_avg(g_w2_hypervisor_ema_mode_ms, mode_time);

	if (mode_time > W2_MAX_MODULE_CYCLE_MS) w2_errcatch_throw(W2_E_WARN_CYCLE_EXPIRED);

#ifdef W2_SIM
	if (DBG_ENABLE_CYCLEINFO) siminfo("cycle end\n");
	if (DBG_CYCLE_DELAY > 0) usleep(DBG_CYCLE_DELAY);

	if (DBG_MAX_CYCLES > -1 && g_w2_hypervisor_cycles > DBG_MAX_CYCLES) exit(0);
#endif

	g_w2_hypervisor_cycles++;
}

void w2_hypervisor_time_start(uint8_t label) {
	g_w2_hypervisor_timers[label] = g_w2_hypervisor_uptime_ms;
}

uint64_t w2_hypervisor_time_end(uint8_t label) {
	return g_w2_hypervisor_uptime_ms - g_w2_hypervisor_timers[label];
}
