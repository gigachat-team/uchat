#pragma once

#include "../utils/utils.h"

typedef enum e_authentication_mode {
    REGISTER_MODE = REGISTER,
    LOGIN_MODE = LOGIN
} t_authentication_mode;

t_state_code send_authenticate_user_request(t_authentication_data authentication_data, t_authentication_mode authentication_mode, t_address server_address);
t_state_code send_create_chat_requests(t_chat_creation_data chat_data, t_address server_address);
t_state_code send_add_new_member_request(t_address server_address, t_new_chat_member_data new_chat_member_data);

t_authentication_data get_authentication_data();
t_chat_creation_data get_chat_creation_data(char *owner_login);
char *get_new_chat_member_login();

