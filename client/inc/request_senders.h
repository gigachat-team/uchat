#pragma once

#include "chat.h"
#include "user.h"
#include "request.h"
#include "packager.h"
#include "state_code.h"
#include "client_receivers.h"

typedef enum e_authentication_mode {
    REGISTER_MODE = REGISTER,
    LOGIN_MODE = LOGIN
} t_authentication_mode;

/**
 * @return The id of created chat
*/
id_t rq_create_chat(t_address *server_address, char *chat_name, id_t owner_id);
list_t *rq_get_chats_i_am_in(t_address *server_address, id_t user_id);
t_state_code rq_add_new_member(t_address *server_address, id_t chat_id, char *new_member_login);
t_state_code rq_send_text_message(t_address *server_address, id_t user_id, id_t chat_id, char *data);
list_t *rq_get_messages_in_chat(t_address *server_address, id_t chat_id);
list_t *rq_send_message_and_get_messages_updates(t_address *server_address, id_t user_id, id_t chat_id, char *message, list_t *messages_list);
list_t *rq_delete_message_and_get_message_updates(t_address *server_address, id_t message_id, id_t chat_id, list_t *messages_list);
list_t *rq_change_message_and_get_message_updates(t_address *server_address, id_t message_id, char *new_message_content, id_t chat_id, list_t *messages_list);
list_t *rq_get_message_updates(t_address *server_address, id_t chat_id, list_t *messages_list);
t_user *rq_get_chat_members(t_address *server_address, id_t chat_id, uint32_t *members_count);
t_state_code rq_remove_member_from_chat(t_address *server_address, id_t user_id, id_t chat_id);
t_state_code rq_authenticate_user(t_address *server_address, char *login, char *password, t_authentication_mode authentication_mode, id_t *user_id);
/**
 * @return LOGIN_SUCCESSFULLY_CHANGED on success; SUCH_LOGIN_ALREADY_EXISTS on failure;
 * CONNECTION_REFUSED on connection failure.
*/
t_state_code rq_change_login(t_address *server_address, id_t user_id, char *new_login);
/**
 * @return true on success; false on connection failure.
*/
bool rq_delete_account(t_address *server_address, id_t user_id);
