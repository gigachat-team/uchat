#include "../utils.h"

unsigned char recieve_unsigned_char(int socket) {
    unsigned char recieved_character;
    read(socket, &recieved_character, sizeof(recieved_character));
    return recieved_character;
}

uint16_t recieve_unsigned_short(int socket) {
    uint16_t recieved_number;
    read(socket, &recieved_number, sizeof(recieved_number));
    return ntohs(recieved_number);
}

uint32_t recieve_unsigned_int(int socket) {
    uint32_t recieved_number;
    read(socket, &recieved_number, sizeof(recieved_number));
    return ntohl(recieved_number);
}

