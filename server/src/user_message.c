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

void free_user_messages_list(t_list **messages_list) {
    for (t_list *i = *messages_list; i != NULL; i = i->next) {
        free_user_message(i->data);
        free(i->data);
    }
    mx_clear_list(messages_list);
}
