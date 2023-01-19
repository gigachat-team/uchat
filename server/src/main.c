#include "../inc/main.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("usage: ./uchat_server [port]\n");
        return 0;
    }

    int listening_socket = create_socket();
    bind_socket(listening_socket, atoi(argv[1]));
    listen_socket(listening_socket, 5);

    while (true)
    {
        int client_socket = accept_socket(listening_socket);

        int read_bytes_count = 0;
        char *read_bytes = read_socket(client_socket, 1024, &read_bytes_count);
        if (strcmp(read_bytes, "exit") == 0) {
            free(read_bytes);
            close(client_socket);
            close(listening_socket);
            return 0;
        }
        write(STDOUT_FILENO, read_bytes, read_bytes_count);
        printf("\n");
        free(read_bytes);
        close(client_socket);
    }
    
    return 0;
}

