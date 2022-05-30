#pragma once

#include "../shared/modes.h"
#include "i18n.h"

#define W2_STRINGS_MODE_MAP_BUFFER_SIZE 32

extern char *g_w2_mode_strings[W2_MODE_COUNT];

void w2_strings_init();
