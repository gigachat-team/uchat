#include "../utils.h"

void send_unsigned_char(int socket, unsigned char character) {
    send(socket, &character, sizeof(character), 0);
}

void send_unsigned_short(int socket, uint16_t number) {
    uint16_t converted_number = htons(number);
    send(socket, &converted_number, sizeof(converted_number), 0);
}

void send_unsigned_int(int socket, uint32_t number) {
    uint32_t converted_number = htonl(number);
    send(socket, &converted_number, sizeof(converted_number), 0);
}
