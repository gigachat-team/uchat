#pragma once

#define _GNU_SOURCE
#include <poll.h>
#include <time.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>

typedef struct s_address {
    char *ip;
    in_port_t port;
} t_address;

int create_socket();
void bind_socket(int socket, uint16_t port);
void listen_socket(int socket, int queue_len);
int accept_socket(int this_socket);
void connect_socket(int socket, t_address address);
int create_and_connect_socket(t_address address);
