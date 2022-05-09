#pragma once

/**
 * runs once at startup, plays beep when setup finishes
 *
 * configures:
 * - serial connection (wixel)
 * - timer0 for cycle duration measurement
 * - lcd display
 * - underside leds
 */
void w2_setup_main();
