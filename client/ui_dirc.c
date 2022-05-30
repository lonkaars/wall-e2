#include "../shared/util.h"
#include "ui.h"

void w2_ui_bar_graph(unsigned int percent) {
	unsigned int width = g_w2_ui_width - 7;
	char bar[width];
	for(unsigned int i = 0; i < width - 2; i++) {
		bar[i+1] = i > (width - 2) * percent / 100 ? ' ' : '*';
	}
	bar[0] = '|';
	bar[width - 1] = '|';
	mvaddnstr(4, 7, bar, width);
}

#define W2_DIRC_MOD ((double) 0.95)
#define W2_DIRC_ADD ((double) 13.0)
#define W2_DIRC_PAD ((double) 1.10)
#define W2_DIRC_SPL ((unsigned int) 20)

int w2_avg(int* samples, unsigned int sample_count) {
	double total = 0;
	for (int i = 0; i < sample_count; i++) {
		total += (double) samples[i] / (double) sample_count;
	}
	return (int) total;
}

void w2_ui_dirc() {
	static unsigned int idx = 0;
	int ch = 0;
	unsigned int presses = 0;

	static double drive_l = 0.f;
	static int drive_l_avg[W2_DIRC_SPL] = {0};


	while ((ch = getch()) != -1) {
		if (ch == 'a') presses++;
	}

	drive_l *= W2_DIRC_MOD;
	drive_l += W2_DIRC_ADD * presses;
	drive_l = W2_MIN(100, drive_l);

	idx = (idx + 1) % W2_DIRC_SPL;
	drive_l_avg[idx] = (int) W2_MIN(100, drive_l * W2_DIRC_PAD);

	mvaddstr(4, 0, "drive: ");
	w2_ui_bar_graph(w2_avg(drive_l_avg, W2_DIRC_SPL));
}
