#include "utils.h"

void free_chat(t_chat chat) {
    free(chat.name);
}

void free_chats(t_chat *chats, size_t length) {
    for (size_t i = 0; i < length; i++) {
        free_chat(chats[i]);
    }
    free(chats);
}

void free_new_chat_member_data(t_new_chat_member_data new_chat_member_data) {
    free(new_chat_member_data.member_login);
}

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
