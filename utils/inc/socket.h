#pragma once

#include "base_includes.h"

int create_socket();
void bind_socket(int socket, unsigned int port);
void listen_socket(int socket, int queue_len);
int accept_socket(int this_socket);
void *read_socket(int socket, unsigned int max_read_bytes, int *read_bytes_count);
void connect_socket(int socket, char *ip, unsigned int port);

