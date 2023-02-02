#include "../server.h"

t_authentication_data recieve_authentication_data(int client_socket) {
    char *login = recieve_string(client_socket);
    char *password = recieve_string(client_socket);

    t_authentication_data authentication_data = {login, password};
    return authentication_data;
}

t_chat_creation_data recieve_chat_creation_data(int client_socket) {
    char *chat_name = recieve_string(client_socket);
    char *owner_login = recieve_string(client_socket);

    t_chat_creation_data chat_cration_data = {chat_name, owner_login};
    return chat_cration_data;
}

t_new_chat_member_data recieve_new_chat_memeber_data(int client_socket) {
    int chat_id = recieve_unsigned_int(client_socket);
    char *memeber_login = recieve_string(client_socket);

    t_new_chat_member_data new_chat_memeber_data = {chat_id, memeber_login};
    return new_chat_memeber_data;
}

