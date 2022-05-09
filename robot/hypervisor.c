#include <pololu/orangutan.h>

#include "consts.h"
#include "errcatch.h"
#include "hypervisor.h"
#include "io.h"
#include "modes.h"
#include "sercomm.h"

void w2_hypervisor_main() {
	w2_sercomm_main();
	w2_errcatch_main();
	w2_io_main();

	time_reset();
	w2_modes_main();
	unsigned long elapsed_ms = get_ms();
	if (elapsed_ms > W2_MAX_MODULE_CYCLE_MS) w2_errcatch_throw(W2_ERR_CYCLE_EXPIRED);
}
