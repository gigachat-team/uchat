#include "../client.h"

t_state_code rq_authenticate_user(t_address server_address, char *login, char *password, t_authentication_mode authentication_mode, uint *user_id) {
    int client_socket = create_and_connect_socket(server_address);
    if (errno == ECONNREFUSED) {
        return CONNECTION_REFUSED;
    }

    t_package package = create_package(3);
    pack_byte(authentication_mode, &package);
    pack_bytes(login, &package);
    pack_bytes(password, &package);
    send_and_free_package(client_socket, package);

    t_state_code authentication_result = receive_byte(client_socket);
    if (authentication_result == SUCCESSFUL_LOGIN || authentication_result == SUCCESSFUL_REGISTRATION) {
        *user_id = receive_uint32(client_socket);
    }

    close(client_socket);

    return authentication_result;
}

id_t rq_create_chat(t_address server_address, char *chat_name, id_t owner_id) {
    int client_socket = create_and_connect_socket(server_address);

    t_package package = create_package(3);
    pack_byte(CREATE_CHAT, &package);
    pack_bytes(chat_name, &package);
    pack_uint32(owner_id, &package);
    send_and_free_package(client_socket, package);

    id_t created_chat_id = receive_uint32(client_socket);

    close(client_socket);

    return created_chat_id;
}

t_chat *rq_get_chats_i_am_in(t_address server_address, id_t user_id, size_t *chats_count) {
    int client_socket = create_and_connect_socket(server_address);

    t_package package = create_package(2);
    pack_byte(GET_CHATS_I_AM_IN, &package);
    pack_uint32(user_id, &package);
    send_and_free_package(client_socket, package);

    *chats_count = receive_uint32(client_socket);
    t_chat *chats_i_am_in = *chats_count == 0 ? NULL : malloc(*chats_count * sizeof(t_chat));
    for (size_t i = 0; i < *chats_count; i++) {
        chats_i_am_in[i].id = receive_uint32(client_socket);
        chats_i_am_in[i].name = receive_bytes(client_socket);
    }

    close(client_socket);

    return chats_i_am_in;
}

t_state_code rq_add_new_member(t_address server_address, t_new_chat_member_data new_chat_member_data) {
    int client_socket = create_and_connect_socket(server_address);

    t_package package = create_package(3);
    pack_byte(ADD_MEMBER_TO_CHAT, &package);
    pack_uint32(new_chat_member_data.chat_id, &package);
    pack_bytes(new_chat_member_data.member_login, &package);
    send_and_free_package(client_socket, package);

    t_state_code adding_new_member_to_chat_result = receive_byte(client_socket);

    close(client_socket);

    return adding_new_member_to_chat_result;
}

t_state_code rq_send_text_message(t_address server_address, id_t user_id, id_t chat_id, char *data) {
    int client_socket = create_and_connect_socket(server_address);

    t_package package = create_package(4);
    pack_byte(SEND_TEXT_MESSAGE, &package);
    pack_uint32(user_id, &package);
    pack_uint32(chat_id, &package);
    pack_bytes(data, &package);
    send_and_free_package(client_socket, package);

    t_state_code response = receive_byte(client_socket);

    close(client_socket);

    return response;
}

t_list_with_size rq_get_messages_in_chat(t_address server_address, id_t chat_id) {
    int client_socket = create_and_connect_socket(server_address);

    t_package package = create_package(2);
    pack_byte(GET_MESSAGES_IN_CHAT, &package);
    pack_uint32(chat_id, &package);
    send_and_free_package(client_socket, package);

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
    send_and_free_package(client_socket, package);

    t_list_with_size updated_messages_list = {.list = NULL, .size = receive_uint32(client_socket)};
    for (size_t i = 0; i < updated_messages_list.size; i++) {
        t_user_message *updated_message = malloc(sizeof(t_user_message));
        updated_message->message_id = receive_uint32(client_socket);
        updated_message->sender_id = receive_uint32(client_socket);
        updated_message->sender_login = receive_bytes(client_socket);
        updated_message->data = receive_bytes(client_socket);
        char *received_creation_date = receive_bytes(client_socket);
        updated_message->creation_date = utc_str_to_localtime_tm(received_creation_date, DEFAULT_TIME_FORMAT);
        free(received_creation_date);
        mx_push_back(&updated_messages_list.list, updated_message);
    }

    close(client_socket);

    return updated_messages_list;
}

t_user *rq_get_chat_members(t_address server_address, id_t chat_id, uint32_t *members_count) {
    int client_socket = create_and_connect_socket(server_address);

    t_package package = create_package(2);
    pack_byte(GET_CHAT_MEMBERS, &package);
    pack_uint32(chat_id, &package);
    send_and_free_package(client_socket, package);

    *members_count = receive_uint32(client_socket);
    t_user *members = malloc(*members_count * sizeof(t_user));
    for (size_t i = 0; i < *members_count; i++) {
        members[i].id = receive_uint32(client_socket);
        members[i].login = receive_bytes(client_socket);
    }

    close(client_socket);

    return members;
}

t_state_code rq_remove_member_from_chat(t_address server_address, id_t user_id, id_t chat_id) {
    int client_socket = create_and_connect_socket(server_address);

    t_package package = create_package(3);
    pack_byte(REMOVE_USER_FROM_CHAT, &package);
    pack_uint32(user_id, &package);
    pack_uint32(chat_id, &package);
    send_and_free_package(client_socket, package);

    t_state_code removing_member_from_chat_result = receive_byte(client_socket);

    close(client_socket);

    return removing_member_from_chat_result;
}
