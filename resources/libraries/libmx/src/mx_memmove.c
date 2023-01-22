#include "../inc/libmx.h"

void *mx_memmove(void *dst, const void *src, size_t len) {
    char *s_dst = (char *)dst;
    char *s_src = (char *)src;
    char *src_copy = malloc(len * sizeof(char));

    for (size_t i = 0; i < len; i++) {
        src_copy[i] = s_src[i];
    }

    for (size_t i = 0; i < len; i++) {
        s_dst[i] = src_copy[i];
    }

    free(src_copy);

    return dst;
}

