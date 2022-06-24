#include "mode_halt.h"
#include "orangutan_shim.h"

// emergency stop
void w2_mode_halt() { set_motors(0, 0); }
