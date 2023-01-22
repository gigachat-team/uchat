#include "../inc/libmx.h"

int mx_count_words(const char *str, char с) {
	if (str == NULL) {
		return -1;
	}
	int words_count = 0;
	bool current_is_word = false;
	for (int i = 0; str[i] != '\0'; i++) {
		if (str[i] != с && !current_is_word) {
			current_is_word = true;
			words_count++;
		} else if (str[i] == с)
			current_is_word = false;
	}
	return words_count;
}

