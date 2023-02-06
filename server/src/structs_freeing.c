#include "../server.h"

void free_message(t_message message) {
    free(message.bytes);
}

void free_messages_array(t_message *messages, size_t length) {
    for (size_t i = 0; i < length; i++) {
        free_message(messages[i]);
    }
    free(messages);
}

