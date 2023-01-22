#include "../inc/libmx.h"

void *mx_memccpy(void *restrict dst, const void *restrict src, int c, size_t n) {
    for (size_t i = 0; i < n; i++) {
        ((char *)dst)[i] = ((char *)src)[i];
        if (((char *)dst)[i] == c) {
            return (char *)dst + i + 1;
        }
    }
    return NULL;
}

