#pragma once

#include "types.h"
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    id_t id;
    uint8_t changes_count;
} t_id_and_changes_count;

typedef struct {
    t_id_and_changes_count *arr;
    size_t len;
} t_id_and_changes_count_array;

t_id_and_changes_count_array create_id_and_changes_count(size_t len);
