#include "../server.h"

void *handle_request_thread(void *client_socket_void) {
    int client_socket = *(int *)client_socket_void;
    free(client_socket_void);

    sqlite3 *database = open_database();

    t_request client_request = recieve_unsigned_char(client_socket);
    send_unsigned_char(client_socket, SUCCESSFULLY_READ);

    if (client_request == LOGIN) {
        char login[MAX_LOGIN_LENGTH];
        read(client_socket, login, MAX_LOGIN_LENGTH);
        send_unsigned_char(client_socket, SUCCESSFULLY_READ);

        char password[MAX_PASSWORD_LENGTH];
        read(client_socket, password, MAX_PASSWORD_LENGTH);

        char *found_password = NULL;

        if (get_password_by_login_in_users_table(database, login, &found_password) != SQLITE_OK) {
            send_unsigned_char(client_socket, SUCH_LOGIN_DOES_NOT_EXIST);
        } else {
            if (strcmp(password, found_password) == 0) {
                send_unsigned_char(client_socket, SUCCESSFUL_LOGIN);
            } else {
                send_unsigned_char(client_socket, WRONG_PASSWORD);
            }
        }

        free(found_password);
    } else if (client_request == REGISTER) {
        char login[MAX_LOGIN_LENGTH];
        read(client_socket, login, MAX_LOGIN_LENGTH);
        send_unsigned_char(client_socket, SUCCESSFULLY_READ);

        char password[MAX_PASSWORD_LENGTH];
        read(client_socket, password, MAX_PASSWORD_LENGTH);

        if (insert_to_users_table(database, login, password) != SQLITE_OK) {
            send_unsigned_char(client_socket, SUCH_LOGIN_ALREADY_EXISTS);
        } else {
            send_unsigned_char(client_socket, SUCCESSFUL_REGISTRATION);
        }
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

