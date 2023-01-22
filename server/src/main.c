#include "../inc/main.h"

void handle_client_request(int client_socket, sqlite3 *database) {
    t_request client_request = recieve_unsigned_char(client_socket);
    send_unsigned_char(client_socket, SUCCESSFULLY_READ);

    if (client_request == LOGIN) {
        
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
}

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("usage: ./uchat_server [port]\n");
        return 0;
    }

    sqlite3 *database = open_database();
    sqlite3_exec(database, USERS_TABLE_CREATION_SQL, NULL, NULL, NULL);

    int listening_socket = create_socket();
    bind_socket(listening_socket, atoi(argv[1]));
    listen_socket(listening_socket, 5);

    while (true)
    {
        int client_socket = accept_socket(listening_socket);
        handle_client_request(client_socket, database);
    }
    
    return 0;
}

