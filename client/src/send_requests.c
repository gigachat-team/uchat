#include "../client.h"

t_state_code send_authenticate_user_request(t_authentication_data authentication_data, t_authentication_mode authentication_mode, t_address server_address) {
    int client_socket = create_and_connect_socket(server_address);

    send_unsigned_char(client_socket, authentication_mode);
    recieve_unsigned_char(client_socket);

    send_string(client_socket, authentication_data.login);
    recieve_unsigned_char(client_socket);

    send_string(client_socket, authentication_data.password);
    recieve_unsigned_char(client_socket);

    t_state_code authentication_result = recieve_unsigned_char(client_socket);

    close(client_socket);

    return authentication_result;
}

t_state_code send_create_chat_request(t_chat_creation_data chat_data, t_address server_address) {
    int client_socket = create_and_connect_socket(server_address);

    send_unsigned_char(client_socket, CREATE_CHAT);
    recieve_unsigned_char(client_socket);

    send_string(client_socket, chat_data.chat_name);
    recieve_unsigned_char(client_socket);

    send_string(client_socket, chat_data.owner_login);
    recieve_unsigned_char(client_socket);

    t_state_code creating_chat_result = recieve_unsigned_char(client_socket);

    close(client_socket);

    return creating_chat_result;
}

t_state_code get_chats_i_am_in(t_address server_address, char *user_login, t_chat **chats_i_am_in, size_t *chats_i_am_in_length) {
    int client_socket = create_and_connect_socket(server_address);

    send_unsigned_char(client_socket, GET_CHATS_I_AM_IN);
    recieve_unsigned_char(client_socket);

    send_string(client_socket, user_login);
    recieve_unsigned_char(client_socket);

    *chats_i_am_in_length = 0;
    t_state_code recieving_chat_datas_state_code = recieve_unsigned_char(client_socket);
    while (recieving_chat_datas_state_code != END_OF_CHATS_ARRAY) {
        t_chat chat_data = recieve_chat(client_socket);
        *chats_i_am_in = realloc(*chats_i_am_in, sizeof(t_chat) * ++(*chats_i_am_in_length));
        (*chats_i_am_in)[*chats_i_am_in_length - 1] = chat_data;
        recieving_chat_datas_state_code = recieve_unsigned_char(client_socket);
    }

    t_state_code resulting_state_code = recieve_unsigned_char(client_socket);

    close(client_socket);

    return resulting_state_code;
}

t_state_code send_add_new_member_request(t_address server_address, t_new_chat_member_data new_chat_member_data) {
    int client_socket = create_and_connect_socket(server_address);

    send_unsigned_char(client_socket, ADD_MEMBER_TO_CHAT);
    recieve_unsigned_char(client_socket);

    send_unsigned_int(client_socket, new_chat_member_data.chat_id);
    recieve_unsigned_char(client_socket);

    send_string(client_socket, new_chat_member_data.member_login);
    recieve_unsigned_char(client_socket);

    t_state_code adding_new_member_to_chat_result = recieve_unsigned_char(client_socket);

    close(client_socket);

    return adding_new_member_to_chat_result;
}

