#include "../utils.h"

int64_t binary_search_uint32(uint32_t sorted_array[], uint32_t left, uint32_t right, uint32_t element) {
    while (left <= right) {
        int i = left + (right - left) / 2;

        if (sorted_array[i] == element)
            return i;
        if (sorted_array[i] < element)
            left = i + 1;
        else
            right = i - 1;
    }

    return -1;
}
