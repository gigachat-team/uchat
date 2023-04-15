#pragma once

#include "client_receivers.h"

typedef enum e_authentication_mode {
    REGISTER_MODE = REGISTER,
    LOGIN_MODE = LOGIN
} t_authentication_mode;

t_state_code rq_authenticate_user(t_address server_address, char *login, char *password, t_authentication_mode authentication_mode, uint *user_id);
/**
 * @return The id of created chat
*/
id_t rq_create_chat(t_address server_address, char *chat_name, id_t owner_id);
t_chat *rq_get_chats_i_am_in(t_address server_address, id_t user_id, size_t *chats_count);
t_state_code rq_add_new_member(t_address server_address, t_new_chat_member_data new_chat_member_data);
t_state_code rq_send_text_message(t_address server_address, id_t user_id, id_t chat_id, char *data);
t_list_with_size rq_get_messages_in_chat(t_address server_address, id_t chat_id);
t_list_with_size rq_send_message_and_get_messages_updates(t_address server_address, id_t user_id, id_t chat_id, char *message, t_list_with_size *messages_list);
t_list_with_size rq_delete_message_and_get_message_updates(t_address *server_address, id_t message_id, id_t chat_id, t_list_with_size *messages_list);
t_list_with_size rq_get_message_updates(t_address server_address, id_t chat_id, t_list_with_size *messages_list);
t_user *rq_get_chat_members(t_address server_address, id_t chat_id, uint32_t *members_count);
t_state_code rq_remove_member_from_chat(t_address server_address, id_t user_id, id_t chat_id);
