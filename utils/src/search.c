#include "../utils.h"

int64_t binary_search_uint32(t_uint32_array *sorted_array, uint32_t to_find) {
    int64_t left = 0;
    int64_t right = sorted_array->size - 1;

    while (right - left > 1) {
        int middle = (right + left) / 2;
        if (sorted_array->arr[middle] < to_find) {
            left = middle + 1;
        }
        else {
            right = middle;
        }
    }
    if (sorted_array->arr[left] == to_find) {
        return left;
    }
    else if (sorted_array->arr[right] == to_find) {
        return right;
    }
    else {
        return -1;
    }
}
