#include <stddef.h>

char *mx_strchr(const char *s, int c) {
	for (int i = 0; s[i] != '\0'; i++) {
		if (s[i] == c) {
			const char *pointer = &s[i];
			return (char *)pointer;
		}
	}
	return NULL;
}

