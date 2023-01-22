#include "../inc/libmx.h"

void mx_printint(int n) {
	if (n == 0) {
		mx_printchar('0');
		return;
	}
	if (n == -2147483648) {
		mx_printstr("-2147483648");
		return;
	}
	int string_length = 11;
	char string[string_length];
	bool is_negative = n < 0;

	if (is_negative) {
		n *= -1;
		mx_printchar('-');
	}
	for (string_length = 0; n != 0; n /= 10) {
		string[string_length] = n % 10 + 48;
		string_length++;
	}
	for (int i = string_length - 1; i >= 0; i--)
		mx_printchar(string[i]);
}

