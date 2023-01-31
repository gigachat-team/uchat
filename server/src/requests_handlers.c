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
    int owner_id = db_get_user_id_by_login(chat_creation_data.owner_login);
    db_create_chat(chat_creation_data.chat_name, owner_id);
    send_unsigned_char(client_socket, CHAT_CREATED_SUCCESSFULLY);

    free_chat_creation_data(chat_creation_data);
}

void handle_getting_chats(int client_socket) {
    char *user_login = recieve_string(client_socket, MAX_LOGIN_LENGTH);
    send_unsigned_char(client_socket, SUCCESSFULLY_READ);
    int user_id = db_get_user_id_by_login(user_login);

    size_t number_of_chats = 0;
    t_chat *chats = db_get_chats_user_is_in(user_id, &number_of_chats);

    send_unsigned_char(client_socket, START_OF_CHATS_ARRAY);
    for (size_t i = 0; i < number_of_chats; i++) {
        send_chat(client_socket, chats[i]);
        if (i + 1 == number_of_chats) {
            send_unsigned_char(client_socket, END_OF_CHATS_ARRAY);
        } else {
            send_unsigned_char(client_socket, CONTINUATION_OF_CHATS_ARRAY);
        }
    }

    send_unsigned_char(client_socket, CHATS_ARRAY_TRENSFERRED_SUCCESSFULLY);

    free(user_login);
    free_chats(chats, number_of_chats);
}

