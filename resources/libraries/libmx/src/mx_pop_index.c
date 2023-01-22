#include "../inc/libmx.h"

void mx_pop_index(t_list **list, int index) {
	if (index < 0)
		index = 0;
	if (index == 0) {
		mx_pop_front(list);
		return;
	}
	t_list *prev_node = *list;
	for (int i = 1; i < index && prev_node->next != NULL; ++i) {
		prev_node = prev_node->next;
	}
	if (prev_node->next == NULL) {
		mx_pop_back(list);
		return;
	}
	t_list *next_node = prev_node->next->next;
	free(prev_node->next);
	prev_node->next = next_node;
}

//#include <stdio.h>
//t_list *mx_create_node(void *data);
//void mx_push_index(t_list **list, void *data, int index);
//int main() {
//	char *data[] = {"This", "Oracle", "shit", "is"};
//	t_list *head = mx_create_node(data[1]);
//	mx_push_index(&head, data[0], 0);
//	mx_push_index(&head, data[2], 849);
//	mx_push_index(&head, data[3], 2);
//
//	mx_pop_index(&head, 1);
//
//	for (t_list *node = head; node != NULL; node = node->next) {
//		printf("Node: %s\n", (char *)node->data);
//	}
//	return 0;
//}

