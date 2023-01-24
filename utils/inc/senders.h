#pragma once

#include "base_includes.h"
#include "socket.h"

void send_unsigned_char(int socket, unsigned char character);
void send_unsigned_short(int socket, uint16_t number);
void send_unsigned_int(int socket, uint32_t number);

