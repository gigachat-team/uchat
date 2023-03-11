#include "../utils.h"

int receive(int socket, char *buffer, size_t length) {
    int number_of_left_bytes = length;
    while (number_of_left_bytes > 0) {
        int received_bytes_count = recv(socket, buffer, number_of_left_bytes, 0);
        if (received_bytes_count < 0) {
            if (errno == EINTR) {
                continue;
            }
            return -1;
        }
        if (received_bytes_count == 0) {
            return length - number_of_left_bytes;
        }
        buffer += received_bytes_count;
        number_of_left_bytes -= received_bytes_count;
    }
    return 0;
}

uint8_t receive_byte(int socket) {
    uint8_t received_byte;
    int byte_size = sizeof(received_byte);
    if (recv(socket, &received_byte, byte_size, 0) != byte_size) {
        errno = ECONNABORTED;
        return 0;
    }
    return received_byte;
}

uint16_t receive_uint16(int socket) {
    uint16_t received_number;
    int number_size = sizeof(received_number);
    if (receive(socket, (char *)&received_number, number_size) != 0) {
        errno = ECONNABORTED;
        return 0;
    }
    return ntohs(received_number);
}

uint32_t receive_uint32(int socket) {
    uint32_t received_number;
    int number_size = sizeof(received_number);
    if (receive(socket, (char *)&received_number, number_size) != 0) {
        errno = ECONNABORTED;
        return 0;
    }
    return ntohl(received_number);
}

char *receive_bytes(int socket) {
    int string_len = receive_uint32(socket);
    if (errno == ECONNABORTED) {
        return NULL;
    }
    char *string = mx_strnew(string_len);

    if (receive(socket, string, string_len) != 0) {
        free(string);
        errno = ECONNABORTED;
        return NULL;
    }

    return string;
}

