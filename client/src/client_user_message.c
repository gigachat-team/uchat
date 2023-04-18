#include "client_user_message.h"

t_user_messages_array allocate_user_messages_array(size_t size) {
    t_user_messages_array user_messages_array = {
        .size = size,
        .arr = malloc(size * sizeof(t_user_message))
    };
    return user_messages_array;
}

void free_user_message(t_user_message message) {
    free(message.sender_login);
    free(message.data);
}

void free_user_messages(t_user_message *messages, size_t length) {
    for (size_t i = 0; i < length; i++) {
        free_user_message(messages[i]);
    }
    free(messages);
}

void free_user_messages_list(list_t *messages_list) {
    if (messages_list == NULL) return;
    for (list_node_t *i = messages_list->head; i != NULL; i = i->next) {
        t_user_message *message = (t_user_message *)i->val;
        free(message->sender_login);
        free(message->data);
        free(message);
        free(i);
    }
    free(messages_list);
}

int compare_user_messages_IDs(void *a, void *b) {
    return ((t_user_message *)a)->message_id == ((t_user_message *)b)->message_id;
}
