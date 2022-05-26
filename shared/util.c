#include "consts.h"

unsigned long w2_util_exp_mov_avg(unsigned long current_avg, unsigned long new_meas) {
	return (unsigned long)((((double)(current_avg)) * ((double)(1.f - W2_EMA_WEIGHT))) +
						   (((double)(new_meas)) * ((double)(W2_EMA_WEIGHT))));
}