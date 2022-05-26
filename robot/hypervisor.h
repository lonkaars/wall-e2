#pragma once

/** @file hypervisor.h */

#include <stdint.h>

extern uint64_t g_w2_hypervisor_cycles;
extern uint64_t g_w2_hypervisor_uptime_ms;

extern unsigned long g_w2_hypervisor_ema_sercomm_ms;
extern unsigned long g_w2_hypervisor_ema_errcatch_ms;
extern unsigned long g_w2_hypervisor_ema_io_ms;
extern unsigned long g_w2_hypervisor_ema_mode_ms;

/**
 * backbone of all other modules
 *
 * stores global variables and controls when other modules run
 */
void w2_hypervisor_main();
