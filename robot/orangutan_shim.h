#pragma once

#ifdef W2_SIM
#include "sim.h"
#else
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Warray-bounds"
#include <pololu/orangutan.h>
#pragma GCC diagnostic pop
#endif
