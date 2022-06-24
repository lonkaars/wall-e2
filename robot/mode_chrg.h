#pragma once

/** @file mode_chrg.h */

/**
 * charge station mode
 *
 * go to the charging station transition in the grid, and continue until a
 * black circle is found
 */
void w2_mode_chrg();

/** called when mode is switched to charge station mode */
void w2_mode_chrg_onswitch();
