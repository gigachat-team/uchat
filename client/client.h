#pragma once

#include "../utils/utils.h"

typedef enum e_authentication_mode {
    REGISTER_MODE = REGISTER,
    LOGIN_MODE = LOGIN
} t_authentication_mode;

t_state_code send_authenticate_user_request(t_address server_address, t_authentication_data authentication_data, t_authentication_mode authentication_mode);
t_state_code send_create_chat_request(t_address server_address, t_chat_creation_data chat_data);
t_state_code get_chats_i_am_in(t_address server_address, char *user_login, t_chat **chats_i_am_in, size_t *chats_i_am_in_length);
t_state_code send_add_new_member_request(t_address server_address, t_new_chat_member_data new_chat_member_data);

t_authentication_data get_authentication_data();
t_chat_creation_data get_chat_creation_data(char *owner_login);
t_new_chat_member_data get_new_chat_member_data();

t_chat receive_chat(int socket);

