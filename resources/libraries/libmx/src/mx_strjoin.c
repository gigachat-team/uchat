#include "../inc/libmx.h"

char *mx_strjoin(char const *s1, char const *s2) {
	if (s1 == NULL && s2 != NULL) return mx_strdup(s2);
	if (s1 != NULL && s2 == NULL) return mx_strdup(s1);
	if (s1 == NULL && s2 == NULL) return NULL;
	int s1_len = mx_strlen(s1);
	int s2_len = mx_strlen(s2);
	char *new_str = mx_strnew(s1_len + s2_len);
	mx_strcpy(new_str, s1);
	mx_strcpy(new_str + s1_len, s2);
	return new_str;
}

