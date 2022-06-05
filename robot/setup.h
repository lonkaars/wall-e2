#pragma once

/** @file setup.h */

/**
 * runs once at startup, plays beep when setup finishes
 *
 * configures:
 * - serial connection (wixel)
 * - lcd display
 * - underside leds
 */
void w2_setup_main();
