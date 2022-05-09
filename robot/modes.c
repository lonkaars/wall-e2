#include "modes.h"
#include "halt.h"

void (*g_w2_current_mode)() = &w2_mode_halt;

void w2_modes_main() { (*g_w2_current_mode)(); }
