#include "../server.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("usage: ./uchat_server [port]\n");
        return 0;
    }

    daemon_server();
    db_create_users_table();
    db_create_chats_table();
    db_create_message_statuses_table();
    db_create_messages_table();
    db_create_members_table();

    int listening_socket = create_socket();
    bind_socket(listening_socket, atoi(argv[1]));
    listen_socket(listening_socket, 5);

    pthread_t listening_thread = create_default_thread(accept_requests_thread, &listening_socket);

    printf("Server is listening for user requests.\n");

    while (true)
    {
        printf("\nEnter a command (exit): ");
        char user_command[1024];
        scanf("%s", user_command);

        if (strcmp(user_command, "exit") == 0) {
            close(listening_socket);
            cancel_thread(listening_thread);
            join_thread(listening_thread, NULL);
            exit(EXIT_FAILURE);
        }
    }
}

