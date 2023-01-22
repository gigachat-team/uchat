#include "../inc/libmx.h"

char *mx_strnew(const int size) {
    if (size < 0) {
        return NULL;
    }
    char *new_str = malloc((size + 1) * sizeof(char));
    if (new_str == NULL) {
        return NULL;
    }
    for (int i = 0; i < size + 1; i++) {
        new_str[i] = '\0';
    }
    return new_str;
}

