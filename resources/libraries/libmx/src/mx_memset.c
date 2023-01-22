#include "../inc/libmx.h"

void *mx_memset(void *b, int c, size_t len) {
    size_t i = 0;
    for (unsigned char *ptr = b; i < len; ptr++) {
        *ptr = c;
        i++;
    }
    return b;
}

