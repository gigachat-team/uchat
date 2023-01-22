#include "../inc/libmx.h"

char *mx_nbr_to_hex(unsigned long nbr) {
	char reversed_hex[100];
	int hex_size = 0;
	while(nbr > 0) {
		unsigned long remainder = nbr % 16;
		if (remainder >= 10)
			reversed_hex[hex_size] = (char)(remainder + 87);
		else
			reversed_hex[hex_size] = (char)(remainder + 48);
		hex_size++;
		nbr /= 16;
	}
	char *hex = mx_strnew(hex_size);
	for (int i = 0; i < hex_size; ++i)
		hex[i] = reversed_hex[hex_size - i - 1];
	return hex;
}

