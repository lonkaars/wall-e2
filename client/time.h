#pragma once

/** amount of parallel timers */
#define W2_CLIENT_TIMER_COUNT (4)
extern unsigned long g_w2_client_timers[W2_CLIENT_TIMER_COUNT];
typedef enum { W2_TIMER_PING = 0 } w2_e_client_timers;

void w2_timer_start(w2_e_client_timers label);
unsigned long w2_timer_end(w2_e_client_timers label);
