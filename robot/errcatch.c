#include "errcatch.h"

void w2_errcatch_main() {}

void w2_errcatch_throw_msg(enum w2_e_errorcodes code, uint16_t length, const char *message) {}

void w2_errcatch_throw(enum w2_e_errorcodes code) { w2_errcatch_throw_msg(code, 0, ""); }
