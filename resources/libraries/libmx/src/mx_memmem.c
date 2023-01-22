#include "../inc/libmx.h"

void *mx_memmem(const void *big, size_t big_len, const void *little, size_t little_len) {
	if (little_len > big_len) {
        return NULL;
    }
	if (little_len == 0) {
        return (void *)big;
    }
    unsigned char *s_big = (unsigned char *)big;
    unsigned char *s_little = (unsigned char *)little;
	char *little_start = mx_memchr(big, s_little[0], big_len);
	if (little_start == NULL) {
        return NULL;
    }
	for (size_t i = 0; i < big_len; i++)
		if (mx_memcmp(s_big + i, little, little_len) == 0)
			return s_big + i;
	return NULL;
}

