#pragma once

#include <stdint.h>

extern uint64_t g_w2_hypervisor_cycles;

/**
 * backbone of all other modules
 *
 * stores global variables and controls when other modules run
 */
void w2_hypervisor_main();
