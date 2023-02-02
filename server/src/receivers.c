#include "../server.h"

t_authentication_data receive_authentication_data(int client_socket) {
    char *login = receive_string(client_socket);
    char *password = receive_string(client_socket);

    t_authentication_data authentication_data = {login, password};
    return authentication_data;
}

t_chat_creation_data receive_chat_creation_data(int client_socket) {
    char *chat_name = receive_string(client_socket);
    char *owner_login = receive_string(client_socket);

    t_chat_creation_data chat_cration_data = {chat_name, owner_login};
    return chat_cration_data;
}

t_new_chat_member_data receive_new_chat_memeber_data(int client_socket) {
    int chat_id = receive_unsigned_int(client_socket);
    char *memeber_login = receive_string(client_socket);

    t_new_chat_member_data new_chat_memeber_data = {chat_id, memeber_login};
    return new_chat_memeber_data;
}

