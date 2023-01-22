#include "../inc/libmx.h"

int mx_get_digits_count(int num) {
    if (num == -2147483648) {
        return 10;
    }
    if (num < 0) {
        num = -num;
    } else if (num == 0) {
        return 1;
    }
    int digits_count = 0;
    while (num != 0) {
        digits_count++;
        num /= 10;
    }
    return digits_count;
}

