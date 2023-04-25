#include "request_senders.h"

t_state_code rq_change_login(t_address *server_address, id_t user_id, char *new_login) {
    int client_socket = create_and_connect_socket(server_address);
    if (client_socket == -1) return CONNECTION_REFUSED;

    t_package package = create_package(2);
    pack_uint32(user_id, &package);
    pack_bytes(new_login, &package);
    send_and_free_package(client_socket, &package);

    t_state_code responce = receive_byte(client_socket);

    close(client_socket);

    return responce;
}
