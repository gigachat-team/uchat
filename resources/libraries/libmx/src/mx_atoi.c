#include "../inc/libmx.h"

int mx_atoi(const char *str) {
	bool is_negative = false;
	int current_index = 0;
	int result_number = 0;
	if (str[current_index] == '-') {
		is_negative = true;
		current_index++;
	}
	if (str[current_index] == '+')
		current_index++;
	for (; str[current_index] != '\0'; current_index++) {
		if (!mx_isdigit(str[current_index]))
			return 0;
		result_number *= 10;
		result_number += str[current_index] - 48;
	}
	if (is_negative) result_number *= -1;
	return result_number;	
}

