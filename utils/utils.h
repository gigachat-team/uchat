#pragma once 

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <netdb.h>
#include <fcntl.h>  
#include <sys/stat.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <errno.h>
#include "../resources/libraries/libmx/inc/libmx.h"

#define MAX_LOGIN_LENGTH 40
#define MAX_PASSWORD_LENGTH 50
#define MAX_CHAT_NAME_LENGTH 30

typedef struct s_address {
    char *ip;
    in_port_t port;
} t_address;

typedef struct s_authentication_data {
    char *login;
    char *password;
} t_authentication_data;

typedef struct s_chat_creation_data {
    char *chat_name;
    char *owner_login;
} t_chat_creation_data;

typedef struct s_new_chat_member_data {
    int chat_id;
    char *member_login;
} t_new_chat_member_data;

typedef struct s_chat_description {
    int id;
    char *name;
} t_chat;

typedef enum e_request {
    LOGIN, // -> login -> password
    REGISTER, // -> login -> password
    CREATE_CHAT, // -> chat_name -> owner_login
    ADD_MEMBER_TO_CHAT, // -> chat_id -> member_login
    GET_CHATS_I_AM_IN // -> user_id
} t_request;

typedef enum e_state_code {
    NONE,

    SUCCESSFULLY_READ,
    SUCCESSFUL_REGISTRATION,
    SUCCESSFUL_LOGIN,
    CHAT_CREATED_SUCCESSFULLY,
    CHATS_ARRAY_TRENSFERRED_SUCCESSFULLY,
    USER_SUCCESSFULLY_ADDED_TO_CHAT,
    
    SUCH_LOGIN_ALREADY_EXISTS,
    SUCH_LOGIN_DOES_NOT_EXIST,
    WRONG_PASSWORD,
    SUCH_USER_IS_ALREADY_IN_CHAT,

    START_OF_CHATS_ARRAY,
    CONTINUATION_OF_CHATS_ARRAY,
    END_OF_CHATS_ARRAY
} t_state_code;

/**
 * @brief Reads LENGTH bytes into BUFFER from SOCKET. This function is best used
 * to read 2 or more bytes.
 * @return 0 for success; -1 for errors; if returns a positive number, this
 * number is number of bytes left to read.
*/
int receive(int socket, char *buffer, size_t length);
/**
 * @brief Reads unsigned char from SOCKET. On errors, sets the erno variable
 * to ECONNABORTED.
 * @return Read unsigned char.
*/
uint8_t receive_unsigned_char(int socket);
/**
 * @brief Reads unsigned short from SOCKET. On errors, sets the erno variable
 * to ECONNABORTED.
 * @return Read unsigned short.
*/
uint16_t receive_unsigned_short(int socket);
/**
 * @brief Reads unsigned int from SOCKET. On errors, sets the erno variable
 * to ECONNABORTED.
 * @return Read unsigned int.
*/
uint32_t receive_unsigned_int(int socket);
/**
 * @brief Reads string from SOCKET. On errors, sets the errno variable to
 * ECONNABORTED. Reading format: int -> string. First, the size of the string
 * is read, and then the string itself.
 * @return Pointer to allocated string.
*/
char *receive_string(int socket);

void send_unsigned_char(int socket, unsigned char character);
void send_unsigned_short(int socket, uint16_t number);
void send_unsigned_int(int socket, uint32_t number);
void send_string(int socket, char *string);

pthread_t create_default_thread(void *(*func)(void *), void *arg);
void create_detached_thread(void *(*func)(void *), void *arg);
void join_thread(pthread_t thread, void **thread_return);
void cancel_thread(pthread_t thread);

int create_socket();
void bind_socket(int socket, unsigned int port);
void listen_socket(int socket, int queue_len);
int accept_socket(int this_socket);
void connect_socket(int socket, t_address address);
int create_and_connect_socket(t_address address);

void free_authentication_data(t_authentication_data authentication_data);
void free_chat_creation_data(t_chat_creation_data chat_creation_data);
void free_chat(t_chat chat);
void free_chats(t_chat *chats, size_t length);
void free_new_chat_member_data(t_new_chat_member_data new_chat_member_data);

