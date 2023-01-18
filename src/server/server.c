#include "../../inc/header.h"

void chat_between_server_and_client(int connection_fd, int socket_fd) {
    char buffer[BUFFER_SIZE];

    while (true) {
        if (connection_fd == -1 || socket_fd == -1) {
            break;
        }
        bzero(buffer, BUFFER_SIZE);
		read(connection_fd, buffer, sizeof(buffer));
		printf("\nLog: From client: %s\n", buffer);

		if (strcmp("exit", buffer) == 0) {
			printf("Log: Server Exit...\n");
			break;
		}

        write(connection_fd, buffer, sizeof(buffer));
    }
}

void print_error(char *error) {
    write(2, error, strlen(error));
    exit(1);
}

void catch_socket_creation_error(int socket_fd) {
    if (socket_fd == -1) {
        print_error("Error: Failed to create a socket\n");
    }
    printf("Log: Socket was successfully created\n");
}

void catch_listening_error(int socket_fd) {
    if (listen(socket_fd, 5) != 0) {
        close(socket_fd);
        print_error("Error: listen was failed\n");
    }

    printf("Log: Server is listening\n");
} 

void catch_connection_error(int connection_fd, int socket_fd) {
    if (connection_fd < 0) {
        close(connection_fd);
        close(socket_fd);
        print_error("Error: server accepting failed\n");
    }

    printf("Log: Server accepted a client\n");
}

int main() {
    int socket_fd;
    int connection_fd;

    socklen_t len;

    struct sockaddr_in server_address, client_address;

    socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    
    catch_socket_creation_error(socket_fd);

    bzero(&server_address, sizeof(server_address));

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(PORT);
    
	if ((bind(socket_fd, (SA*)&server_address, sizeof(server_address))) != 0) {
		printf("Error: failed to bind the socket\n");
		return 1;
	}
	
    printf("Log: The socket was successfully binded\n");

    catch_listening_error(socket_fd);

    len = sizeof(client_address);
    connection_fd = accept(socket_fd, (SA*)&client_address, &len);

    catch_connection_error(connection_fd, socket_fd);
    chat_between_server_and_client(connection_fd, socket_fd);

    close(socket_fd);
    printf("Log: Listening socket is closed\n");

    close(connection_fd);
    printf("Log: Connectionfd socket is closed\n");

    return 0;
}

