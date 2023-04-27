#include "client_receivers.h"

list_t *receive_messages_list(int client_socket) {
    uint32_t messages_count = receive_uint32(client_socket);
    list_t *messages_list = list_new();
    for (size_t i = 0; i < messages_count; i++) {
        t_user_message *message = malloc(sizeof(t_user_message));
        message->message_id = receive_uint32(client_socket);
        message->sender_id = receive_uint32(client_socket);
        message->sender_login = receive_bytes(client_socket);
        message->data = receive_bytes(client_socket);
        message->creation_date = receive_uint32(client_socket);
        message->changes_count = receive_byte(client_socket);
        message->widget = NULL;
        message->label_widget = NULL;
        list_rpush(messages_list, list_node_new(message));
    }

    return messages_list;
}
