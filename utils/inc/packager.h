#pragma once

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/uio.h>
#include <netinet/in.h>

typedef struct s_package {
    struct iovec *const buffer;
    const size_t size;
    size_t filled_size;
} t_package;

t_package create_package(size_t size);
void free_package(t_package *package);
void pack_byte(uint8_t byte, t_package *package);
void pack_uint16(uint16_t number, t_package *package);
void pack_uint32(uint32_t number, t_package *package);
void pack_bytes(char *bytes, t_package *package);
void send_package(int socket, t_package *package);
void send_and_free_package(int socket, t_package *package);
