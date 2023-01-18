#include "../inc/header.h"

void send_string_to_server(int socket_fd) {
    char buffer[BUFFER_SIZE];
    int n = 0;

    while (true) {
        bzero(buffer, sizeof(buffer));
        printf("Enter a string: ");

        for (n = 0; (buffer[n] = getchar()) != '\n'; n++);

        if (strcmp(buffer, "exit\n") == 0) {
            printf("Log: Exiting\n");
            bzero(buffer, sizeof(buffer));
            break;
        }

        write(socket_fd, buffer, sizeof(buffer));
        bzero(buffer, sizeof(buffer));
        read(socket_fd, buffer, sizeof(buffer));
        printf("Log: Received from Server: '%s'\n", buffer);

    }
}

int main() {
    int socket_fd;
    
    struct sockaddr_in server_address, client_address;

    socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (socket_fd == -1) {
        printf("Error: failed to create a socket\n");
        return 1;
    }

    printf("Log: Client socket was successfully created\n");

    bzero(&server_address, sizeof(server_address));

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1"); 
    server_address.sin_port = htons(PORT);

    if (connect(socket_fd, (struct sockaddr*)&server_address, sizeof(server_address)) != 0) {
		printf("Error: Connection with the server failed\n");
		return 1;
	}
	
	printf("Log: Connected to the server\n");
    send_string_to_server(socket_fd);
    close(socket_fd);
    printf("Log: Client socket is closed\n");

    return 0;
}