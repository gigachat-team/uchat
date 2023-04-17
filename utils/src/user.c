#include "user.h"

void free_user(t_user user) {
    free(user.login);
}

void free_users(t_user *users, size_t users_count) {
    for (size_t i = 0; i < users_count; i++) {
        free_user(users[i]);
    }
    free(users);
}

void free_users_list(list_t *users_list) {
    if (users_list == NULL) return;
    for (list_node_t *i = users_list->head; i != NULL; i = i->next) {
        t_user *user = i->val;
        free(user->login);
        free(i);
    }
    free(users_list);
}
