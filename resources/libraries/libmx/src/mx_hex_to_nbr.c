#include "../inc/libmx.h"

int mx_hex_digit_to_number(const char hex_digit) {
    if (hex_digit >= '0' && hex_digit <= '9') {
        return hex_digit - '0';
    } else if (hex_digit >= 'A' && hex_digit <= 'F') {
        return hex_digit - 'A' + 10;
    } else if (hex_digit >= 'a' && hex_digit <= 'f') {
        return hex_digit - 'a' + 10;
    }
    return 0;
}

unsigned long mx_hex_to_nbr(const char *hex) {
    if (hex == NULL) {
        return 0;
    }
    int hex_len = mx_strlen(hex);
    unsigned long result = 0;
    for (int i = 0; i < hex_len; i++) {
        int hex_digit = mx_hex_digit_to_number(hex[hex_len - 1 - i]);
        result += hex_digit * mx_pow(16, i);
    }
    return result;
}

