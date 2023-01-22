#include "../inc/libmx.h"

int mx_get_substr_index(const char *str, const char *sub) {
    if (str == NULL || sub == NULL) {
        return -2;
    }
    int s1_len = mx_strlen(str);
	int s2_len = mx_strlen(sub);
	if (s2_len > s1_len) return -1;
	if (s2_len == 0) return -1;
	char *str_start = mx_strchr(str, sub[0]);
	if (str_start == NULL) return -1;
	for (int i = 0; i < s1_len; i++)
		if (mx_strncmp(str + i, sub, s2_len) == 0)
			return i;
	return -1;
}

