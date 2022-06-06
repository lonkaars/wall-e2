#pragma once

#include "../shared/errcatch.h"

#define W2_ERRCATCH_LOG_SIZE 256

extern w2_s_error *g_w2_error_log[W2_ERRCATCH_LOG_SIZE];
extern unsigned int g_w2_error_log_index;
