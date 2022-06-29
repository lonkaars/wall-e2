#include "mode_halt.h"
#include "io.h"
#include "orangutan_shim.h"

// emergency stop
void w2_mode_halt() { w2_set_motors(0, 0); }
