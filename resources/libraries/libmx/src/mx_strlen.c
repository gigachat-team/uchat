#include "../inc/libmx.h"

int mx_strlen(const char *s) {
    if (s == NULL) {
        return 0;
    }
    int len = 0;
    for ( ; s[len] != '\0'; len++) { }
    return len;
}

