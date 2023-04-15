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
        if (received_creation_date && strlen(received_creation_date))
            message->creation_date = utc_str_to_localtime_tm(received_creation_date, DEFAULT_TIME_FORMAT);
        free(received_creation_date);
        message->widget = NULL;
        mx_push_back(&messages_list.list, message);
    }

    return messages_list;
}

t_list_with_size receive_message_updates_list(int client_socket) {
    t_list_with_size message_updates_list = {.list = NULL, .size = receive_uint32(client_socket)};
    for (size_t i = 0; i < message_updates_list.size; i++) {
        t_message_update *message_update = malloc(sizeof(t_message_update));
        message_update->message.message_id = receive_uint32(client_socket);
        message_update->message.sender_id = receive_uint32(client_socket);
        message_update->message.sender_login = receive_bytes(client_socket);
        message_update->message.data = receive_bytes(client_socket);
        char *received_creation_date = receive_bytes(client_socket);
        if (received_creation_date && strlen(received_creation_date))
            message_update->message.creation_date = utc_str_to_localtime_tm(received_creation_date, DEFAULT_TIME_FORMAT);
        free(received_creation_date);
        message_update->message.widget = NULL;
        message_update->remove = receive_byte(client_socket);

        mx_push_back(&message_updates_list.list, message_update);
    }
    return message_updates_list;
}
