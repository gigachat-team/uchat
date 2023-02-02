#include "../utils.h"

int recieve(int socket, char *buffer, size_t length) {
    int number_of_left_bytes = length;
    while (number_of_left_bytes > 0) {
        int recieved_bytes_count = recv(socket, buffer, number_of_left_bytes, 0);
        if (recieved_bytes_count < 0) {
            if (errno == EINTR) {
                continue;
            }
            return -1;
        }
        if (recieved_bytes_count == 0) {
            return length - number_of_left_bytes;
        }
        buffer += recieved_bytes_count;
        number_of_left_bytes -= recieved_bytes_count;
    }
    return 0;
}

uint8_t recieve_unsigned_char(int socket) {
    uint8_t recieved_character;
    int character_size = sizeof(recieved_character);
    if (recv(socket, &recieved_character, character_size, 0) != character_size) {
        errno = ECONNABORTED;
        return 0;
    }
    return recieved_character;
}

uint16_t recieve_unsigned_short(int socket) {
    uint16_t recieved_number;
    int number_size = sizeof(recieved_number);
    if (recieve(socket, (char *)&recieved_number, number_size) != number_size) {
        errno = ECONNABORTED;
        return 0;
    }
    return ntohs(recieved_number);
}

uint32_t recieve_unsigned_int(int socket) {
    uint32_t recieved_number;
    int number_size = sizeof(recieved_number);
    if (recieve(socket, (char *)&recieved_number, number_size) != number_size) {
        errno = ECONNABORTED;
        return 0;
    }
    return ntohl(recieved_number);
}

char *recieve_string(int socket, int max_string_length) {
    char *recieved_string = malloc(max_string_length);
    recv(socket, recieved_string, max_string_length, 0);
    char *returning_string = mx_strdup(recieved_string);
    free(recieved_string);
    return returning_string;
}

