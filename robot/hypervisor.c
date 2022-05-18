#include "hypervisor.h"
#include "errcatch.h"
#include "io.h"
#include "modes.h"
#include "orangutan_shim.h"
#include "sercomm.h"

void w2_hypervisor_main() {
#ifdef W2_SIM
	if (DBG_ENABLE_CYCLEINFO) siminfo("cycle start\n");
#endif

	time_reset();

	w2_sercomm_main();
	unsigned long sercomm_time = get_ms();
	w2_errcatch_main();
	unsigned long errcatch_time = get_ms() - sercomm_time;
	w2_io_main();
	unsigned long io_time = get_ms() - errcatch_time;
	w2_modes_main();
	unsigned long mode_time = get_ms() - io_time;

	if (mode_time > W2_MAX_MODULE_CYCLE_MS) w2_errcatch_throw(W2_E_WARN_CYCLE_EXPIRED);

#ifdef W2_SIM
	if (DBG_ENABLE_CYCLEINFO) siminfo("cycle end\n");
	usleep(100e3);
#endif
}
