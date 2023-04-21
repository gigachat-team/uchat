#include "request_senders.h"

t_state_code rq_add_new_member(t_address server_address, id_t chat_id, char *new_member_login) {
    int client_socket = create_and_connect_socket(server_address);
    if (client_socket == -1) return 0;

    t_package package = create_package(3);
    pack_byte(ADD_MEMBER_TO_CHAT, &package);
    pack_uint32(chat_id, &package);
    pack_bytes(new_member_login, &package);
    send_and_free_package(client_socket, &package);

    t_state_code adding_new_member_to_chat_result = receive_byte(client_socket);

    close(client_socket);

    return adding_new_member_to_chat_result;
}

t_user *rq_get_chat_members(t_address server_address, id_t chat_id, uint32_t *members_count) {
    int client_socket = create_and_connect_socket(server_address);
    if (client_socket == -1) return NULL;

    t_package package = create_package(2);
    pack_byte(GET_CHAT_MEMBERS, &package);
    pack_uint32(chat_id, &package);
    send_and_free_package(client_socket, &package);

    *members_count = receive_uint32(client_socket);
    t_user *members = malloc(*members_count * sizeof(t_user));
    for (size_t i = 0; i < *members_count; i++) {
        members[i].id = receive_uint32(client_socket);
        members[i].login = receive_bytes(client_socket);
    }

    close(client_socket);

    return members;
}

t_state_code rq_remove_member_from_chat(t_address server_address, id_t user_id, id_t chat_id) {
    int client_socket = create_and_connect_socket(server_address);
    if (client_socket == -1) return 0;

    t_package package = create_package(3);
    pack_byte(REMOVE_USER_FROM_CHAT, &package);
    pack_uint32(user_id, &package);
    pack_uint32(chat_id, &package);
    send_and_free_package(client_socket, &package);

    t_state_code removing_member_from_chat_result = receive_byte(client_socket);

    close(client_socket);

    return removing_member_from_chat_result;
}
