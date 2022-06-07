#include "strings.h"
#include "../shared/errcatch.h"

char *g_w2_mode_strings[W2_MODE_COUNT];
char *g_w2_tab_strings[W2_UI_TAB_COUNT];
char *g_w2_error_type_strings[4];
char *g_w2_error_internal_strings[0x100];
char *g_w2_error_user_strings[0x100];

void w2_strings_modes_init() {
	g_w2_mode_strings[W2_M_CHRG] = W2_UI_MODE_CHRG;
	g_w2_mode_strings[W2_M_DIRC] = W2_UI_MODE_DIRC;
	g_w2_mode_strings[W2_M_GRID] = W2_UI_MODE_GRID;
	g_w2_mode_strings[W2_M_HALT] = W2_UI_MODE_HALT;
	g_w2_mode_strings[W2_M_MAZE] = W2_UI_MODE_MAZE;
	g_w2_mode_strings[W2_M_SCAL] = W2_UI_MODE_SCAL;
	g_w2_mode_strings[W2_M_SPIN] = W2_UI_MODE_SPIN;
}

void w2_strings_tabs_init() {
	g_w2_tab_strings[W2_UI_TAB_START]	 = W2_UI_TAB_LABEL_START;
	g_w2_tab_strings[W2_UI_TAB_ERRCATCH] = W2_UI_TAB_LABEL_ERRCATCH;
	g_w2_tab_strings[W2_UI_TAB_DIRC]	 = W2_UI_TAB_LABEL_DIRC;
	g_w2_tab_strings[W2_UI_TAB_ORDERS]	 = W2_UI_TAB_LABEL_ORDERS;
	g_w2_tab_strings[W2_UI_TAB_MODES]	 = W2_UI_TAB_LABEL_MODES;
}

void w2_strings_errors_types() {
	g_w2_error_type_strings[0b00] = W2_UI_ERROR_SEVERITY_CRIT;
	g_w2_error_type_strings[0b01] = W2_UI_ERROR_SEVERITY_WARN;
	g_w2_error_type_strings[0b10] = W2_UI_ERROR_SEVERITY_INFO;
	g_w2_error_type_strings[0b11] = W2_UI_ERROR_SEVERITY_VERB;
}

void w2_strings_errors_internal() {
	g_w2_error_internal_strings[W2_E_CRIT_CONN_LOST] = W2_UI_ERROR_INT_W2_E_CRIT_CONN_LOST;
	g_w2_error_internal_strings[W2_E_CRIT_COM_UNAVAILABLE] =
		W2_UI_ERROR_INT_W2_E_CRIT_COM_UNAVAILABLE;
	g_w2_error_internal_strings[W2_E_CRIT_LINE_LOST] = W2_UI_ERROR_INT_W2_E_CRIT_LINE_LOST;
	g_w2_error_internal_strings[W2_E_CRIT_OBSTACLE_STUCK] =
		W2_UI_ERROR_INT_W2_E_CRIT_OBSTACLE_STUCK;
	g_w2_error_internal_strings[W2_E_CRIT_VERSION_INCOMPATIBLE] =
		W2_UI_ERROR_INT_W2_E_CRIT_VERSION_INCOMPATIBLE;
	g_w2_error_internal_strings[W2_E_WARN_BATTERY_LOW] = W2_UI_ERROR_INT_W2_E_WARN_BATTERY_LOW;
	g_w2_error_internal_strings[W2_E_WARN_OBSTACLE_DETECTED] =
		W2_UI_ERROR_INT_W2_E_WARN_OBSTACLE_DETECTED;
	g_w2_error_internal_strings[W2_E_WARN_CYCLE_EXPIRED] = W2_UI_ERROR_INT_W2_E_WARN_CYCLE_EXPIRED;
	g_w2_error_internal_strings[W2_E_WARN_UNCAUGHT_ERROR] =
		W2_UI_ERROR_INT_W2_E_WARN_UNCAUGHT_ERROR;
	g_w2_error_internal_strings[W2_E_WARN_ERR_BUFFER_FULL] =
		W2_UI_ERROR_INT_W2_E_WARN_ERR_BUFFER_FULL;
	g_w2_error_internal_strings[W2_E_WARN_LINE_LOST] = W2_UI_ERROR_INT_W2_E_WARN_LINE_LOST;
	g_w2_error_internal_strings[W2_E_WARN_SERCOMM_BUFFER_FULL] =
		W2_UI_ERROR_INT_W2_E_WARN_SERCOMM_BUFFER_FULL;
	g_w2_error_internal_strings[W2_E_WARN_VERSION_INCOMPATIBLE] =
		W2_UI_ERROR_INT_W2_E_WARN_VERSION_INCOMPATIBLE;
	g_w2_error_internal_strings[W2_E_WARN_SERIAL_NOISY] = W2_UI_ERROR_INT_W2_E_WARN_SERIAL_NOISY;
	g_w2_error_internal_strings[W2_E_WARN_MODE_HISTORY_BUFFER_IOB] =
		W2_UI_ERROR_INT_W2_E_WARN_MODE_HISTORY_BUFFER_IOB;
	g_w2_error_internal_strings[W2_E_WARN_PING_TIMEOUT] = W2_UI_ERROR_INT_W2_E_WARN_PING_TIMEOUT;
}

