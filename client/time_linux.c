#ifdef W2_HOST_LINUX

#include <time.h>

#include "time.h"

unsigned long w2_get_time() {
	struct timespec now;
	clock_gettime(CLOCK_MONOTONIC, &now);
	return ((now.tv_sec * 1000) + (now.tv_nsec / 1000000));
}

void w2_timer_start(w2_e_client_timers label) { g_w2_client_timers[label] = w2_get_time(); }

unsigned long w2_timer_end(w2_e_client_timers label) {
	return w2_get_time() - g_w2_client_timers[label];
}

#endif
