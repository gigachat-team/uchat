#include "../inc/libmx.h"

char *mx_strcat(char *restrict s1, const char *restrict s2) {
	int s1_length = mx_strlen(s1);
	int s2_length = mx_strlen(s2);
	for (int i = 0; i <= s2_length; i++)
		s1[s1_length + i] = s2[i];
	return s1;
}

