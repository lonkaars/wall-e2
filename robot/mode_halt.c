#include "mode_halt.h"
#include "orangutan_shim.h"
#include "io.h"

// emergency stop
void w2_mode_halt() { w2_set_motors(0, 0); }
