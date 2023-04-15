#pragma once

#include "utils.h"
#include "styles.h"
#include "request_senders.h"

#define USAGE_MESSAGE "usage: ./uchat_server [port]\n"

#define NEW_LOGIN_ENTRY_ID "new_login_entry"
#define NEW_PASSWORD_ENTRY_ID "new_password_entry"
#define NEW_PASSWORD_AGAIN_ENTRY_ID "new_password_again_entry"
#define LOGIN_ENTRY_ID "login_entry"
#define PASSWORD_ENTRY_ID "password_entry"
#define NEW_CHAT_NAME_ENTRY_ID "new_chat_name_entry"
#define CHAT_NAME_LABEL_ID "chat_name"

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

typedef struct s_chat_data {
    t_gui_data gui_data;
    t_chat chat;
    t_list_with_size messages;
} t_chat_data;

// GUI-----------------------------------------------------------------------------
GtkWidget *get_widget(GtkBuilder *gtk_builder, char *name);
void set_label_text(GtkWidget *gtk_widget, char *text);
char *get_entry_text(GtkBuilder *builder, char *entry_name);

#pragma region GUIUtils

// x, y is new size image
GtkWidget *get_image_from_path(char *path, gint x, gint y);

// Add widget in box contener whith in builder
void add_to_box_start(GtkBuilder *builder, GtkWidget *new_element, gchar *box_name, gint padding);

// Destroy all widgets in container whith in builder
void clear_container(GtkBuilder *builder, char *contener_name);

// Scroll GrkSclolledWindow to botton position
void scroll_to_bottom(GtkBuilder *builder, char *name_scrolled_field);

void write_label_text(GtkBuilder *builder, char *label_name, char *text);
void open_window(GtkBuilder *builder, char *window_name);
void close_window(GtkBuilder *builder, char *window_name);
void exit_app();

#pragma endregion GUIUtils

// Data Input
t_new_chat_member_data get_new_chat_member_data(id_t chat_id);

void on_chat_clicked(GtkButton *b, gpointer user_data);
void on_send_message_clicked(GtkEntry *entry, gpointer *user_data);
void on_open_chat_settings_clicked(GtkButton *b, gpointer user_data);
void on_leave_from_chat_clicked(GtkButton *b, gpointer user_data);

void gui_login(GtkBuilder *gtk_builder, t_address *server_address, id_t *user_id);
void gui_register(GtkBuilder *gtk_builder, t_address *server_address, id_t *user_id);
void gui_send_message_and_update_messages_list(GtkBuilder *builder, t_address *server_address, id_t user_id, id_t chat_id, char *message, t_list_with_size *messages_in_chat);
void gui_open_chat(t_chat_data *chat_data);
void gui_render_chats_list(GtkBuilder *gtk_builder, t_address *server_address, id_t user_id);
void gui_create_chat(GtkBuilder *builder, t_address *server_address, id_t user_id);

// Chat main messenger window
void gui_render_chats_list(GtkBuilder *gtk_builder, t_address *server_address, id_t user_id);

// Chat settings window
void gui_init_chat_settings_window(t_chat_data *chat_data);
void gui_leave_from_chat(GtkBuilder *builder, t_address *server_address, id_t user_id, id_t chat_id);