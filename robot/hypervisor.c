#include "hypervisor.h"
#include "consts.h"
#include "errcatch.h"
#include "io.h"
#include "modes.h"
#include "orangutan_shim.h"
#include "sercomm.h"

void w2_hypervisor_main() {
	time_reset();

	w2_sercomm_main();
	unsigned long sercomm_time = get_ms();
	w2_errcatch_main();
	unsigned long errcatch_time = get_ms() - sercomm_time;
	w2_io_main();
	unsigned long io_time = get_ms() - errcatch_time;
	w2_modes_main();
	unsigned long mode_time = get_ms() - io_time;

#ifdef W2_SIM
	siminfo("sercomm:  %lums\n", sercomm_time);
	siminfo("errcatch: %lums\n", errcatch_time);
	siminfo("io:       %lums\n", io_time);
	siminfo("mode:     %lums\n", mode_time);

	usleep(100e3);
#endif

	if (mode_time > W2_MAX_MODULE_CYCLE_MS) w2_errcatch_throw(W2_ERR_CYCLE_EXPIRED);
}
