#pragma once

#define _GNU_SOURCE
#include "styles.h"
#include "socket.h"
#include "gui_utils.h"
#include "request_senders.h"

#define UPDATE_INTERVAL 5000
#define MESSAGES_LIST_UPDATE_INTERVAL 2000

#define MIN_LOGIN_LENGTH 4
#define MIN_PASSWORD_LENGTH 5

#define CANVAS_ID "canvas"
#define CREATE_ROOM_ID "create_room"
#define NEW_LOGIN_ENTRY_ID "new_login_entry"
#define CHAT_NAME_LABEL_ID "chat_name"
#define LOGIN_ENTRY_ID "login_entry"
#define PASSWORD_ENTRY_ID "password_entry"
#define NEW_PASSWORD_ENTRY_ID "new_password_entry"
#define NEW_CHAT_NAME_ENTRY_ID "new_chat_name_entry"
#define NEW_PASSWORD_AGAIN_ENTRY_ID "new_password_again_entry"

#define ERROR_MESSAGE_LOGIN_LABEL_ID "error_message_login_label"
#define ERROR_MESSAGE_REGISTRATION_LABEL_ID "error_message_registration_label"
#define CONNECTING_LABEL_ID "connecting_label"

#define CHAT_SETTINGS_BUTTON_ID "open_chat_settings_window"

#define  AUTHENTICATION_LABEL_ID "authentication_label"

//Windows
#define CHAT_CREATE_ROOM_ID "create_room"
#define MESSENGER_WINDOW_ID "messenger_window"
#define CREATE_ROOM_PARENT_ID "create_room_parent"
#define CHAT_LISTS_WINDOW_ID "chats_list_container"
#define CREATE_CHAT_WINDOW_ID "create_chat_window"
#define UPPER_CANVAS_WINDOW_ID "upper_canvas_window"
#define CHAT_SETTINGS_WINDOW_ID "chat_settings_window"
#define AUTHENTICATION_WINDOW_ID "authentication_window"
#define NEW_MESSAGE_ENTRY_PARENT_ID "new_message_entry_parent"

//Conteners
#define NEW_MESSAGE_ENTRY_ID "new_message_entry"
#define CHATS_LIST_CONTAINER_ID "chats_list_container"
#define CHAT_FIELD_CONTENER_ID "chat_field"

#define GROUP_SETTINGS_BOX "group_settings_box"
#define CONNECTING_BOX_ID "connecting_box"

#define LAST_LOADING_MESSAGES_COUNT 30

extern GtkBuilder *Builder;
extern t_address *ServerAddress;
extern t_user *ThisUser;
extern list_t *LoadedMessagesList;
extern t_chat *SelectedChat;

void gui_update_messages_list(list_t *message_updates_list, char *sended_message);

void on_chat_clicked(GtkButton *b, gpointer user_data);
void on_send_message_clicked(GtkEntry *entry);
void on_open_chat_settings_clicked(GtkButton *b, gpointer user_data);
void on_leave_from_chat_clicked(GtkButton *b, gpointer user_data);
void on_add_chat_member_clicked(GtkButton *b, gpointer user_data);
void on_remove_chat_member_clicked(GtkButton *b, gpointer user_data);
gboolean on_open_message_settings_clicked(GtkWidget *widget, GdkEventButton *event, gpointer user_data);

void open_messenger_window();

void gui_render_chats_list();
