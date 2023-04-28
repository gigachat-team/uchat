#include "request_senders.h"

t_state_code rq_send_text_message(t_address *server_address, id_t user_id, id_t chat_id, char *data) {
    int client_socket = create_and_connect_socket(server_address);
    if (client_socket == -1) return CONNECTION_REFUSED;

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

list_t *rq_get_messages_in_chat(t_address *server_address, id_t chat_id) {
    int client_socket = create_and_connect_socket(server_address);
    if (client_socket == -1) return NULL;

    t_package package = create_package(2);
    pack_byte(GET_MESSAGES_IN_CHAT, &package);
    pack_uint32(chat_id, &package);
    send_and_free_package(client_socket, &package);

    list_t *messages_list = receive_messages_list(client_socket);

    close(client_socket);

    return messages_list;
}

list_t *rq_send_message_and_get_messages_updates(t_address *server_address, id_t user_id, id_t chat_id, char *message, list_t *messages_list) {
    int client_socket = create_and_connect_socket(server_address);
    if (client_socket == -1) return NULL;

    t_package package = create_package(5 + messages_list->len * 2);
    pack_byte(SEND_MESSAGE_AND_GET_MESSAGE_UPDATES, &package);
    pack_uint32(user_id, &package);
    pack_uint32(chat_id, &package);
    pack_bytes(message, &package);
    pack_uint32(messages_list->len, &package);
    for (list_node_t *i = messages_list->head; i != NULL; i = i->next) {
        t_message *message = (t_message *)i->val;
        pack_uint32(message->message_id, &package);
        pack_byte(message->changes_count, &package);
    }
    send_and_free_package(client_socket, &package);

    list_t *message_updates_list = receive_messages_list(client_socket);

    close(client_socket);

    return message_updates_list;
}

list_t *rq_delete_message_and_get_message_updates(t_address *server_address, id_t message_id, id_t chat_id, list_t *messages_list) {
    int client_socket = create_and_connect_socket(server_address);
    if (client_socket == -1) return NULL;

    t_package package = create_package(4 + messages_list->len * 2);
    pack_byte(DELETE_MESSAGE_AND_GET_MESSAGE_UPDATES, &package);
    pack_uint32(message_id, &package);
    pack_uint32(chat_id, &package);
    pack_uint32(messages_list->len, &package);
    for (list_node_t *i = messages_list->head; i != NULL; i = i->next) {
        t_message *message = (t_message *)i->val;
        pack_uint32(message->message_id, &package);
        pack_byte(message->changes_count, &package);
    }
    send_and_free_package(client_socket, &package);

    list_t *message_updates_list = receive_messages_list(client_socket);

    close(client_socket);

    return message_updates_list;
}

list_t *rq_change_message_and_get_message_updates(t_address *server_address, id_t message_id, char *new_message_content, id_t chat_id, list_t *messages_list) {
    int client_socket = create_and_connect_socket(server_address);
    if (client_socket == -1) return NULL;

    t_package package = create_package(5 + messages_list->len * 2);
    pack_byte(CHANGE_MESSAGE_AND_GET_MESSAGE_UPDATES, &package);
    pack_uint32(message_id, &package);
    pack_bytes(new_message_content, &package);
    pack_uint32(chat_id, &package);
    pack_uint32(messages_list->len, &package);
    for (list_node_t *i = messages_list->head; i != NULL; i = i->next) {
        t_message *message = i->val;
        pack_uint32(message->message_id, &package);
        pack_byte(message->changes_count, &package);
    }
    send_and_free_package(client_socket, &package);

    list_t *message_updates_list = receive_messages_list(client_socket);

    close(client_socket);

    return message_updates_list;
}

list_t *rq_reply_to_message_and_get_message_updates(t_address *server_address, id_t replier_id, id_t replying_message_id, char *reply_content, id_t chat_id, list_t *messages_list) {
    int client_socket = create_and_connect_socket(server_address);
    if (client_socket == -1) return NULL;

    t_package package = create_package(6 + messages_list->len * 2);
    pack_byte(REPLY_TO_MESSAGE_AND_GET_MESSAGE_UPDATES, &package);
    pack_uint32(replier_id, &package);
    pack_uint32(replying_message_id, &package);
    pack_uint32(chat_id, &package);
    pack_bytes(reply_content, &package);
    pack_uint32(messages_list->len, &package);
    for (list_node_t *i = messages_list->head; i != NULL; i = i->next) {
        t_message *message = i->val;
        pack_uint32(message->message_id, &package);
        pack_byte(message->changes_count, &package);
    }
    send_and_free_package(client_socket, &package);

    list_t *message_updates_list = receive_messages_list(client_socket);

    close(client_socket);

    return message_updates_list;
}

list_t *rq_get_message_updates(t_address *server_address, id_t chat_id, list_t *messages_list) {
    int client_socket = create_and_connect_socket(server_address);
    if (client_socket == -1) return NULL;

    t_package package = create_package(3 + messages_list->len * 2);
    pack_byte(GET_MESSAGE_UPDATES, &package);
    pack_uint32(chat_id, &package);
    pack_uint32(messages_list->len, &package);
    for (list_node_t *i = messages_list->head; i != NULL; i = i->next) {
        t_message *message = (t_message *)i->val;
        pack_uint32(message->message_id, &package);
        pack_byte(message->changes_count, &package);
    }
    send_and_free_package(client_socket, &package);

    list_t *message_updates_list = receive_messages_list(client_socket);

    close(client_socket);

    return message_updates_list;
}
