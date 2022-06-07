#include "consts.h"

unsigned long w2_util_exp_mov_avg(unsigned long current_avg, unsigned long new_meas) {
	return (unsigned long)((((double)(current_avg)) * ((double)(1.f - W2_EMA_WEIGHT))) +
						   (((double)(new_meas)) * ((double)(W2_EMA_WEIGHT))));
}

int w2_sign(int n) { return (n > 0) - (n < 0); }

unsigned int w2_newline_count(char *str, unsigned int len) {
	unsigned int newlines = 0;
	for (unsigned int i = 0; i < len; i++)
		if (str[i] == '\n') newlines++;
	return newlines;
}
