#include "mode_halt.h"
#include "orangutan_shim.h"

void w2_mode_halt() {
	set_motors(0, 0);
}