void w2_strings_errors_user() {
	g_w2_error_user_strings[W2_E_CRIT_CONN_LOST]	   = W2_UI_ERROR_USR_W2_E_CRIT_CONN_LOST;
	g_w2_error_user_strings[W2_E_CRIT_COM_UNAVAILABLE] = W2_UI_ERROR_USR_W2_E_CRIT_COM_UNAVAILABLE;
	g_w2_error_user_strings[W2_E_CRIT_LINE_LOST]	   = W2_UI_ERROR_USR_W2_E_CRIT_LINE_LOST;
	g_w2_error_user_strings[W2_E_CRIT_OBSTACLE_STUCK]  = W2_UI_ERROR_USR_W2_E_CRIT_OBSTACLE_STUCK;
	g_w2_error_user_strings[W2_E_CRIT_VERSION_INCOMPATIBLE] =
		W2_UI_ERROR_USR_W2_E_CRIT_VERSION_INCOMPATIBLE;
	g_w2_error_user_strings[W2_E_WARN_BATTERY_LOW] = W2_UI_ERROR_USR_W2_E_WARN_BATTERY_LOW;
	g_w2_error_user_strings[W2_E_WARN_OBSTACLE_DETECTED] =
		W2_UI_ERROR_USR_W2_E_WARN_OBSTACLE_DETECTED;
	g_w2_error_user_strings[W2_E_WARN_CYCLE_EXPIRED]   = W2_UI_ERROR_USR_W2_E_WARN_CYCLE_EXPIRED;
	g_w2_error_user_strings[W2_E_WARN_UNCAUGHT_ERROR]  = W2_UI_ERROR_USR_W2_E_WARN_UNCAUGHT_ERROR;
	g_w2_error_user_strings[W2_E_WARN_ERR_BUFFER_FULL] = W2_UI_ERROR_USR_W2_E_WARN_ERR_BUFFER_FULL;
	g_w2_error_user_strings[W2_E_WARN_LINE_LOST]	   = W2_UI_ERROR_USR_W2_E_WARN_LINE_LOST;
	g_w2_error_user_strings[W2_E_WARN_SERCOMM_BUFFER_FULL] =
		W2_UI_ERROR_USR_W2_E_WARN_SERCOMM_BUFFER_FULL;
	g_w2_error_user_strings[W2_E_WARN_VERSION_INCOMPATIBLE] =
		W2_UI_ERROR_USR_W2_E_WARN_VERSION_INCOMPATIBLE;
	g_w2_error_user_strings[W2_E_WARN_SERIAL_NOISY] = W2_UI_ERROR_USR_W2_E_WARN_SERIAL_NOISY;
	g_w2_error_user_strings[W2_E_WARN_MODE_HISTORY_BUFFER_IOB] =
		W2_UI_ERROR_USR_W2_E_WARN_MODE_HISTORY_BUFFER_IOB;
	g_w2_error_user_strings[W2_E_WARN_PING_TIMEOUT] = W2_UI_ERROR_USR_W2_E_WARN_PING_TIMEOUT;
}

void w2_strings_init() {
	w2_strings_errors_types();
	w2_strings_errors_internal();
	w2_strings_errors_user();
	w2_strings_modes_init();
	w2_strings_tabs_init();
}
