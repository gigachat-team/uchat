#include "../utils.h"
#include <stdint.h>
#include <stdlib.h>

t_uint32_array allocate_uint32_array(size_t size) {
    t_uint32_array uint32_array = {
        .size = size,
        .arr = malloc(size * sizeof(uint32_t))
    };
    return uint32_array;
}
