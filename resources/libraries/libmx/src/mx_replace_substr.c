#include "../inc/libmx.h"

char *mx_replace_substr(const char *str, const char *sub, const char *replace) {
    if (str == NULL || sub == NULL || replace == NULL) {
        return NULL;
    }
    int str_len = mx_strlen(str);
    int sub_len = mx_strlen(sub);
    int replace_len = mx_strlen(replace);
    int substrs_count = mx_count_substr(str, sub);
    int new_str_len = str_len + substrs_count * (replace_len - sub_len);
    char *new_str = mx_strnew(new_str_len);
    if (new_str == NULL) {
        return NULL;
    }

    int sub_index = mx_get_substr_index(str, sub);
    for (int i = 0, j = 0; i < new_str_len;) {
        if (i == sub_index) {
            mx_strcpy(new_str + i, replace);
            i += replace_len;
            j += sub_len;
            sub_index = mx_get_substr_index(str + j, sub);
            if (sub_index != -1)
                sub_index += i;
        } else {
            new_str[i++] = str[j++];
        }
    }

    return new_str;
}

