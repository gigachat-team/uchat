#include "../inc/libmx.h"

void mx_reverse_array(char **strarr) {
	char *temp;
    for (int start = 0, end = mx_strarr_len(strarr) - 1; start < end; start++, end--) {
        temp = strarr[start];
		strarr[start] = strarr[end];
		strarr[end] = temp;
    }
}

