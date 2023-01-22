#include "../inc/libmx.h"

bool mx_num_in_str_is_positive(char *str) {
    if (str == NULL)
        return false;
    for (int i = 0; str[i] != '\0'; i++) {
        if (!mx_isdigit(str[i])) {
            return false;
        }
    }
    return true;
}

