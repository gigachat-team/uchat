#include "../inc/libmx.h"

void *mx_memrchr(const void *s, int c, size_t n) {
    unsigned char *s_s = (unsigned char *)s;
    for (int i = n - 1; i >= 0; i--) {
        if (s_s[i] == c) {
            return s_s + i;
        }
    }
    return NULL;
}

