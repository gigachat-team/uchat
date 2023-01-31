#include "../utils.h"

int create_socket() {
    int created_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (created_socket == -1) {
        perror("Failed to create a socket");
        exit(EXIT_FAILURE);
    }

    return created_socket;
}

void bind_socket(int socket, unsigned int port) {
    struct sockaddr_in socket_address = {0};
    socket_address.sin_family = AF_INET;
    socket_address.sin_port = htons(port);
    
    if (bind(socket, (struct sockaddr *)&socket_address, sizeof(socket_address)) == -1) {
        perror("Failed to bind the socket");
        close(socket);
        exit(EXIT_FAILURE);
    }
}

void listen_socket(int socket, int queue_len) {
    if (listen(socket, queue_len) == -1) {
        perror("Failed to listen the socket");
        close(socket);
        exit(EXIT_FAILURE);
    }
}

int accept_socket(int this_socket) {
    struct sockaddr_in accepting_socket_address = {0};
    socklen_t accepting_socket_address_len = sizeof(accepting_socket_address);

    int accepted_socket = accept(this_socket, (struct sockaddr *)&accepting_socket_address, &accepting_socket_address_len);
    if (accepted_socket == -1) {
        perror("Failed to accept the socket");
        close(this_socket);
        exit(EXIT_FAILURE);
    }
    
    return accepted_socket;
}

void connect_socket(int socket, t_address address) {
    struct sockaddr_in socket_address = {0};
    socket_address.sin_family = AF_INET;
    socket_address.sin_addr.s_addr = inet_addr(address.ip);
    socket_address.sin_port = htons(address.port);

    if (connect(socket, (struct sockaddr *)&socket_address, sizeof(socket_address)) != 0) {
		perror("Failed to connect the socket");
        close(socket);
		exit(EXIT_FAILURE);
	}
}

int create_and_connect_socket(t_address address) {
    int socket = create_socket();
    connect_socket(socket, address);
    return socket;
}

