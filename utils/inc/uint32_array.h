#pragma once

#include <stdlib.h>
#include <stdint.h>

typedef struct s_uint32_array {
    uint32_t *arr;
    size_t size;
} t_uint32_array;

t_uint32_array allocate_uint32_array(size_t size);
