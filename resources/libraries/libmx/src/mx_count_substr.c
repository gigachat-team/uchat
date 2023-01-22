#include "../inc/libmx.h"

int mx_count_substr(const char *str, const char *sub) {
	if (str == NULL || sub == NULL) {
		return -1;
	}
	int counter = 0;
	int sub_len = mx_strlen(sub);
	int str_len = mx_strlen(str);

	if (sub_len == 0) {
		return 0;
	}
	for (char *i = (char *)str; i < str + str_len;) {
		i = strstr(i, sub);
		if (i != NULL) {
			i += sub_len;
			counter++;
		} else
			return counter;
	}
	return counter;
}

