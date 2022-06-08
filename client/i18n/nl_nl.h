#pragma once

#define W2_UI_CLI_USAGE "gebruik: %s <seriele port>\n"
#define W2_UI_CLI_SERPORT_ERROR "seriele port open fout\n"
#define W2_UI_CLI_INITSCR_FAIL "ncurses initscr() fout\n"
#define W2_UI_CONN_STAT_CONNECTED "verbonden"
#define W2_UI_CONN_STAT_DISCONNECTED "Verbindng verloren"
#define W2_UI_CONN_STAT_PING "ping"
#define W2_UI_BATT_STAT_BATTERY "batterij"
#define W2_UI_EXPT_STAT_WARNINGS "waarshuwing(en)"
#define W2_UI_EXPT_STAT_ERRORS "error(s)"

#define W2_UI_MODE_CHRG "oplaadstation"
#define W2_UI_MODE_DIRC "handbesturing"
#define W2_UI_MODE_GRID "grid"
#define W2_UI_MODE_HALT "noodstop"
#define W2_UI_MODE_LCAL "lijn kalibratie"
#define W2_UI_MODE_MAZE "doolhof"
#define W2_UI_MODE_SCAL "sensor kalibratie"
#define W2_UI_MODE_SPIN "natte vloer simulatie"

#define W2_UI_TAB_LABEL_START "info"
#define W2_UI_TAB_LABEL_DIRC "handbesturing"
#define W2_UI_TAB_LABEL_ERRCATCH "logs"
#define W2_UI_TAB_LABEL_MCFG "kaart"
#define W2_UI_TAB_LABEL_ORDERS "orders"
#define W2_UI_TAB_LABEL_MODES "modus instellen"

#define W2_UI_TAB_START_MESSAGE "" \
	"welcome to the wall-e2 console application!\n" \
	"this is client version " W2_BUILD_STR "\n" \
	"\n" \
	"this application is functionally similar to a BIOS.\n" \
	"here's a brief summary of keyboard commands:\n" \
	"\n" \
	"<tab>        switch to next tab\n" \
	"<ctrl-c>     exit\n" \
	"\n" \

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

#define W2_UI_ERROR_USR_W2_E_UNKNOWN "onbekende error code"
#define W2_UI_ERROR_USR_W2_E_CRIT_CONN_LOST "verbinding met de robot verloren"
#define W2_UI_ERROR_USR_W2_E_CRIT_COM_UNAVAILABLE "COM-port niet beschikbaar"
#define W2_UI_ERROR_USR_W2_E_CRIT_LINE_LOST "lijn verloren en niet mogelijk automatisch te detecteren"
#define W2_UI_ERROR_USR_W2_E_CRIT_OBSTACLE_STUCK "obstakel gedetecteerd, robot staat klem"
#define W2_UI_ERROR_USR_W2_E_CRIT_VERSION_INCOMPATIBLE "versie komt niet overeen, update de robot voor de nieuwste versie"
#define W2_UI_ERROR_USR_W2_E_WARN_BATTERY_LOW "batterij bijna leeg, de robot gaat naar het oplaadstation"
#define W2_UI_ERROR_USR_W2_E_WARN_OBSTACLE_DETECTED "obstakel gedetecteerd, robot wacht af"
#define W2_UI_ERROR_USR_W2_E_WARN_CYCLE_EXPIRED "maximale cyclus tijd overschreden"
#define W2_UI_ERROR_USR_W2_E_WARN_UNCAUGHT_ERROR "onopgemerkte fout gedetecteerd"
#define W2_UI_ERROR_USR_W2_E_WARN_ERR_BUFFER_FULL "error buffer zit vol"
#define W2_UI_ERROR_USR_W2_E_WARN_LINE_LOST "lijn verloren, initieer automatische lijn detectie"
#define W2_UI_ERROR_USR_W2_E_WARN_SERCOMM_BUFFER_FULL "seriele communicatie buffer is vol"
#define W2_UI_ERROR_USR_W2_E_WARN_VERSION_INCOMPATIBLE "versie komt niet overeen, dit kan leiden tot problemen"
#define W2_UI_ERROR_USR_W2_E_WARN_SERIAL_NOISY "ongeldige seriele informatie gedetecteerd, (ruisend kanaal / controleer de verbinding?)"
#define W2_UI_ERROR_USR_W2_E_WARN_MODE_HISTORY_BUFFER_IOB "mode geschiedenisbuffer index is buiten bereik"
#define W2_UI_ERROR_USR_W2_E_WARN_PING_TIMEOUT "ping time-out"

#define W2_UI_ORDER_CMD_HELP "help"
#define W2_UI_ORDER_CMD_START "start"
#define W2_UI_ORDER_CMD_COORDINATE "coördinaat"
#define W2_UI_ORDER_CMD_DONE "klaar"
#define W2_UI_ORDER_CMD_SEND "verstuur"

#define W2_UI_ORDER_MSG_ERROR "onbekend commando, type 'help' om een lijst te krijgen van alle mogelijke commando's\n\n"
#define W2_UI_ORDER_MSG_HELP \
	"commando's:\n" \
	"\n" \
	W2_UI_ORDER_CMD_HELP ": print deze lijst\n" \
	W2_UI_ORDER_CMD_START ": start een order\n" \
	W2_UI_ORDER_CMD_COORDINATE " <x> <y>: voeg een coördinaat toe aan het huidige order\n" \
	W2_UI_ORDER_CMD_DONE ": voltooi de huidige bestelling\n" \
	W2_UI_ORDER_CMD_SEND ": verstuur het laatst voltooide order naar de robot\n\n"
#define W2_UI_ORDER_MSG_ORDER_START_OK "order gestart\n\n"
#define W2_UI_ORDER_MSG_ORDER_START_ERR "order wordt al verwekt\n\n"
#define W2_UI_ORDER_MSG_ORDER_APPEND_OK "coördinaat toegevoegd aan bestelling\n\n"
#define W2_UI_ORDER_MSG_ORDER_APPEND_ERR "geen order actief\n\n"
#define W2_UI_ORDER_MSG_ORDER_DONE_OK "order opgeslagen\n\n"
#define W2_UI_ORDER_MSG_ORDER_DONE_ERR "geen order actief\n\n"
#define W2_UI_ORDER_MSG_ORDER_SENT "order verzonden naar de robot\n\n"

#define W2_UI_MODES_INFO \
    "Druk toetsen (0-9) voor:\n" \
    "\n" \
    "1 - kies doolhof modus\n" \
    "2 - kies grid modus\n" \
    "3 - noodstop\n" \
    "4 - kies oplaad modus\n" \
    "5 - natte vloer simulatie\n" \
    "6 - calibreer sensoren\n" \
    "\n" \
    "0 - vorige\n" \

