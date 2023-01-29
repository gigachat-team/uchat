#include "../server.h"

t_authentication_data recieve_authentication_data(int socket) {
    char login[MAX_LOGIN_LENGTH];
    read(socket, login, MAX_LOGIN_LENGTH);
    send_unsigned_char(socket, SUCCESSFULLY_READ);

    char password[MAX_PASSWORD_LENGTH];
    read(socket, password, MAX_PASSWORD_LENGTH);
    send_unsigned_char(socket, SUCCESSFULLY_READ);

    t_authentication_data authentication_data;
    authentication_data.login = mx_strdup(login);
    authentication_data.password = mx_strdup(password);

    return authentication_data;
}

t_chat_creation_data recieve_chat_creation_data(int socket) {
    char *chat_name = recieve_string(socket, MAX_CHAT_NAME_LENGTH);
    send_unsigned_char(socket, SUCCESSFULLY_READ);

    char *owner_login = recieve_string(socket, MAX_LOGIN_LENGTH);
    send_unsigned_char(socket, SUCCESSFULLY_READ);

    t_chat_creation_data chat_cration_data = {chat_name, owner_login};
    return chat_cration_data;
}

