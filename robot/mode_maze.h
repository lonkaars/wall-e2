#pragma once

/**
 * maze mode
 *
 * finds route out of maze
 */
unsigned int sensors[5]; // an array to hold sensor values
unsigned int position;
unsigned int last_proportional=0;
long integral=0;
void w2_mode_maze();
