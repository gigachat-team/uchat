#include "../inc/libmx.h"

int mx_list_size(t_list *list) {
	int list_size = 0;
	for (t_list *node = list; node != NULL; node = node->next) {
		list_size++;
	}
	return list_size;
}

