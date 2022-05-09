#include "hypervisor.h"
#include "errcatch.h"
#include "io.h"
#include "modes.h"
#include "sercomm.h"

void w2_hypervisor_main() {
	w2_sercomm_main();
	w2_errcatch_main();
	w2_io_main();

	// start timer
	w2_modes_main();
	// stop timer
	// throw error if cycle expired
}
