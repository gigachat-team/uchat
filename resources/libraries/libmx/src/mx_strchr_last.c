#include "../inc/libmx.h"

char *mx_strchr_last(const char *s, int c) {
    char *last_pointer = NULL;
    for (int i = 0; s[i] != '\0'; i++) {
		if (s[i] == c) {
            last_pointer = (char *)&s[i];
		}
	}
	return last_pointer;
}

