#pragma once

#include "../utils/utils.h"

typedef struct s_authentication_data {
    char *login;
    char *password;
} t_authentication_data;

typedef enum e_authentication_mode {
    REGISTER_MODE = REGISTER,
    LOGIN_MODE = LOGIN
} t_authentication_mode;

void init_authentication(char *server_ip, int server_port);
t_state_code authenticate_user(t_authentication_data authentication_data, t_authentication_mode authentication_mode);

t_authentication_data get_authentication_data();
void free_authentication_data(t_authentication_data authentication_data);
