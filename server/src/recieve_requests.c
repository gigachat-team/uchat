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

void *handle_request_thread(void *client_socket_void) {
    int client_socket = *(int *)client_socket_void;
    free(client_socket_void);

    sqlite3 *database = open_database();

    t_request client_request = recieve_unsigned_char(client_socket);
    send_unsigned_char(client_socket, SUCCESSFULLY_READ);

    if (client_request == LOGIN) {
        t_authentication_data authentication_data = recieve_authentication_data(client_socket);
        char *found_password = NULL;
        if (get_password_by_login_in_users_table(database, authentication_data.login, &found_password) != SQLITE_OK) {
            send_unsigned_char(client_socket, SUCH_LOGIN_DOES_NOT_EXIST);
        } else {
            if (strcmp(authentication_data.password, found_password) == 0) {
                send_unsigned_char(client_socket, SUCCESSFUL_LOGIN);
            } else {
                send_unsigned_char(client_socket, WRONG_PASSWORD);
            }
        }

        free(found_password);
        free_authentication_data(authentication_data);
    } else if (client_request == REGISTER) {
        t_authentication_data authentication_data = recieve_authentication_data(client_socket);
        if (insert_to_users_table(database, authentication_data.login, authentication_data.password) != SQLITE_OK) {
            send_unsigned_char(client_socket, SUCH_LOGIN_ALREADY_EXISTS);
        } else {
            send_unsigned_char(client_socket, SUCCESSFUL_REGISTRATION);
        }

        free_authentication_data(authentication_data);
    }

    close_database(database);
    pthread_exit(NULL);
}

void *accept_requests_thread(void *listening_socket_void) {
    int listening_socket = *(int *)listening_socket_void;

    while (true)
    {
        int *client_socket = malloc(sizeof(int));
        *client_socket = accept_socket(listening_socket);
        create_detached_thread(handle_request_thread, client_socket);
    }
}

