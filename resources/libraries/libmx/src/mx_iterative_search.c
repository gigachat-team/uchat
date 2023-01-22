#include "../inc/libmx.h"

int mx_iterative_search(char **strings, int count, char *searching) {
    if (strings == NULL || searching == NULL) {
        return -1;
    }

    for (int i = 0; i < count; i++) {
        if (mx_strcmp(strings[i], searching) == 0) {
            return i;
        }
    }
    return -1;
}

