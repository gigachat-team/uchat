#include "../utils.h"

void send_byte(int socket, uint8_t byte) {
    send(socket, &byte, sizeof(byte), 0);
}

void send_uint16(int socket, uint16_t number) {
    uint16_t converted_number = htons(number);
    send(socket, &converted_number, sizeof(converted_number), 0);
}

void send_uint32(int socket, uint32_t number) {
    uint32_t converted_number = htonl(number);
    send(socket, &converted_number, sizeof(converted_number), 0);
}
