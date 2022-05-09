#include "main.h"
#include "hypervisor.h"
#include "setup.h"

int main() {
	w2_setup_main();

	for (;;) w2_hypervisor_main();

	// satisfy compiler
	return 0;
}
