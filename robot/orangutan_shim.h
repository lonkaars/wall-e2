#pragma once

/** @file orangutan_shim.h */

#ifdef W2_SIM
#include "sim.h"
#else
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Warray-bounds"
#include <pololu/3pi.h>
#include <pololu/orangutan.h>
#pragma GCC diagnostic pop
#endif
