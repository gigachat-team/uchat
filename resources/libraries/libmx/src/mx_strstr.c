#include "../inc/libmx.h"

char *mx_strstr(const char *haystack, const char *needle) {
	int s1_len = mx_strlen(haystack);
	int s2_len = mx_strlen(needle);
	if (s2_len > s1_len) return NULL;
	if (s2_len == 0) return (char *)haystack;
	char *str_start = mx_strchr(haystack, needle[0]);
	if (str_start == NULL) return NULL;
	for (int i = 0; i < s1_len; i++)
		if (mx_strncmp(haystack + i, needle, s2_len) == 0)
			return (char *)(haystack + i);
	return NULL;
}

