#include "../server.h"

void handle_registration(int client_socket) {
    t_authentication_data authentication_data = recieve_authentication_data(client_socket);
    if (db_create_user(authentication_data.login, authentication_data.password)) {
        send_unsigned_char(client_socket, SUCCESSFUL_REGISTRATION);
    } else {
        send_unsigned_char(client_socket, SUCH_LOGIN_ALREADY_EXISTS);
    }

    free_authentication_data(authentication_data);
}

void handle_login(int client_socket) {
    t_authentication_data authentication_data = recieve_authentication_data(client_socket);
    char *found_password = NULL;
    if (db_get_password_by_login(authentication_data.login, &found_password)) {
        if (strcmp(authentication_data.password, found_password) == 0) {
            send_unsigned_char(client_socket, SUCCESSFUL_LOGIN);
        } else {
            send_unsigned_char(client_socket, WRONG_PASSWORD);
        }
    } else {
        send_unsigned_char(client_socket, SUCH_LOGIN_DOES_NOT_EXIST);
    }

    free(found_password);
    free_authentication_data(authentication_data);
}

void handle_chat_creation(int client_socket) {
    t_chat_creation_data chat_creation_data = recieve_chat_creation_data(client_socket);

    int owner_id;
    db_get_user_id_by_login(chat_creation_data.owner_login, &owner_id);

    db_create_chat(chat_creation_data.chat_name, owner_id);

    send_unsigned_char(client_socket, CHAT_CREATED_SUCCESSFULLY);

    free_chat_creation_data(chat_creation_data);
}

