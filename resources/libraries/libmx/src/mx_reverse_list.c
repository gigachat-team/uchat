#include "../inc/libmx.h"

void mx_reverse_list(t_list *head) {
	void *temp;
    for (int start = 0, end = mx_list_size(head) - 1; start < end; start++, end--) {
        temp = mx_get_by_index(head, start)->data;
        mx_get_by_index(head, start)->data = mx_get_by_index(head, end)->data;
        mx_get_by_index(head, end)->data = temp;
    }
}

