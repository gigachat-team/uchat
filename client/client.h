#pragma once

#include "../utils/utils.h"

typedef struct s_authentication_data {
    char *login;
    char *password;
} t_authentication_data;

typedef struct s_chat_data {
    char *name;
    char **member_logins;
} t_chat_data;

typedef enum e_authentication_mode {
    REGISTER_MODE = REGISTER,
    LOGIN_MODE = LOGIN
} t_authentication_mode;

t_state_code authenticate_user(t_authentication_data authentication_data, t_authentication_mode authentication_mode, t_address server_address);
t_state_code create_chat(t_chat_data chat_data, t_address server_address);

t_authentication_data get_authentication_data();
t_chat_data get_chat_data();
void free_authentication_data(t_authentication_data authentication_data);
void free_chat_data(t_chat_data chat_data);

