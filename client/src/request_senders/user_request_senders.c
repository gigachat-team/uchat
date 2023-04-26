#include "request_senders.h"

t_state_code rq_authenticate_user(t_address *server_address, char *login, char *password, t_authentication_mode authentication_mode, id_t *user_id) {
    int client_socket = create_and_connect_socket(server_address);
    if (client_socket == -1) return CONNECTION_REFUSED;

    t_package package = create_package(3);
    pack_byte(authentication_mode, &package);
    pack_bytes(login, &package);
    pack_bytes(password, &package);
    send_and_free_package(client_socket, &package);

    t_state_code authentication_result = receive_byte(client_socket);
    if (authentication_result == SUCCESSFUL_LOGIN || authentication_result == SUCCESSFUL_REGISTRATION) {
        *user_id = receive_uint32(client_socket);
    }

    close(client_socket);

    return authentication_result;
}

t_state_code rq_change_login(t_address *server_address, id_t user_id, char *new_login) {
    int client_socket = create_and_connect_socket(server_address);
    if (client_socket == -1) return CONNECTION_REFUSED;

    t_package package = create_package(3);
    pack_byte(CHANGE_LOGIN, &package);
    pack_uint32(user_id, &package);
    pack_bytes(new_login, &package);
    send_and_free_package(client_socket, &package);

    t_state_code responce = receive_byte(client_socket);

    close(client_socket);

    return responce;
}

bool rq_delete_account(t_address *server_address, id_t user_id) {
    int client_socket = create_and_connect_socket(server_address);
    if (client_socket == -1) return false;

    t_package package = create_package(2);
    pack_byte(DELETE_ACCOUNT, &package);
    pack_uint32(user_id, &package);
    send_and_free_package(client_socket, &package);

    close(client_socket);

    return true;
}
