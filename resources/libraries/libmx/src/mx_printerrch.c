#include "../inc/libmx.h"

void mx_printerrch(const char c) {
    write(2, &c, 1);
}

