#include "senders.h"

void send_message_updates_list(int client_socket, t_list_with_size *message_updates_list) {
    t_package package = create_package(1 + message_updates_list->size * 6);
    pack_uint32(message_updates_list->size, &package);
    for (t_list *i = message_updates_list->list; i != NULL; i = i->next) {
        t_message_update *message_update = (t_message_update *)i->data;
        pack_uint32(message_update->message.message_id, &package);
        pack_uint32(message_update->message.sender_id, &package);
        pack_bytes(message_update->message.sender_login, &package);
        pack_bytes(message_update->message.data, &package);
        pack_bytes(message_update->message.creation_date, &package);
        pack_byte(message_update->remove, &package);
    }
    send_and_free_package(client_socket, &package);
}
