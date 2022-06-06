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

