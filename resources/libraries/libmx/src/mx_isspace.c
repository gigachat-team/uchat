#include <stdbool.h>

bool mx_isspace(char c) {
	if (c >= 9 && c <= 13)
		return 1;
	if (c == 32)
		return 1;
	return 0;
}

