#include "../client.h"

void free_user_message(t_user_message message) {
    free(message.user_login);
    free(message.bytes);
}

void free_user_messages(t_user_message *messages, size_t length) {
    for (size_t i = 0; i < length; i++) {
        free_user_message(messages[i]);
    }
    free(messages);
}

