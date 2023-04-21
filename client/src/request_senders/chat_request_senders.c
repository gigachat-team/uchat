#include "request_senders.h"

id_t rq_create_chat(t_address server_address, char *chat_name, id_t owner_id) {
    int client_socket = create_and_connect_socket(server_address);
    if (errno == ECONNREFUSED) return 0;

    t_package package = create_package(3);
    pack_byte(CREATE_CHAT, &package);
    pack_bytes(chat_name, &package);
    pack_uint32(owner_id, &package);
    send_and_free_package(client_socket, &package);

    id_t created_chat_id = receive_uint32(client_socket);

    close(client_socket);

    return created_chat_id;
}

t_chat *rq_get_chats_i_am_in(t_address server_address, id_t user_id, size_t *chats_count) {
    int client_socket = create_and_connect_socket(server_address);
    if (errno == ECONNREFUSED) return NULL;

    t_package package = create_package(2);
    pack_byte(GET_CHATS_I_AM_IN, &package);
    pack_uint32(user_id, &package);
    send_and_free_package(client_socket, &package);

    *chats_count = receive_uint32(client_socket);
    t_chat *chats_i_am_in = *chats_count == 0 ? NULL : malloc(*chats_count * sizeof(t_chat));
    for (size_t i = 0; i < *chats_count; i++) {
        chats_i_am_in[i].id = receive_uint32(client_socket);
        chats_i_am_in[i].name = receive_bytes(client_socket);
        chats_i_am_in[i].owner_id = receive_uint32(client_socket);
    }

    close(client_socket);

    return chats_i_am_in;
}
