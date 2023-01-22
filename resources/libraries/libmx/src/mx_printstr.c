#include "../inc/libmx.h"

void mx_printstr(const char *s) {
    int str_len = mx_strlen(s);
    write(1, s, str_len);
}

