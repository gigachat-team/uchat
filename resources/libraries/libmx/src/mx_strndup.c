#include "../inc/libmx.h"

char *mx_strndup(const char *s1, size_t n) {
	size_t str_len = mx_strlen(s1);
    int new_str_len = str_len > n ? n : str_len;

	char *new_str = mx_strnew(new_str_len);
	if (new_str == NULL) {
        return NULL;
    }
	mx_strncpy(new_str, s1, new_str_len);
	return new_str;
}

