#pragma once

#define _GNU_SOURCE
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <netdb.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include "list.h"

#define MIN_LOGIN_LENGTH 4
#define MIN_PASSWORD_LENGTH 5

#define MAX_LOGIN_LENGTH 40
#define MAX_PASSWORD_LENGTH 50
#define MAX_CHAT_NAME_LENGTH 30

typedef struct s_new_chat_member_data {
    id_t chat_id;
    char *member_login;
} t_new_chat_member_data;

typedef struct s_chat_description {
    id_t id;
    char *name;
} t_chat;

typedef struct s_user {
    id_t id;
    char *login;
} t_user;

typedef enum e_request {
    LOGIN, // -> login -> password
    REGISTER, // -> login -> password
    CREATE_CHAT, // -> chat_name -> user_id
    ADD_MEMBER_TO_CHAT, // -> chat_id -> member_login
    GET_CHATS_I_AM_IN, // -> user_id
    SEND_TEXT_MESSAGE, // -> user_id -> chat_id -> text_message
    GET_MESSAGES_IN_CHAT,
    SEND_MESSAGE_AND_GET_MESSAGE_UPDATES,
    DELETE_MESSAGE_AND_GET_MESSAGE_UPDATES,
    GET_MESSAGE_UPDATES,
    REMOVE_USER_FROM_CHAT,
    GET_CHAT_MEMBERS
} t_request;

typedef enum e_state_code {
    NONE,

    CONNECTION_REFUSED,

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

void send_byte(int socket, uint8_t byte);
void send_uint16(int socket, uint16_t number);
void send_uint32(int socket, uint32_t number);

void free_chat(t_chat chat);
void free_chats(t_chat *chats, size_t length);
void free_new_chat_member_data(t_new_chat_member_data new_chat_member_data);
void free_user(t_user user);
void free_users(t_user *users, size_t users_count);
void free_users_list(list_t *users_list);
