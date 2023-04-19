#include "user_message.h"

void free_user_message_ptr(void *message_ptr) {
    t_user_message *message = message_ptr;
    free(message->sender_login);
    free(message->data);
    free(message);

}

void free_user_messages(t_user_message *messages, size_t length) {
    for (size_t i = 0; i < length; i++) {
        free_user_message_ptr(&messages[i]);
    }
    free(messages);
}

void free_user_messages_list(list_t *messages_list) {
    if (messages_list == NULL) return;
    messages_list->free = free_user_message_ptr;
    list_destroy(messages_list);
}
