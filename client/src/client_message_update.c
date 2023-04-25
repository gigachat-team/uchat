#include "client_message_update.h"

void free_message_update_ptr(void *message_update_void) {
    t_message_update *message_update = message_update_void;
    free(message_update->message.sender_login);
    free(message_update->message.data);
    free(message_update);
}

void free_message_updates_list(list_t *message_updates_list) {
    if (!message_updates_list) return;
    message_updates_list->free = free_message_update_ptr;
    list_destroy(message_updates_list);
}
