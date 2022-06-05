#pragma once

/** @file hypervisor.h */

#include <stdint.h>

#include "../shared/bool.h"

/** amount of parallel timers */
#define W2_HYPERVISOR_TIMER_COUNT (1)

#define W2_TIMER_PING (0)

extern uint64_t g_w2_hypervisor_cycles;
extern uint64_t g_w2_hypervisor_uptime_ms;

extern unsigned long g_w2_hypervisor_ema_sercomm_ms;
extern unsigned long g_w2_hypervisor_ema_errcatch_ms;
extern unsigned long g_w2_hypervisor_ema_io_ms;
extern unsigned long g_w2_hypervisor_ema_mode_ms;

extern unsigned int g_w2_ping_ms;
extern uint8_t g_w2_ping_id;
extern bool g_w2_ping_received;
extern bool g_w2_ping_timeout;
extern bool g_w2_connected;

/**
 * backbone of all other modules
 *
 * stores global state and controls when other modules run
 */
void w2_hypervisor_main();

/** start timer with label `label` */
void w2_hypervisor_time_start(uint8_t label);
/** stop timer with label `label` */
uint64_t w2_hypervisor_time_end(uint8_t label);
