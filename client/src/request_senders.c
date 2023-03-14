#include "../client.h"

t_state_code rq_authenticate_user(t_address server_address, t_authentication_data authentication_data, t_authentication_mode authentication_mode, uint *user_id) {
    int client_socket = create_and_connect_socket(server_address);

    t_package package = create_package(3);
    pack_byte(authentication_mode, &package);
    pack_bytes(authentication_data.login, &package);
    pack_bytes(authentication_data.password, &package);
    send_and_free_package(client_socket, package);

    t_state_code authentication_result = receive_byte(client_socket);
    if (authentication_result == SUCCESSFUL_LOGIN || authentication_result == SUCCESSFUL_REGISTRATION) {
        *user_id = receive_uint32(client_socket);
    }

    close(client_socket);

    return authentication_result;
}

id_t rq_create_chat(t_address server_address, t_chat_creation_data chat_data) {
    int client_socket = create_and_connect_socket(server_address);

    t_package package = create_package(3);
    pack_byte(CREATE_CHAT, &package);
    pack_bytes(chat_data.chat_name, &package);
    pack_uint32(chat_data.owner_id, &package);
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

t_state_code rq_send_text_message(t_address server_address, t_text_message_data text_message_data) {
    int client_socket = create_and_connect_socket(server_address);

    t_package package = create_package(4);
    pack_byte(SEND_TEXT_MESSAGE, &package);
    pack_uint32(text_message_data.user_id, &package);
    pack_uint32(text_message_data.chat_id, &package);
    pack_bytes(text_message_data.text, &package);
    send_and_free_package(client_socket, package);

    t_state_code response = receive_byte(client_socket);

    close(client_socket);

    return response;
}

t_user_message *rq_get_last_messages(t_address server_address, uint32_t msg_number, uint16_t messages_count, id_t chat_id, uint16_t *found_messages_count) {
    int client_socket = create_and_connect_socket(server_address);

    t_package package = create_package(4);
    pack_byte(GET_LAST_MESSAGES, &package);
    pack_uint16(messages_count, &package);
    pack_uint32(chat_id, &package);
    pack_uint32(msg_number, &package);
    send_and_free_package(client_socket, package);

    *found_messages_count = receive_uint16(client_socket);
    t_user_message *found_messages = malloc(*found_messages_count * sizeof(t_user_message));
    for (size_t i = 0; i < *found_messages_count; i++) {
        found_messages[i].user_id = receive_uint32(client_socket);
        found_messages[i].user_login = receive_bytes(client_socket);
        found_messages[i].bytes = receive_bytes(client_socket);
        char *received_creation_date = receive_bytes(client_socket);
        found_messages[i].creation_date = utc_str_to_localtime_tm(received_creation_date, DEFAULT_TIME_FORMAT);
        free(received_creation_date);
        found_messages[i].order_in_chat = receive_uint32(client_socket);
    }

    close(client_socket);

    return found_messages;
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
