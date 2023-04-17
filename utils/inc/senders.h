#pragma once

#include <sys/socket.h>
#include <netinet/in.h>

void send_byte(int socket, uint8_t byte);
void send_uint16(int socket, uint16_t number);
void send_uint32(int socket, uint32_t number);
