#include "../inc/libmx.h"

void mx_printerrn(const char *s, int n) {
    int s_len = mx_strlen(s);
	write(2, s, n > s_len ? s_len : n);
}

