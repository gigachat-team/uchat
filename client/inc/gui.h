#pragma once

#include "utils.h"
#include "styles.h"
#include "socket.h"
#include "gui_utils.h"
#include "request_senders.h"

#define UPDATE_INTERVAL 5000
#define MESSAGES_LIST_UPDATE_INTERVAL 2000

#define NEW_LOGIN_ENTRY_ID "new_login_entry"
#define NEW_PASSWORD_ENTRY_ID "new_password_entry"
#define NEW_PASSWORD_AGAIN_ENTRY_ID "new_password_again_entry"
#define LOGIN_ENTRY_ID "login_entry"
#define PASSWORD_ENTRY_ID "password_entry"
#define NEW_CHAT_NAME_ENTRY_ID "new_chat_name_entry"
#define CHAT_NAME_LABEL_ID "chat_name"
#define CREATE_ROOM_ID "create_room"

#define ERROR_MESSAGE_REGISTRATION_LABEL_ID "error_message_registration_label"
#define ERROR_MESSAGE_LOGIN_LABEL_ID "error_message_login_label"

#define CHAT_SETTINGS_BUTTON_ID "open_chat_settings_window"

//Windows
#define AUTHENTICATION_WINDOW_ID "authentication_window"
#define MESSENGER_WINDOW_ID "messenger_window"
#define CREATE_CHAT_WINDOW_ID "create_chat_window"
#define CHAT_SETTINGS_WINDOW_ID "chat_settings_window"

//Conteners
#define CHATS_LIST_CONTAINER_ID "chats_list_container"
#define CHAT_FIELD_CONTENER_ID "chat_field"

#define LAST_LOADING_MESSAGES_COUNT 30

typedef struct s_gui_data {
    GtkBuilder *builder;
    t_address server_address;
    uint user_id;
} t_gui_data;
t_gui_data create_gui_data(char *ip, in_port_t port);

typedef struct s_chat_data {
    t_gui_data gui_data;
    t_chat chat;
    list_t *messages;
} t_chat_data;
t_chat_data *create_chat_data_ptr(GtkBuilder *gtk_builder, t_address *server_address, id_t user_id, char *chat_name, id_t chat_id);

// Data Input
t_new_chat_member_data get_new_chat_member_data(id_t chat_id);

void on_chat_clicked(GtkButton *b, gpointer user_data);
void on_send_message_clicked(GtkEntry *entry, gpointer *user_data);
void on_open_chat_settings_clicked(GtkButton *b, gpointer user_data);
void on_leave_from_chat_clicked(GtkButton *b, gpointer user_data);
void on_add_chat_member_clicked(GtkButton *b, gpointer user_data);
void on_remove_chat_member_clicked(GtkButton *b, gpointer user_data);

void open_messenger_window(GtkBuilder *gtk_builder, t_gui_data *data);

void gui_render_chats_list(GtkBuilder *gtk_builder, t_address *server_address, id_t user_id);