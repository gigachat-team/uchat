#include "../inc/libmx.h"

void *mx_memchr(const void *s, int c, size_t n) {
    unsigned char *s_s = (unsigned char *)s;
    for (size_t i = 0; i < n; i++) {
        if (s_s[i] == c) {
            return s_s + i;
        }
    }
    return NULL;
}

