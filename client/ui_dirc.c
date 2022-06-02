#include "../shared/protocol.h"
#include "../shared/util.h"
#include "commands.h"
#include "ui.h"

/** decay modifier */
#define W2_DIRC_MOD ((double)0.95)
/** add value per key press */
#define W2_DIRC_ADD ((double)17.0)
/** padding */
#define W2_DIRC_PAD ((double)3.00)
/** average samples */
#define W2_DIRC_SPL ((unsigned int)14)
/** steering padding */
#define W2_DIRC_STP ((double)0.2)

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

void w2_ui_bar_graph(unsigned int y, unsigned int x, unsigned int width, double value) {
	char temp[width];
	temp[0]			= '|';
	temp[width - 1] = '|';
	for (unsigned int i = 0; i < width - 2; i++) temp[i + 1] = i < width * value ? '*' : ' ';

	mvaddnstr(y, x, temp, width);
}

void w2_ui_bar_graph_pm(unsigned int y, unsigned int x, unsigned int width, double value) {
	char temp[width];
	temp[0]			= '|';
	temp[width - 1] = '|';
	width -= 2;
	unsigned int hw = width / 2;
	if (value >= 0) {
		for (unsigned int i = 0; i < width; i++)
			temp[i + 1] = i < hw ? ' ' : (i - hw) < (hw * value) ? '*' : ' ';
	} else {
		for (unsigned int i = 0; i < width; i++)
			temp[i + 1] = i < hw ? ' ' : (i - hw) < (hw * value) ? '*' : ' ';
	}

	mvaddnstr(y, x, temp, width);
}

void w2_ui_dirc_paint(int left, int right) {
	mvaddstr(4, 0, "left drive:  ");
	w2_ui_bar_graph_pm(4, 13, g_w2_ui_width - 14, (double)left / 255);
	mvaddstr(5, 0, "right drive: ");
	w2_ui_bar_graph_pm(5, 13, g_w2_ui_width - 14, (double)right / 255);

	mvaddstr(7, 0,
			 "             controls:\n"
			 "\n"
			 " <q>      <w>       <e>   forward\n"
			 " <a>      <s>       <d>   backward\n"
			 "left     both      right\n");
}

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

	drive_l += drive_r * W2_DIRC_STP;
	drive_r += drive_l * W2_DIRC_STP;

	w2_send_dirc(drive_l, drive_r);
	w2_ui_dirc_paint(drive_l, drive_r);
}
