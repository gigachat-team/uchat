#include "utils.h"

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

t_list *mx_create_node(void *data) {
	t_list *node = malloc(sizeof(t_list));
	node->data = data;
	node->next = NULL;
	return node;
}

t_list *mx_get_by_index(t_list *head, int index) {
    int j = 0;
    for (t_list *i = head; i != NULL; i = i->next, j++) {
        if (j == index) {
            return i;
        }
    }
    return NULL;
}

int mx_list_size(t_list *list) {
	int list_size = 0;
	for (t_list *node = list; node != NULL; node = node->next) {
		list_size++;
	}
	return list_size;
}

void mx_reverse_list(t_list *head) {
	void *temp;
    for (int start = 0, end = mx_list_size(head) - 1; start < end; start++, end--) {
        temp = mx_get_by_index(head, start)->data;
        mx_get_by_index(head, start)->data = mx_get_by_index(head, end)->data;
        mx_get_by_index(head, end)->data = temp;
    }
}

t_list *mx_sort_list(t_list *lst, bool (*cmp)(void *, void *)) {
	for (t_list *i = lst; i != NULL; i = i->next) {
		for (t_list *j = lst; j->next != NULL; j = j->next) {
			if (cmp(j->data, j->next->data)) {
				void *stored = j->data;
				j->data = j->next->data;
				j->next->data = stored;
			}
		}
	}
	return lst;
}

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

void mx_pop_node(t_list **head, t_list *node) {
    if (head == NULL || *head == NULL || node == NULL) {
        return;
    }
    if (*head == node) {
        mx_pop_front(head);
        return;
    }
    t_list *prev_node = NULL;
    for (t_list *curr_node = *head; curr_node != NULL; curr_node = curr_node->next) {
        if (curr_node == node) {
            t_list *next_node = curr_node->next;
            free(curr_node);
            prev_node->next = next_node;
            return;
        }
        prev_node = curr_node;
    }
}

void mx_push_front(t_list **list, void *data) {
	t_list *new_node = mx_create_node(data);
	new_node->next = *list;
	*list = new_node;
}

void mx_push_back(t_list **list, void *data) {
	t_list *new_node = mx_create_node(data);
	t_list *last_node = *list;
	if (last_node != NULL) {
		for ( ; last_node->next != NULL; last_node = last_node->next) { }
		last_node->next = new_node;
	} else {
		*list = new_node;
	}
}
