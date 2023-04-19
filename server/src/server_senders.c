#include "server_senders.h"

void send_messages_list(int client_socket, list_t *messages_list) {
    t_package package = create_package(1 + messages_list->len * 8);
    pack_uint32(messages_list->len, &package);
    for (list_node_t *i = messages_list->head; i != NULL; i = i->next) {
        t_user_message *user_message = (t_user_message *)i->val;
        pack_uint32(user_message->message_id, &package);
        pack_uint32(user_message->sender_id, &package);
        pack_bytes(user_message->sender_login, &package);
        pack_bytes(user_message->data, &package);
        pack_uint32(user_message->creation_date, &package);
        pack_byte(user_message->changes_count, &package);
    }
    send_and_free_package(client_socket, &package);
}

void send_message_updates_list(int client_socket, list_t *message_updates_list) {
    t_package package = create_package(1 + message_updates_list->len * 7);
    pack_uint32(message_updates_list->len, &package);
    for (list_node_t *i = message_updates_list->head; i != NULL; i = i->next) {
        t_message_update *message_update = (t_message_update *)i->val;
        pack_uint32(message_update->message.message_id, &package);
        pack_uint32(message_update->message.sender_id, &package);
        pack_bytes(message_update->message.sender_login, &package);
        pack_bytes(message_update->message.data, &package);
        pack_uint32(message_update->message.creation_date, &package);
        pack_byte(message_update->message.changes_count, &package);
        pack_byte(message_update->remove, &package);
    }
    send_and_free_package(client_socket, &package);
}
