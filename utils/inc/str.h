#pragma once

#include <stdlib.h>

typedef struct {
    char *val;
    size_t len;
} t_string;

t_string string_new(size_t len);
void string_destroy(t_string *string);
