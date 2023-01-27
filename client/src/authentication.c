#include "../client.h"

char *Server_ip = NULL;
int Server_port = 0;

void init_authentication(char *server_ip, int server_port) {
    Server_ip = server_ip;
    Server_port = server_port;
}

t_state_code authenticate_user(t_authentication_data authentication_data, t_authentication_mode authentication_mode) {
    if (authentication_mode != REGISTER_MODE && authentication_mode != LOGIN_MODE) {
        printf("authenticate_user: There is only two authentication modes.");
        exit(EXIT_FAILURE);
    }

    int client_socket = create_socket();
    connect_socket(client_socket, Server_ip, Server_port);

    send_unsigned_char(client_socket, authentication_mode);
    recieve_unsigned_char(client_socket);

    send(client_socket, authentication_data.login, strlen(authentication_data.login) + 1, 0);
    recieve_unsigned_char(client_socket);

    send(client_socket, authentication_data.password, strlen(authentication_data.password) + 1, 0);

    t_state_code authentication_result = recieve_unsigned_char(client_socket);

    close(client_socket);

    return authentication_result;
}

