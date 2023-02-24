#pragma once

#include "../utils/utils.h"
#include <gtk/gtk.h>

#define LAST_LOADING_MESSAGES_COUNT 30

typedef enum e_authentication_mode
{
    REGISTER_MODE = REGISTER,
    LOGIN_MODE = LOGIN
} t_authentication_mode;

typedef struct s_gui_data
{
    GtkBuilder *builder;

    t_address server_address;
    uint user_id;
} t_gui_data;

// GUI
void gui_init(int argc, char **argv);
void exit_app();

void handle_authenticated_user_commands(t_address server_address, int user_id);

t_state_code rq_authenticate_user(t_address server_address, t_authentication_data authentication_data, t_authentication_mode authentication_mode, uint *user_id);
t_state_code rq_create_chat(t_address server_address, t_chat_creation_data chat_data);
t_state_code rq_get_chats_i_am_in(t_address server_address, int user_id, t_chat **chats_i_am_in, size_t *chats_i_am_in_length);
t_state_code rq_add_new_member(t_address server_address, t_new_chat_member_data new_chat_member_data);
t_state_code rq_send_text_message(t_address server_address, t_text_message_data text_message_data);
t_user_message *rq_get_last_messages(t_address server_address, uint16_t messages_count, uint32_t chat_id, uint32_t *found_messages_count);

// Data Input
t_authentication_data get_authentication_data(GtkWidget *enter_login, GtkWidget *enter_password);
t_chat_creation_data get_chat_creation_data(int owner_id);
t_new_chat_member_data get_new_chat_member_data();
int get_chat_id();
t_text_message_data get_text_message_data(uint32_t user_id, uint32_t chat_id);

t_chat receive_chat(int socket);
