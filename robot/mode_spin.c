#include "mode_spin.h"
#include "io.h"
#include "orangutan_shim.h"

// wet floor simulation
void w2_mode_spin() { w2_set_motors(255, -255); }
