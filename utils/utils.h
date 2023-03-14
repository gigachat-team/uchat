#pragma once 

#define _GNU_SOURCE
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <netdb.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <errno.h>
#include "../resources/libraries/libmx/inc/libmx.h"

/** For daemon**/
#include <syslog.h>
#include <signal.h>

#define MIN_LOGIN_LENGTH 4
#define MIN_PASSWORD_LENGTH 5

#define MAX_LOGIN_LENGTH 40
#define MAX_PASSWORD_LENGTH 50
#define MAX_CHAT_NAME_LENGTH 30

#define DEFAULT_TIME_FORMAT "%4Y-%2m-%2d %2H:%2M:%2S"
#define DEFAULT_TIME_FORMAT_LEN 20

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
    id_t owner_id;
} t_chat_creation_data;

typedef struct s_new_chat_member_data {
    id_t chat_id;
    char *member_login;
} t_new_chat_member_data;

typedef struct s_chat_description {
    id_t id;
    char *name;
} t_chat;

typedef struct s_text_message_data {
    id_t user_id;
    id_t chat_id;
    char *text;
} t_text_message_data;

typedef struct s_user {
    id_t id;
    char *login;
} t_user;

typedef struct s_package {
    struct iovec *const buffer;
    const size_t size;
    size_t filled_size;
} t_package;
t_package create_package(size_t size);
void free_package(t_package package);
void pack_byte(uint8_t byte, t_package *package);
void pack_uint16(uint16_t number, t_package *package);
void pack_uint32(uint32_t number, t_package *package);
void pack_bytes(char *bytes, t_package *package);
void send_package(int socket, t_package package);
void send_and_free_package(int socket, t_package package);

typedef enum e_request {
    LOGIN, // -> login -> password
    REGISTER, // -> login -> password
    CREATE_CHAT, // -> chat_name -> user_id
    ADD_MEMBER_TO_CHAT, // -> chat_id -> member_login
    GET_CHATS_I_AM_IN, // -> user_id
    SEND_TEXT_MESSAGE, // -> user_id -> chat_id -> text_message
    GET_LAST_MESSAGES,
    REMOVE_USER_FROM_CHAT,
    GET_CHAT_MEMBERS
} t_request;

typedef enum e_state_code {
    NONE,

    SUCCESSFULLY_READ,
    SUCCESSFUL_REGISTRATION,
    SUCCESSFUL_LOGIN,
    USER_SUCCESSFULLY_ADDED_TO_CHAT,
    TEXT_MESSAGE_SENT_SUCCESSFULLY,
    USER_REMOVED_FROM_CHAT_SUCCESSFULLY,
    
    SUCH_LOGIN_ALREADY_EXISTS,
    SUCH_LOGIN_DOES_NOT_EXIST,
    WRONG_PASSWORD,
    SUCH_USER_IS_ALREADY_IN_CHAT
} t_state_code;

/**
 * @brief Reads LENGTH bytes into BUFFER from SOCKET. This function is best used
 * to read 2 or more bytes.
 * @return 0 for success; -1 for errors; if returns a positive number, this
 * number is number of bytes left to read.
*/
int receive(int socket, char *buffer, size_t length);
/**
 * @brief Reads 1 byte from SOCKET. On errors, sets the erno variable to
 * ECONNABORTED.
 * @return Read unsigned char.
*/
uint8_t receive_byte(int socket);
/**
 * @brief Reads 2 bytes from SOCKET. On errors, sets the erno variable to
 * ECONNABORTED.
 * @return Read unsigned short.
*/
uint16_t receive_uint16(int socket);
/**
 * @brief Reads 4 bytes from SOCKET. On errors, sets the erno variable to
 * ECONNABORTED.
 * @return Read unsigned int.
*/
uint32_t receive_uint32(int socket);
/**
 * @brief Reads string from SOCKET. On errors, sets the errno variable to
 * ECONNABORTED. Reading format: int -> string. First, the size of the string
 * is read, and then the string itself.
 * @return Pointer to allocated string.
*/
char *receive_bytes(int socket);

void send_byte(int socket, uint8_t byte);
void send_uint16(int socket, uint16_t number);
void send_uint32(int socket, uint32_t number);

pthread_t create_default_thread(void *(*func)(void *), void *arg);
void create_detached_thread(void *(*func)(void *), void *arg);
void join_thread(pthread_t thread, void **thread_return);
void cancel_thread(pthread_t thread);

int create_socket();
void bind_socket(int socket, uint16_t port);
void listen_socket(int socket, int queue_len);
int accept_socket(int this_socket);
void connect_socket(int socket, t_address address);
int create_and_connect_socket(t_address address);

void free_authentication_data(t_authentication_data authentication_data);
void free_chat_creation_data(t_chat_creation_data chat_creation_data);
void free_chat(t_chat chat);
void free_chats(t_chat *chats, size_t length);
void free_new_chat_member_data(t_new_chat_member_data new_chat_member_data);
void free_text_message_data(t_text_message_data text_message_data);
void free_user(t_user user);
void free_users(t_user *users, size_t users_count);

struct tm str_to_tm(char *datetime_str, char *datetime_format);
struct tm utc_to_localtime(struct tm utc);
struct tm utc_str_to_localtime_tm(char *utc_str, char *datetime_format);

