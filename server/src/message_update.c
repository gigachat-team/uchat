#include "message_updates.h"

t_message_update create_empty_message_update() {
    t_message_update message_update = {
        .message = {
            .message_id = 0,
            .sender_id = 0,
            .sender_login = NULL,
            .data = NULL,
            .creation_date = NULL,
            .changes_count = 0
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

void free_message_updates_list(list_t *message_updates_list) {
    if (message_updates_list == NULL) return;
    for (list_node_t *i = message_updates_list->head; i != NULL; i = i->next) {
        t_message_update *message_update = (t_message_update *)i->val;
        free(message_update->message.sender_login);
        free(message_update->message.data);
        free(message_update->message.creation_date);
        free(message_update);
        free(i);
    }
    free(message_updates_list);
}
