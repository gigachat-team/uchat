#include "../client.h"

t_state_code send_authenticate_user_request(t_authentication_data authentication_data, t_authentication_mode authentication_mode, t_address server_address) {
    if (authentication_mode != REGISTER_MODE && authentication_mode != LOGIN_MODE) {
        printf("authenticate_user: There is only two authentication modes.");
        exit(EXIT_FAILURE);
    }

    int client_socket = create_socket();
    connect_socket(client_socket, server_address.ip, server_address.port);

    send_unsigned_char(client_socket, authentication_mode);
    recieve_unsigned_char(client_socket);

    send(client_socket, authentication_data.login, strlen(authentication_data.login) + 1, 0);
    recieve_unsigned_char(client_socket);

    send(client_socket, authentication_data.password, strlen(authentication_data.password) + 1, 0);
    recieve_unsigned_char(client_socket);

    t_state_code authentication_result = recieve_unsigned_char(client_socket);

    close(client_socket);

    return authentication_result;
}

t_state_code send_create_chat_requests(t_chat_creation_data chat_data, t_address server_address) {
    int client_socket = create_socket();
    connect_socket(client_socket, server_address.ip, server_address.port);

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

t_state_code send_add_new_member_request(t_address server_address, t_new_chat_member_data new_chat_member_data) {
    int client_socket = create_socket();
    connect_socket(client_socket, server_address.ip, server_address.port);

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

