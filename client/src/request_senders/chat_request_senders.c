#include "request_senders.h"

id_t rq_create_chat(t_address *server_address, char *chat_name, id_t owner_id) {
    int client_socket = create_and_connect_socket(server_address);
    if (client_socket == -1) return 0;

    t_package package = create_package(3);
    pack_byte(CREATE_CHAT, &package);
    pack_bytes(chat_name, &package);
    pack_uint32(owner_id, &package);
    send_and_free_package(client_socket, &package);

    id_t created_chat_id = receive_uint32(client_socket);

    close(client_socket);

    return created_chat_id;
}

list_t *rq_get_chats_i_am_in(t_address *server_address, id_t user_id) {
    int client_socket = create_and_connect_socket(server_address);
    if (client_socket == -1) return NULL;

    t_package package = create_package(2);
    pack_byte(GET_CHATS_I_AM_IN, &package);
    pack_uint32(user_id, &package);
    send_and_free_package(client_socket, &package);

    size_t chats_count = receive_uint32(client_socket);
    list_t *chats_list = list_new();
    for (size_t i = 0; i < chats_count; i++) {
        t_chat *chat = malloc(sizeof(t_chat));
        chat->id = receive_uint32(client_socket);
        chat->name = receive_bytes(client_socket);
        chat->owner_id = receive_uint32(client_socket);
        list_rpush(chats_list, list_node_new(chat));
    }

    close(client_socket);

    return chats_list;
}
