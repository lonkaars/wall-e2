#pragma once

#ifdef W2_LANG_NL_NL
#define W2_LANG_DEFAULT
#include "i18n/nl_nl.h"
#endif

#ifndef W2_LANG_DEFAULT
#define W2_LANG_DEFAULT
#include "i18n/en_us.h"
#endif

