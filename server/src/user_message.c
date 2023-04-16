#include "user_message.h"

void free_user_message(t_user_message *message) {
    free(message->sender_login);
    free(message->data);
    free(message->creation_date);
}

void free_user_messages(t_user_message *messages, size_t length) {
    for (size_t i = 0; i < length; i++) {
        free_user_message(&messages[i]);
    }
    free(messages);
}

void free_user_messages_list(list_t *messages_list) {
    if (messages_list == NULL) return;
    for (list_node_t *i = messages_list->head; i != NULL; i = i->next) {
        free_user_message(i->val);
        free(i->val);
    }
    free(messages_list);
}
