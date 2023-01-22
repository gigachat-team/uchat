#include "../inc/libmx.h"

int mx_bubble_sort(char **arr, int size) {
    int number_of_swaps = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 1; j < size - i; j++) {
            if (mx_strcmp(arr[j - 1], arr[j]) > 0) {
                char *stored = arr[j - 1];
                arr[j - 1] = arr[j];
                arr[j] = stored;
                number_of_swaps++;
            }
        }
    }
    return number_of_swaps;
}

