#pragma once

#include "base_includes.h"
#include "socket.h"

unsigned char recieve_unsigned_char(int socket);
uint16_t recieve_unsigned_short(int socket);
uint32_t recieve_unsigned_int(int socket);

