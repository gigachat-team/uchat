#include "../client.h"

t_list_with_size receive_messages_list(int client_socket) {
    t_list_with_size messages_list = {.list = NULL, .size = receive_uint32(client_socket)};
    for (size_t i = 0; i < messages_list.size; i++) {
        t_user_message *message = malloc(sizeof(t_user_message));
        message->message_id = receive_uint32(client_socket);
        message->sender_id = receive_uint32(client_socket);
        message->sender_login = receive_bytes(client_socket);
        message->data = receive_bytes(client_socket);
        char *received_creation_date = receive_bytes(client_socket);
        message->creation_date = utc_str_to_localtime_tm(received_creation_date, DEFAULT_TIME_FORMAT);
        free(received_creation_date);
        mx_push_back(&messages_list.list, message);
    }

    return messages_list;
}
