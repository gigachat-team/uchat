#include "../inc/libmx.h"

int mx_quicksort(char **arr, int left, int right) {
    if (arr == NULL) {
        return -1;
    }
    if (left >= right) {
        return 0;
    }
    int swaps_count = 0;
    int stored_left = left;
    int stored_right = right;
    int middle = (right - left) / 2 + left;
    while (left < right) {
        bool move_right = true;
        bool move_left = true;
        int left_len = mx_strlen(arr[left]);
        int middle_len = mx_strlen(arr[middle]);
        int right_len = mx_strlen(arr[right]);
        if (left_len > middle_len) {
            move_left = false;
        }
        if (middle_len > right_len) {
            move_right = false;
        }
        if (left_len == middle_len && middle_len > right_len) {
            move_left = false;
        }
        if (middle_len == right_len && left_len > middle_len) {
            move_right = false;
        }
        if (!move_left && !move_right) {
            char *stored = arr[left];
            arr[left] = arr[right];
            arr[right] = stored;
            if (left == middle) {
                middle = right;
            } else if (right == middle) {
                middle = left;
            }
            move_left = true;
            move_right = true;
            swaps_count++;
        }
        if (move_right) {
            right--;
        }
        if (move_left) {
            left++;
        }
    }
    swaps_count += mx_quicksort(arr, stored_left, middle);
    swaps_count += mx_quicksort(arr, middle + 1, stored_right);
    
    return swaps_count;
}

