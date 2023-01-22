#include "../inc/libmx.h"

void mx_pop_front(t_list **head) {
	if (head == NULL || *head == NULL) {
		return;
	}
	t_list *second_node = (*head)->next;
	free(*head);
	*head = NULL;
	if (second_node != NULL) {
		*head = second_node;
	}
}

