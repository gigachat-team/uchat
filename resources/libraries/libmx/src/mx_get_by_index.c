#include "../inc/libmx.h"

t_list *mx_get_by_index(t_list *head, int index) {
    int j = 0;
    for (t_list *i = head; i != NULL; i = i->next, j++) {
        if (j == index) {
            return i;
        }
    }
    return NULL;
}

