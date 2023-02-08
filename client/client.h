#pragma once

#include "../utils/utils.h"

#define LAST_LOADING_MESSAGES_COUNT 30

typedef enum e_authentication_mode {
    REGISTER_MODE = REGISTER,
    LOGIN_MODE = LOGIN
} t_authentication_mode;

t_state_code rq_authenticate_user(t_address server_address, t_authentication_data authentication_data, t_authentication_mode authentication_mode, uint *user_id);
t_state_code rq_create_chat(t_address server_address, t_chat_creation_data chat_data);
t_chat *rq_get_chats_i_am_in(t_address server_address, id_t user_id, size_t *chats_count);
t_state_code rq_add_new_member(t_address server_address, t_new_chat_member_data new_chat_member_data);
t_state_code rq_send_text_message(t_address server_address, t_text_message_data text_message_data);
t_user_message *rq_get_last_messages(t_address server_address, uint16_t messages_count, id_t chat_id, uint16_t *found_messages_count);

t_authentication_data get_authentication_data();
t_chat_creation_data get_chat_creation_data(id_t owner_id);
t_new_chat_member_data get_new_chat_member_data();
id_t get_chat_id();
t_text_message_data get_text_message_data(id_t user_id, id_t chat_id);

t_chat receive_chat(int socket);

