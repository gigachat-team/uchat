#include "../inc/socket.h"

int create_socket() {
    int created_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (created_socket == -1) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    return created_socket;
}

void bind_socket(int socket, unsigned int port) {
    struct sockaddr_in socket_address = {0};
    socket_address.sin_family = AF_INET;
    socket_address.sin_port = htons(port);
    
    if (bind(socket, (struct sockaddr *)&socket_address, sizeof(socket_address)) == -1) {
        perror("bind failed");
        close(socket);
        exit(EXIT_FAILURE);
    }
}

void listen_socket(int socket, int queue_len) {
    if (listen(socket, queue_len) == -1) {
        perror("listen failed");
        close(socket);
        exit(EXIT_FAILURE);
    }
}

int accept_socket(int this_socket) {
    struct sockaddr_in accepting_socket_address = {0};
    socklen_t accepting_socket_address_len = sizeof(accepting_socket_address);

    int accepted_socket = accept(this_socket, (struct sockaddr *)&accepting_socket_address, &accepting_socket_address_len);
    if (accepted_socket == -1) {
        perror("client_socket");
        close(this_socket);
        exit(EXIT_FAILURE);
    }
    
    return accepted_socket;
}

char *read_socket(int socket, unsigned int max_read_bytes, int *read_str_count) {
    char *read_bytes = malloc(max_read_bytes);
    *read_str_count = read(socket, read_bytes, max_read_bytes);
    if (*read_str_count == -1) {
        perror("read failed");
        close(socket);
        // need to close listening socket
        free(read_bytes);
        exit(EXIT_FAILURE);
    }
    read_bytes = realloc(read_bytes, *read_str_count);

    return read_bytes;
}

void connect_socket(int socket, char *ip, unsigned int port) {
    struct sockaddr_in socket_address = {0};
    socket_address.sin_family = AF_INET;
    socket_address.sin_addr.s_addr = inet_addr(ip);
    socket_address.sin_port = htons(port);

    if (connect(socket, (struct sockaddr *)&socket_address, sizeof(socket_address)) != 0) {
		perror("connect failed");
        close(socket);
		exit(EXIT_FAILURE);
	}
}

