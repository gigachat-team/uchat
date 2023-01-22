#include "../inc/libmx.h"

void mx_swap_char(char *s1, char *s2) {
	if (s1 == NULL || s2 == NULL) {
		return;
	}
	char stored = *s1;
	*s1 = *s2;
	*s2 = stored;
}

