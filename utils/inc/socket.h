#pragma once

#include <netdb.h>
#include <fcntl.h>  
#include <sys/stat.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "base_includes.h"

int create_socket();
void bind_socket(int socket, unsigned int port);
void listen_socket(int socket, int queue_len);
int accept_socket(int this_socket);
void *read_socket(int socket, unsigned int max_read_bytes, int *read_bytes_count);
void connect_socket(int socket, char *ip, unsigned int port);

