#include "../inc/libmx.h"

void *mx_memcpy(void *restrict dst, const void *restrict src, size_t n) {
    char *s_dst = (char *)dst;
    char *s_src = (char *)src;

    for (size_t i = 0; i < n; i++) {
        s_dst[i] = s_src[i];
    }
    
    return dst;
}

