#include "../inc/libmx.h"

int mx_memcmp(const void *s1, const void *s2, size_t n) {
    unsigned char *s_s1 = (unsigned char *)s1;
    unsigned char *s_s2 = (unsigned char *)s2;
    for (size_t i = 0; i < n; i++) {
        if (s_s1[i] != s_s2[i]) {
            return s_s1[i] - s_s2[i];
        }
    }
    return 0;
}

