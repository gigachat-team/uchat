#include "../inc/libmx.h"

char *mx_strtrim(const char *str) {
	if (str == NULL) return NULL;
	int str_start_index = 0;
	for (int i = 0; i < str[i] != '\0'; ++i)
		if (mx_isspace(str[i]))
			str_start_index = i + 1;
		else break;

	int str_length = mx_strlen(str);
	int str_end_index = str_length - 1;
	for (int i = str_length - 1; i >= 0; --i)
		if (mx_isspace(str[i]))
			str_end_index = i - 1;
		else break;

	int new_str_length = str_end_index - str_start_index + 1;
	char *trimmed_str = mx_strnew(new_str_length);
	if (trimmed_str == NULL) return NULL;
	mx_strncpy(trimmed_str, str + str_start_index, new_str_length);
	return trimmed_str;
}

