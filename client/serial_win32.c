#ifdef W2_HOST_WIN32

#include "serial.h"

bool w2_serial_read(uint8_t *target, uint8_t bytes);
bool w2_serial_write(uint8_t *target, uint8_t bytes);
void w2_serial_open();
void w2_serial_close();

#endif
