#include "str.h"

t_string string_new(size_t len) {
    t_string string = {
        .val = malloc(len + 1),
        .len = len
    };
    string.val[string.len] = '\0';
    return string;
}

void string_destroy(t_string *string) {
    free(string->val);
    string->val = NULL;
    string->len = 0;
}
