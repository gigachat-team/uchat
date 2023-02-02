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

uint8_t receive_unsigned_char(int socket) {
    uint8_t received_character;
    int character_size = sizeof(received_character);
    if (recv(socket, &received_character, character_size, 0) != character_size) {
        errno = ECONNABORTED;
        return 0;
    }
    return received_character;
}

uint16_t receive_unsigned_short(int socket) {
    uint16_t received_number;
    int number_size = sizeof(received_number);
    if (receive(socket, (char *)&received_number, number_size) != 0) {
        errno = ECONNABORTED;
        return 0;
    }
    return ntohs(received_number);
}

uint32_t receive_unsigned_int(int socket) {
    uint32_t received_number;
    int number_size = sizeof(received_number);
    if (receive(socket, (char *)&received_number, number_size) != 0) {
        errno = ECONNABORTED;
        return 0;
    }
    return ntohl(received_number);
}

char *receive_string(int socket) {
    int string_len = receive_unsigned_int(socket);
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

