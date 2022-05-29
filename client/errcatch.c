#include "../shared/errcatch.h"

void w2_errcatch_handle_error(w2_s_error *error) {
	// TODO: handle more error types
	switch (error->code) {
		case W2_E_WARN_UNCAUGHT_ERROR: {
			break;
		}
		default: {
			g_w2_error_uncaught = true;
#ifdef W2_SIM
			simwarn("Uncaught/unhandled error found with code 0x%02x\n", error->code);
#endif
		}
	}

	return;
}
