#pragma once

#define W2_UI_CLI_USAGE "usage: %s <serial port>\n"
#define W2_UI_CLI_SERPORT_ERROR "serial port open fout\n"
#define W2_UI_CLI_INITSCR_FAIL "ncurses initscr() failed\n"
#define W2_UI_CONN_STAT_CONNECTED "connected"
#define W2_UI_CONN_STAT_DISCONNECTED "disconnected"
#define W2_UI_CONN_STAT_PING "ping"
#define W2_UI_BATT_STAT_BATTERY "battery"
#define W2_UI_EXPT_STAT_WARNINGS "warning(s)"
#define W2_UI_EXPT_STAT_ERRORS "error(s)"

#define W2_UI_MODE_CHRG "charging station"
#define W2_UI_MODE_DIRC "direct control"
#define W2_UI_MODE_GRID "grid"
#define W2_UI_MODE_HALT "emergency stop"
#define W2_UI_MODE_LCAL "line calibration"
#define W2_UI_MODE_MAZE "maze"
#define W2_UI_MODE_SCAL "sensor calibration"
#define W2_UI_MODE_SPIN "wet floor simulation"

#define W2_UI_TAB_LABEL_START "info"
#define W2_UI_TAB_LABEL_DIRC "direct control"
#define W2_UI_TAB_LABEL_ERRCATCH "logs"
#define W2_UI_TAB_LABEL_MCFG "map"
#define W2_UI_TAB_LABEL_ORDERS "orders"
#define W2_UI_TAB_LABEL_MODE "set mode"

#define W2_UI_TAB_START_MESSAGE "" \
	"welcome to the wall-e2 console application!\n" \
	"this is client version " W2_BUILD_STR "\n" \
	"\n" \
	"this application is functionally similar to a BIOS.\n" \
	"here's a brief summary of keyboard commands:\n" \
	"\n" \
	"<tab>                         switch to next tab\n" \
	"<up>/<down>, <j>/<k>          select option\n" \
	"<enter>, <i>                  edit option\n" \
	"<home>, <g>                   scroll to top\n" \
	"<end>, <G>                    scroll to bottom\n" \
	"<escape>                      back\n" \
	"<q>                           exit\n" \
	"\n" \
	"tab shortcuts:\n" \
	"<N>  info                   <o>  orders\n" \
	"<S>  logs                   <M>  set mode\n" \
	"<d>  direct control         <m>  map\n"

#define W2_UI_ERROR_SEVERITY_CRIT "CRIT"
#define W2_UI_ERROR_SEVERITY_WARN "WARN"
#define W2_UI_ERROR_SEVERITY_INFO "INFO"
#define W2_UI_ERROR_SEVERITY_VERB "VERB"

#define W2_UI_ERROR_INT_W2_E_UNKNOWN "W2_E_UNKNOWN"
#define W2_UI_ERROR_INT_W2_E_CRIT_CONN_LOST "W2_E_CRIT_CONN_LOST"
#define W2_UI_ERROR_INT_W2_E_CRIT_COM_UNAVAILABLE "W2_E_CRIT_COM_UNAVAILABLE"
#define W2_UI_ERROR_INT_W2_E_CRIT_LINE_LOST "W2_E_CRIT_LINE_LOST"
#define W2_UI_ERROR_INT_W2_E_CRIT_OBSTACLE_STUCK "W2_E_CRIT_OBSTACLE_STUCK"
#define W2_UI_ERROR_INT_W2_E_CRIT_VERSION_INCOMPATIBLE "W2_E_CRIT_VERSION_INCOMPATIBLE"
#define W2_UI_ERROR_INT_W2_E_WARN_BATTERY_LOW "W2_E_WARN_BATTERY_LOW"
#define W2_UI_ERROR_INT_W2_E_WARN_OBSTACLE_DETECTED "W2_E_WARN_OBSTACLE_DETECTED"
#define W2_UI_ERROR_INT_W2_E_WARN_CYCLE_EXPIRED "W2_E_WARN_CYCLE_EXPIRED"
#define W2_UI_ERROR_INT_W2_E_WARN_UNCAUGHT_ERROR "W2_E_WARN_UNCAUGHT_ERROR"
#define W2_UI_ERROR_INT_W2_E_WARN_ERR_BUFFER_FULL "W2_E_WARN_ERR_BUFFER_FULL"
#define W2_UI_ERROR_INT_W2_E_WARN_LINE_LOST "W2_E_WARN_LINE_LOST"
#define W2_UI_ERROR_INT_W2_E_WARN_SERCOMM_BUFFER_FULL "W2_E_WARN_SERCOMM_BUFFER_FULL"
#define W2_UI_ERROR_INT_W2_E_WARN_VERSION_INCOMPATIBLE "W2_E_WARN_VERSION_INCOMPATIBLE"
#define W2_UI_ERROR_INT_W2_E_WARN_SERIAL_NOISY "W2_E_WARN_SERIAL_NOISY"
#define W2_UI_ERROR_INT_W2_E_WARN_MODE_HISTORY_BUFFER_IOB "W2_E_WARN_MODE_HISTORY_BUFFER_IOB"
#define W2_UI_ERROR_INT_W2_E_WARN_PING_TIMEOUT "W2_E_WARN_PING_TIMEOUT"

#define W2_UI_ERROR_USR_W2_E_UNKNOWN "unknown error code"
#define W2_UI_ERROR_USR_W2_E_CRIT_CONN_LOST "connection to robot lost"
#define W2_UI_ERROR_USR_W2_E_CRIT_COM_UNAVAILABLE "COM-port unavailable"
#define W2_UI_ERROR_USR_W2_E_CRIT_LINE_LOST "line lost and unable to be found automatically"
#define W2_UI_ERROR_USR_W2_E_CRIT_OBSTACLE_STUCK "obstacle detected, robot stuck"
#define W2_UI_ERROR_USR_W2_E_CRIT_VERSION_INCOMPATIBLE "major version mismatch detected, please update robot"
#define W2_UI_ERROR_USR_W2_E_WARN_BATTERY_LOW "battery low, going to charging station"
#define W2_UI_ERROR_USR_W2_E_WARN_OBSTACLE_DETECTED "obstacle detected, waiting"
#define W2_UI_ERROR_USR_W2_E_WARN_CYCLE_EXPIRED "maximum logic module cycle time exceeded"
#define W2_UI_ERROR_USR_W2_E_WARN_UNCAUGHT_ERROR "uncaught error occurred"
#define W2_UI_ERROR_USR_W2_E_WARN_ERR_BUFFER_FULL "error buffer full"
#define W2_UI_ERROR_USR_W2_E_WARN_LINE_LOST "line lost, trying to find line automatically"
#define W2_UI_ERROR_USR_W2_E_WARN_SERCOMM_BUFFER_FULL "serial communication buffer full"
#define W2_UI_ERROR_USR_W2_E_WARN_VERSION_INCOMPATIBLE "minor version mismatch detected, this might cause problems"
#define W2_UI_ERROR_USR_W2_E_WARN_SERIAL_NOISY "invalid serial data received (noisy channel / check connection?)"
#define W2_UI_ERROR_USR_W2_E_WARN_MODE_HISTORY_BUFFER_IOB "mode history buffer index out of bounds"
#define W2_UI_ERROR_USR_W2_E_WARN_PING_TIMEOUT "ping timed out"
