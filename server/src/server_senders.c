#include "server_senders.h"

void send_messages_list(int client_socket, list_t *messages_list) {
    t_package package = create_package(1 + messages_list->len * 8);
    pack_uint32(messages_list->len, &package);
    for (list_node_t *i = messages_list->head; i != NULL; i = i->next) {
        t_message *message = (t_message *)i->val;
        pack_uint32(message->message_id, &package);
        pack_uint32(message->sender_id, &package);
        pack_bytes(message->sender_login, &package);
        pack_bytes(message->data, &package);
        pack_uint32(message->creation_date, &package);
        pack_byte(message->changes_count, &package);
        pack_uint32(message->reply_message_id, &package);
    }
    send_and_free_package(client_socket, &package);
}
