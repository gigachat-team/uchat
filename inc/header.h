#pragma once 

#include <stdio.h>
#include <netdb.h>
#include <fcntl.h>  
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define BUFFER_SIZE 80
#define PORT 8080

#define SA struct sockaddr
