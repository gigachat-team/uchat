#include "../server.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("usage: ./uchat_server [port]\n");
        return 0;
    }

    // daemon_server();

    sqlite3 *db = db_open();
    db_create_users_table(db);
    db_create_chats_table(db);
    db_create_message_statuses_table(db);
    db_create_messages_table(db);
    db_create_members_table(db);
    db_close(db);

    int listening_socket = create_socket();
    bind_socket(listening_socket, atoi(argv[1]));
    listen_socket(listening_socket, 5);

    while (true)
    {
        int client_socket = accept_socket(listening_socket);
        int *mallocated_client_socket = malloc(sizeof(int));
        *mallocated_client_socket = client_socket;
        create_detached_thread(handle_request_thread, mallocated_client_socket);
    }
}

