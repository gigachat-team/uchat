#include "../inc/libmx.h"

char *mx_itoa(int number) {
	bool is_negative = number < 0;
    int digits_count = mx_get_digits_count(number);
    char *num_str = mx_strnew(is_negative ? digits_count + 1 : digits_count);
    int num_str_len = 0;

    if (number == 0) {
		num_str[0] = '0';
		return num_str;
	}
	if (number == -2147483648) {
        mx_strcpy(num_str, "-2147483648");
		return num_str;
	}

	if (is_negative) {
		number *= -1;
		num_str[num_str_len++] = '-';
	}
	for (; number != 0; number /= 10) {
		num_str[is_negative ? digits_count - num_str_len + 1 : digits_count - num_str_len - 1] = number % 10 + '0';
        num_str_len++;
	}
    return num_str;
}

