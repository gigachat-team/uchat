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
