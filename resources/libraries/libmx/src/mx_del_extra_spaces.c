#include "../inc/libmx.h"

// char *mx_del_extra_spaces(const char *str) {
// 	char *trimmed_str = NULL;
// 	char *cleared_str = NULL;
// 	int trimmed_str_len = 0;
// 	int cleared_str_len = 0;
// 	int word_start_index = 0;
// 	bool current_is_word = true;

// 	if (str == NULL) return NULL;
// 	trimmed_str = mx_strtrim(str);
// 	if (trimmed_str == NULL) return NULL;
// 	trimmed_str_len = mx_strlen(trimmed_str);
// 	cleared_str = mx_strnew(trimmed_str_len);

// 	for (int i = 0; i <= trimmed_str_len; ++i) {
// 		if ((mx_isspace(trimmed_str[i]) || trimmed_str[i] == '\0') && current_is_word) {
// 			current_is_word = false;
// 			mx_strncpy(cleared_str + cleared_str_len, trimmed_str + word_start_index, i - word_start_index);
// 			cleared_str_len += i - word_start_index;
// 			if (i < trimmed_str_len) {
// 				mx_strncpy(cleared_str + cleared_str_len, " ", 1);
// 				cleared_str_len++;
// 			}
// 		}
// 		if (!current_is_word) {
// 			current_is_word = !mx_isspace(trimmed_str[i]);
// 			if (current_is_word) word_start_index = i;
// 		}
// 	}
// 	cleared_str[cleared_str_len] = '\0';
// 	mx_strdel(&trimmed_str);
// 	return cleared_str;
// }

