#pragma once

/** @file mode_lcal.h */

/**
 * calibration mode
 *
 * turns robot on its own axis 360 degress, and aligns the front sensors with
 * the line if found, else triggers halt mode (emergency)
 */
void w2_mode_lcal();
