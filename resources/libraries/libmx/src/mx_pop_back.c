#include "../inc/libmx.h"

void mx_pop_back(t_list **head) {
	if (head == NULL || *head == NULL) {
		return;
	}
	t_list *penultimate_node = NULL;
	t_list *last_node = *head;
	for ( ; last_node->next != NULL; last_node = last_node->next)
		penultimate_node = last_node;
	if (last_node == *head)
		*head = NULL;
	free(last_node);
	if (penultimate_node != NULL)
		penultimate_node->next = NULL;
}

