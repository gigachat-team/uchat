#include "senders.h"

void send_message_updates_list(int client_socket, list_t *message_updates_list) {
    t_package package = create_package(1 + message_updates_list->len * 6);
    pack_uint32(message_updates_list->len, &package);
    for (list_node_t *i = message_updates_list->head; i != NULL; i = i->next) {
        t_message_update *message_update = (t_message_update *)i->val;
        pack_uint32(message_update->message.message_id, &package);
        pack_uint32(message_update->message.sender_id, &package);
        pack_bytes(message_update->message.sender_login, &package);
        pack_bytes(message_update->message.data, &package);
        pack_bytes(message_update->message.creation_date, &package);
        pack_byte(message_update->remove, &package);
    }
    send_and_free_package(client_socket, &package);
}
