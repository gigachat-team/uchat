#include "server_message.h"

void free_message(void *message_ptr) {
    t_message *message = message_ptr;
    free(message->sender_login);
    free(message->data);
    free(message);

}

void free_messages_array(t_message *messages, size_t length) {
    for (size_t i = 0; i < length; i++) {
        free_message(&messages[i]);
    }
    free(messages);
}

void free_messages_list(list_t *messages_list) {
    if (messages_list == NULL) return;
    messages_list->free = free_message;
    list_destroy(messages_list);
}
