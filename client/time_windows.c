#ifdef W2_HOST_WIN32

#include "time.h"

unsigned long w2_get_time() {
	return 0;
}

void w2_timer_start(w2_e_client_timers label) { g_w2_client_timers[label] = w2_get_time(); }

unsigned long w2_timer_end(w2_e_client_timers label) {
	return w2_get_time() - g_w2_client_timers[label];
}

#endif
