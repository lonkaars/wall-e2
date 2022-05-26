#pragma once

#define W2_MIN(a, b) (((a) < (b)) ? (a) : (b))
#define W2_MAX(a, b) (((a) > (b)) ? (a) : (b))
#define W2_RANGE(min, val, max) W2_MIN(max, W2_MAX(val, min))

unsigned long w2_util_exp_mov_avg(unsigned long current_avg, unsigned long new_meas);
