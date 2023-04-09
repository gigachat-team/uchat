#include "../utils.h"

int create_socket() {
    int created_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (created_socket == -1) {
        perror("Failed to create a socket");
        exit(EXIT_FAILURE);
    }

    return created_socket;
}

void bind_socket(int socket, uint16_t port) {
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
    int accepted_socket = accept(this_socket, NULL, NULL);
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
        close(socket);
	}
}

int create_and_connect_socket(t_address address) {
    int socket = create_socket();
    connect_socket(socket, address);
    return socket;
}
