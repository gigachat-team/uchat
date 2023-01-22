#include "../inc/libmx.h"

char **mx_strsplit(char const *s, char c) {
	if (s == NULL) {
		return NULL;
	}
	int words_count = mx_count_words(s, c);
	if (words_count <= 0) {
		return NULL;
	}
	char **words = malloc((words_count + 1) * sizeof(char *));
	int words_arr_size = 0;
	int curr_word_start_index = -1;
	if (words == NULL)
		return NULL;
	for (int i = 0; ; ++i) {
		if (s[i] != c && curr_word_start_index == -1)
			curr_word_start_index = i;
		else if ((s[i] == c || s[i] == '\0') && curr_word_start_index != -1) {
			words[words_arr_size] = mx_strnew(i - curr_word_start_index);
			mx_strncpy(words[words_arr_size], s + curr_word_start_index, i - curr_word_start_index);
			curr_word_start_index = -1;
			words_arr_size++;
		}
		if (s[i] == '\0') break;
	}
	words[words_count] = NULL;
	return words;
}

