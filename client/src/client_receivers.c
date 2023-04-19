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
        char *received_creation_date = receive_bytes(client_socket);
        // if (received_creation_date && strlen(received_creation_date))
        //     message->creation_date = utc_str_to_localtime_tm(received_creation_date, DEFAULT_TIME_FORMAT);
        free(received_creation_date);
        message->changes_count = receive_byte(client_socket);
        message->widget = NULL;
        list_rpush(messages_list, list_node_new(message));
    }

    return messages_list;
}

list_t *receive_message_updates_list(int client_socket) {
    uint32_t message_updates_count = receive_uint32(client_socket);
    list_t *message_updates_list = list_new();
    for (size_t i = 0; i < message_updates_count; i++) {
        t_message_update *message_update = malloc(sizeof(t_message_update));
        message_update->message.message_id = receive_uint32(client_socket);
        message_update->message.sender_id = receive_uint32(client_socket);
        message_update->message.sender_login = receive_bytes(client_socket);
        message_update->message.data = receive_bytes(client_socket);
        char *received_creation_date = receive_bytes(client_socket);
        // if (received_creation_date && strlen(received_creation_date))
        //     message_update->message.creation_date = utc_str_to_localtime_tm(received_creation_date, DEFAULT_TIME_FORMAT);
        free(received_creation_date);
        message_update->message.changes_count = receive_byte(client_socket);
        message_update->message.widget = NULL;
        message_update->remove = receive_byte(client_socket);
        list_rpush(message_updates_list, list_node_new(message_update));
    }
    return message_updates_list;
}
