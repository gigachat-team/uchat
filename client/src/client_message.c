#include "client_message.h"

t_message create_message() {
    t_message message = {
        .message_id = 0,
        .sender_id = 0,
        .sender_login = NULL,
        .data = NULL,
        .creation_date = 0,
        .changes_count = 0,
        .reply_message_id = 0,
        .container_box = NULL,
        .content_label = NULL,
        .is_edited_label = NULL,
        .replied_message_content_label = NULL,
        .replied_message_login_label = NULL
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

void free_message_ptr(void *message_void) {
    free_message(message_void);
    free(message_void);
}

void free_messages_list(list_t *messages_list) {
    if (messages_list == NULL) return;
    messages_list->free = free_message_ptr;
    list_destroy(messages_list);
}

int compare_messages_IDs(void *a, void *b) {
    return ((t_message *)a)->message_id == ((t_message *)b)->message_id;
}
