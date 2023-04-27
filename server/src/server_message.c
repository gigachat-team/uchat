#include "server_message.h"

t_message create_message() {
    t_message message = {
        .message_id = 0,
        .sender_id = 0,
        .sender_login = NULL,
        .data = NULL,
        .creation_date = 0,
        .changes_count = 0
    };
    return message;
}

t_message *create_message_ptr() {
    t_message *message = malloc(sizeof(t_message));
    *message = create_message();
    return message;
}

void free_message(t_message *message) {
    free(message->sender_login);
    free(message->data);
}

void free_message_ptr(void *message) {
    free_message(message);
    free(message);
}

void free_messages_array(t_message *messages, size_t length) {
    for (size_t i = 0; i < length; i++) {
        free_message_ptr(&messages[i]);
    }
    free(messages);
}

void free_messages_list(list_t *messages_list) {
    if (messages_list == NULL) return;
    messages_list->free = free_message_ptr;
    list_destroy(messages_list);
}
