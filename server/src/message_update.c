#include "../server.h"

t_message_update create_empty_message_update() {
    t_message_update message_update = {
        .message = {
            .message_id = 0,
            .sender_id = 0,
            .sender_login = NULL,
            .data = NULL,
            .creation_date = NULL
        },
        .remove = false
    };
    return message_update;
}

t_message_update *create_empty_message_update_ptr() {
    t_message_update *message_update = malloc(sizeof(t_message_update));
    *message_update = create_empty_message_update();
    return message_update;
}

void free_message_updates_list(t_list **message_updates_list) {
    for (t_list *i = *message_updates_list; i != NULL; i = i->next) {
        t_message_update *message_update = (t_message_update *)i->data;
        free(message_update->message.sender_login);
        free(message_update->message.data);
        free(message_update->message.creation_date);
        free(message_update);
    }
    mx_clear_list(message_updates_list);
}