#ifdef W2_HOST_WIN32

#include "serial.h"

int w2_serial_read() {
    return 0x00;
}

bool w2_serial_write(char *data, uint8_t length) {
    return true;
}

bool w2_serial_open(const char *port_name) {
    return true;
}

void w2_serial_close() {
    return;
}

#endif
