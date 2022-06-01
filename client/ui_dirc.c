#include "../shared/protocol.h"
#include "../shared/util.h"
#include "commands.h"
#include "ui.h"

void w2_ui_bar_graph(unsigned int percent) {
	unsigned int width = g_w2_ui_width - 7;
	char bar[width];
	for (unsigned int i = 0; i < width - 2; i++) {
		bar[i + 1] = i > (width - 2) * percent / 100 ? ' ' : '*';
	}
	bar[0]		   = '|';
	bar[width - 1] = '|';
	mvaddnstr(4, 7, bar, width);
}

#define W2_DIRC_MOD ((double)0.95)
#define W2_DIRC_ADD ((double)13.0)
#define W2_DIRC_PAD ((double)1.10)
#define W2_DIRC_SPL ((unsigned int)20)

int w2_avg(int *samples, unsigned int sample_count) {
	double total = 0;
	for (int i = 0; i < sample_count; i++) {
		total += (double)samples[i] / (double)sample_count;
	}
	return (int)total;
}

#define W2_DIRC_MOTOR_DRIVER(name)                                                                 \
	int w2_dirc_motor_##name(unsigned int forward, unsigned int backward) {                        \
		static unsigned int idx = 0;                                                               \
                                                                                                   \
		static double drive				  = 0.f;                                                   \
		static int drive_avg[W2_DIRC_SPL] = {0};                                                   \
                                                                                                   \
		drive *= W2_DIRC_MOD;                                                                      \
		drive += W2_DIRC_ADD * forward + -W2_DIRC_ADD * backward;                                  \
		drive = W2_RANGE(-254, drive, 255);                                                        \
                                                                                                   \
		idx			   = (idx + 1) % W2_DIRC_SPL;                                                  \
		drive_avg[idx] = (int)W2_RANGE(-254, drive * W2_DIRC_PAD, 255);                            \
                                                                                                   \
		return w2_avg(drive_avg, W2_DIRC_SPL);                                                     \
	}

W2_DIRC_MOTOR_DRIVER(l);
W2_DIRC_MOTOR_DRIVER(r);

void w2_ui_dirc_init() { w2_send_mode(W2_M_DIRC); }

void w2_ui_dirc(bool first) {
	if (first) w2_ui_dirc_init();
	int ch			= 0;
	unsigned int lb = 0;
	unsigned int lf = 0;
	unsigned int rb = 0;
	unsigned int rf = 0;
	while ((ch = getch()) != -1) {
		if (ch == 'a' || ch == 's') lb++;
		if (ch == 'q' || ch == 'w') lf++;
		if (ch == 'd' || ch == 's') rb++;
		if (ch == 'e' || ch == 'w') rf++;
	}

	int drive_l = w2_dirc_motor_l(lf, lb);
	int drive_r = w2_dirc_motor_r(rf, rb);

	char temp[32] = {0};
	sprintf(temp, "l: %04i, r: %04i", drive_l, drive_r);
	mvaddstr(4, 0, temp);

	w2_send_dirc(drive_l, drive_r);
}
