#include "main.h"
#include "hypervisor.h"
#include "setup.h"
#ifdef W2_SIM
#include "sim.h"
#endif

int main(int argc, char **argv) {
#ifdef W2_SIM
	w2_sim_setup(argc, argv);
#endif

	w2_setup_main();

	for (;;) w2_hypervisor_main();

	// satisfy compiler
	return 0;
}
