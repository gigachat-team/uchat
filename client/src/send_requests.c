#include "../client.h"

t_state_code authenticate_user(t_authentication_data authentication_data, t_authentication_mode authentication_mode, t_address server_address) {
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

t_state_code create_chat(t_chat_data chat_data, t_address server_address) {
    int client_socket = create_socket();
    connect_socket(client_socket, server_address.ip, server_address.port);

    send_unsigned_char(client_socket, CREATE_CHAT);
    recieve_unsigned_char(client_socket);

    send_string(client_socket, chat_data.name);
    recieve_unsigned_char(client_socket);

    for (size_t i = 0; chat_data.member_logins[i] != NULL; i++)
    {
        send_string(client_socket, chat_data.member_logins[i]);
        recieve_unsigned_char(client_socket);
    }

    t_state_code creating_chat_result = recieve_unsigned_char(client_socket);

    close(client_socket);

    return creating_chat_result;
}

