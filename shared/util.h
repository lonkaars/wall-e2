#pragma once

/** @file util.h */

#define W2_MIN(a, b) (((a) < (b)) ? (a) : (b))
#define W2_MAX(a, b) (((a) > (b)) ? (a) : (b))
#define W2_RANGE(min, val, max) W2_MIN(max, W2_MAX(val, min))

/** calculate exponential moving average */
unsigned long w2_util_exp_mov_avg(unsigned long current_avg, unsigned long new_meas);
/** return the sign of a number (-1 or 1) */
int w2_sign(int n);
/** return amount of newline characters */
unsigned int w2_newline_count(char *str, unsigned int len);
