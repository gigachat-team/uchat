#include "../inc/libmx.h"

int mx_strarr_len(char **strarr) {
    if (strarr == NULL) {
        return 0;
    }
    int strarr_len = 0;
    for (; strarr[strarr_len] != NULL; strarr_len++) { }
    return strarr_len;
}

