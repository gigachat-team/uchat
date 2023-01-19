#include "../inc/main.h"

int main(int argc, char **argv) {
    if (argc != 3) {
        printf("usage: ./uchat [ip] [port]");
        return 0;
    }

    while (true)
    {
        char inputed_string[1024];
        printf("Enter a string: ");
        scanf("%s", inputed_string);

        int client_socket = create_socket();
        connect_socket(client_socket, argv[1], atoi(argv[2]));
        write(client_socket, inputed_string, strlen(inputed_string));
        close(client_socket);
        
        if (strcmp(inputed_string, "exit") == 0) {
            return 0;
        }
    }

    return 0;
}

