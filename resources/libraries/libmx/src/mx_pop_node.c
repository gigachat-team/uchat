#include "../inc/libmx.h"

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

