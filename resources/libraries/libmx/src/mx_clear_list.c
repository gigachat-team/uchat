#include "../inc/libmx.h"

void mx_clear_list(t_list **list) {
	if (list == NULL) {
		return;
	}
	t_list *current_node = *list;
	while (current_node != NULL) {
		t_list *next_node = current_node->next;
		free(current_node);
		current_node = next_node;
	}
	*list = NULL;
}

