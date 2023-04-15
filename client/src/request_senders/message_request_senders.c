#include "main.h"

t_state_code rq_send_text_message(t_address server_address, id_t user_id, id_t chat_id, char *data) {
    int client_socket = create_and_connect_socket(server_address);

    t_package package = create_package(4);
    pack_byte(SEND_TEXT_MESSAGE, &package);
    pack_uint32(user_id, &package);
    pack_uint32(chat_id, &package);
    pack_bytes(data, &package);
    send_and_free_package(client_socket, &package);

    t_state_code response = receive_byte(client_socket);

    close(client_socket);

    return response;
}

t_list_with_size rq_get_messages_in_chat(t_address server_address, id_t chat_id) {
    int client_socket = create_and_connect_socket(server_address);

    t_package package = create_package(2);
    pack_byte(GET_MESSAGES_IN_CHAT, &package);
    pack_uint32(chat_id, &package);
    send_and_free_package(client_socket, &package);

    t_list_with_size messages_list = receive_messages_list(client_socket);

    close(client_socket);

    return messages_list;
}

t_list_with_size rq_send_message_and_get_messages_updates(t_address server_address, id_t user_id, id_t chat_id, char *message, t_list_with_size *messages_list) {
    int client_socket = create_and_connect_socket(server_address);

    t_package package = create_package(5 + messages_list->size);
    pack_byte(SEND_MESSAGE_AND_GET_MESSAGE_UPDATES, &package);
    pack_uint32(user_id, &package);
    pack_uint32(chat_id, &package);
    pack_bytes(message, &package);
    pack_uint32(messages_list->size, &package);
    for (t_list *i = messages_list->list; i != NULL; i = i->next) {
        pack_uint32(((t_user_message *)i->data)->message_id, &package);
    }
    send_and_free_package(client_socket, &package);

    t_list_with_size message_updates_list = receive_message_updates_list(client_socket);

    close(client_socket);

    return message_updates_list;
}

t_list_with_size rq_get_message_updates(t_address server_address, id_t chat_id, t_list_with_size *messages_list) {
    int client_socket = create_and_connect_socket(server_address);

    t_package package = create_package(5 + messages_list->size);
    pack_byte(GET_MESSAGES_IN_CHAT, &package);
    pack_uint32(chat_id, &package);
    pack_uint32(messages_list->size, &package);
    for (t_list *i = messages_list->list; i != NULL; i = i->next) {
        pack_uint32(((t_user_message *)i->data)->message_id, &package);
    }
    send_and_free_package(client_socket, &package);

    t_list_with_size message_updates_list = receive_message_updates_list(client_socket);

    close(client_socket);

    return message_updates_list;
}
