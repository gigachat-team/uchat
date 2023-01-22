#include "../inc/libmx.h"

int mx_binary_search(char **arr, int size, const char *s, int *count) {
    if (size <= 0 && count != NULL) {
        *count = 0;
        return -1;
    }
    if (arr == NULL || size <= 0 || s == NULL || count == NULL) {
        return -1;
    }

    int min = 0;
    int max = size - 1;
    for (int i = max / 2; ; i = min + (max - min) / 2) {
        int comparing_result = mx_strcmp(arr[i], s);
        (*count)++;
        if (comparing_result < 0) {
            min = i + 1;
        } else if (comparing_result > 0) {
            max = i;
        } else {
            return i;
        }
        if (*count > size) {
            break;
        }
    }

    *count = 0;
    return -1;
}

// int mx_binary_search(char **arr, int size, const char *s, int *count) {
//     if (size <= 0 && count != NULL) {
//         *count = 0;
//         return -1;
//     }
//     if (arr == NULL || size <= 0 || s == NULL || count == NULL) {
//         return -1;
//     }

// 	int low = 0;
// 	int high = size - 1;
// 	for (int middle = high / 2; ; middle = (high + low) / 2) {
// 		(*count)++;
// 		int cmp_result = mx_strcmp(arr[middle], s);
// 		if (cmp_result == 0) return middle;
// 		if (low == high) break;
// 		if (cmp_result > 0) high = middle - 1 < 0 ? 0 : middle - 1;
// 		else low = middle + 1;
// 	}
// 	(*count) = 0;
// 	return -1;
// }

