#include "client_message.h"

t_messages_array allocate_messages_array(size_t size) {
    t_messages_array messages_array = {
        .size = size,
        .arr = malloc(size * sizeof(t_message))
    };
    return messages_array;
}

void free_message(t_message message) {
    free(message.sender_login);
    free(message.data);
}

void free_messages(t_message *messages, size_t length) {
    for (size_t i = 0; i < length; i++) {
        free_message(messages[i]);
    }
    free(messages);
}

void free_message_ptr(void *message_void) {
    t_message *message = message_void;
    free(message->sender_login);
    free(message->data);
    free(message);
}

void free_messages_list(list_t *messages_list) {
    if (messages_list == NULL) return;
    messages_list->free = free_message_ptr;
    list_destroy(messages_list);
}

int compare_messages_IDs(void *a, void *b) {
    return ((t_message *)a)->message_id == ((t_message *)b)->message_id;
}
