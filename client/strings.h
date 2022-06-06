#pragma once

#include "../shared/modes.h"
#include "i18n.h"
#include "ui.h"

extern char *g_w2_mode_strings[W2_MODE_COUNT];
extern char *g_w2_tab_strings[W2_UI_TAB_COUNT];
extern char *g_w2_error_type_strings[4];
extern char *g_w2_error_internal_strings[0x100];
extern char *g_w2_error_user_strings[0x100];

void w2_strings_init();
