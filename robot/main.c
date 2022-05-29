#include "main.h"
#include "hypervisor.h"
#include "setup.h"
#ifdef W2_SIM
#include "sim.h"
#endif

#include <unistd.h>
int main() {
#ifdef W2_SIM
	w2_sim_setup();
#endif

	w2_setup_main();

	for (;;) w2_hypervisor_main();

	// satisfy compiler
	return 0;
}
