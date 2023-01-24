#include "../inc/requests.h"

t_database_and_socket *create_database_and_socket(sqlite3 *database, int socket) {
    t_database_and_socket *database_and_socket = malloc(sizeof(t_database_and_socket));
    database_and_socket->database = database;
    database_and_socket->socket = socket;
    return database_and_socket;
}

void *handle_request_thread(void *database_and_client_socket) {
    t_database_and_socket *args = (t_database_and_socket *)database_and_client_socket;
    int client_socket = args->socket;
    sqlite3 *database = args->database;
    free(args);

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

    pthread_exit(NULL);
}

void *accept_requests_thread(void *database_and_listening_socket) {
    t_database_and_socket *args = (t_database_and_socket *)database_and_listening_socket;
    int listening_socket = args->socket;
    sqlite3 *database = args->database;
    free(args);

    while (true)
    {
        int client_socket = accept_socket(listening_socket);
        handle_request_in_new_thread(database, client_socket);
    }
}

pthread_t accept_requests_in_new_thread(sqlite3 *database, int listening_socket) {
    t_database_and_socket *database_and_listening_socket = create_database_and_socket(database, listening_socket);
    return create_default_thread(accept_requests_thread, database_and_listening_socket);
}

pthread_t handle_request_in_new_thread(sqlite3 *database, int client_socket) {
    t_database_and_socket *database_and_client_socket = create_database_and_socket(database, client_socket);
    return create_default_thread(handle_request_thread, database_and_client_socket);
}

