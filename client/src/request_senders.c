#include "../client.h"

t_state_code rq_authenticate_user(t_address server_address, t_authentication_data authentication_data, t_authentication_mode authentication_mode, uint *user_id) {
    int client_socket = create_and_connect_socket(server_address);

    send_unsigned_char(client_socket, authentication_mode);
    send_string(client_socket, authentication_data.login);
    send_string(client_socket, authentication_data.password);

    t_state_code authentication_result = receive_unsigned_char(client_socket);
    if (authentication_result == SUCCESSFUL_LOGIN || authentication_result == SUCCESSFUL_REGISTRATION) {
        *user_id = receive_unsigned_int(client_socket);
    }

    close(client_socket);

    return authentication_result;
}

t_state_code rq_create_chat(t_address server_address, t_chat_creation_data chat_data) {
    int client_socket = create_and_connect_socket(server_address);

    send_unsigned_char(client_socket, CREATE_CHAT);
    send_string(client_socket, chat_data.chat_name);
    send_unsigned_int(client_socket, chat_data.owner_id);

    t_state_code creating_chat_result = receive_unsigned_char(client_socket);

    close(client_socket);

    return creating_chat_result;
}

t_chat *rq_get_chats_i_am_in(t_address server_address, id_t user_id, size_t *chats_count) {
    int client_socket = create_and_connect_socket(server_address);

    send_unsigned_char(client_socket, GET_CHATS_I_AM_IN);
    send_unsigned_int(client_socket, user_id);

    *chats_count = receive_unsigned_int(client_socket);
    t_chat *chats_i_am_in = *chats_count == 0 ? NULL : malloc(*chats_count * sizeof(t_chat));
    for (size_t i = 0; i < *chats_count; i++) {
        chats_i_am_in[i].id = receive_unsigned_int(client_socket);
        chats_i_am_in[i].name = receive_string(client_socket);
    }

    close(client_socket);

    return chats_i_am_in;
}

t_state_code rq_add_new_member(t_address server_address, t_new_chat_member_data new_chat_member_data) {
    int client_socket = create_and_connect_socket(server_address);

    send_unsigned_char(client_socket, ADD_MEMBER_TO_CHAT);
    send_unsigned_int(client_socket, new_chat_member_data.chat_id);
    send_string(client_socket, new_chat_member_data.member_login);

    t_state_code adding_new_member_to_chat_result = receive_unsigned_char(client_socket);

    close(client_socket);

    return adding_new_member_to_chat_result;
}

t_state_code rq_send_text_message(t_address server_address, t_text_message_data text_message_data) {
    int client_socket = create_and_connect_socket(server_address);
    send_unsigned_char(client_socket, SEND_TEXT_MESSAGE);
    send_unsigned_int(client_socket, text_message_data.user_id);
    send_unsigned_int(client_socket, text_message_data.chat_id);
    send_string(client_socket, text_message_data.text);

    t_state_code response = receive_unsigned_char(client_socket);

    close(client_socket);

    return response;
}

t_user_message *rq_get_last_messages(t_address server_address, uint16_t messages_count, id_t chat_id, uint16_t *found_messages_count) {
    int client_socket = create_and_connect_socket(server_address);
    send_unsigned_char(client_socket, GET_LAST_MESSAGES);
    send_unsigned_short(client_socket, messages_count);
    send_unsigned_int(client_socket, chat_id);

    *found_messages_count = receive_unsigned_short(client_socket);
    t_user_message *found_messages = malloc(*found_messages_count * sizeof(t_user_message));
    for (size_t i = 0; i < *found_messages_count; i++) {
        found_messages[i].user_id = receive_unsigned_int(client_socket);
        found_messages[i].user_login = receive_string(client_socket);
        found_messages[i].bytes = receive_string(client_socket);
    }

    close(client_socket);

    return found_messages;
}

t_user *rq_get_chat_members(t_address server_address, id_t chat_id, uint32_t *members_count) {
    int client_socket = create_and_connect_socket(server_address);

    send_unsigned_char(client_socket, GET_CHAT_MEMBERS);
    send_unsigned_int(client_socket, chat_id);

    *members_count = receive_unsigned_int(client_socket);
    t_user *members = malloc(*members_count * sizeof(t_user));
    for (size_t i = 0; i < *members_count; i++) {
        members[i].id = receive_unsigned_int(client_socket);
        members[i].login = receive_string(client_socket);
    }

    close(client_socket);

    return members;
}
