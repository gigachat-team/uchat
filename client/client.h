#pragma once

#include "../utils/utils.h"
#include <gtk/gtk.h>

#define DEFAULT_CSS_FILE_PATH "resources/style.css"
#define GLADE_FILE_PATH "resources/markup.glade"

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

typedef enum e_authentication_mode {
    REGISTER_MODE = REGISTER,
    LOGIN_MODE = LOGIN
} t_authentication_mode;

typedef struct s_gui_data {
    GtkBuilder *builder;
    t_address server_address;
    uint user_id;
} t_gui_data;

typedef struct s_user_message {
    id_t message_id;
    id_t sender_id;
    char *sender_login;
    char *data;
    struct tm creation_date;
} t_user_message;

typedef struct s_chat_data {
    t_gui_data gui_data;
    t_chat chat;
    t_list_with_size messages;
} t_chat_data;

typedef struct s_user_messages_array {
    t_user_message *arr;
    size_t size;
} t_user_messages_array;
t_user_messages_array allocate_user_messages_array(size_t size);
void free_user_message(t_user_message message);
void free_user_messages(t_user_message *messages, size_t length);
void free_user_messages_list(t_list_with_size *messages_list);

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

void write_label_text(GtkBuilder *builder, char *label_name, char *text);
void open_window(GtkBuilder *builder, char *window_name);
void close_window(GtkBuilder *builder, char *window_name);
void exit_app();

#pragma endregion GUIUtils

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
t_user *rq_get_chat_members(t_address server_address, id_t chat_id, uint32_t *members_count);
t_state_code rq_remove_member_from_chat(t_address server_address, id_t user_id, id_t chat_id);

// Data Input
t_new_chat_member_data get_new_chat_member_data(id_t chat_id);
int console_input_int(char *message);

void on_chat_clicked(GtkButton *b, gpointer user_data);
void on_send_message_clicked(GtkEntry *entry, gpointer *user_data);
void on_open_chat_settings_clicked(GtkButton *b, gpointer user_data);
void on_leave_from_chat_clicked(GtkButton *b, gpointer user_data);

void gui_login(GtkBuilder *gtk_builder, t_address *server_address, id_t *user_id);
void gui_register(GtkBuilder *gtk_builder, t_address *server_address, id_t *user_id);
void gui_send_message(GtkBuilder *builder, t_address *server_address, id_t user_id, id_t chat_id, char *message, t_list_with_size *messages_in_chat);
void gui_open_chat(t_chat_data *chat_data);
void gui_render_chats_list(GtkBuilder *gtk_builder, t_address *server_address, id_t user_id);
void gui_create_chat(GtkBuilder *builder, t_address *server_address, id_t user_id);

// Chat main messenger window
void gui_render_chats_list(GtkBuilder *gtk_builder, t_address *server_address, id_t user_id);

// Chat settings window
void gui_init_chat_settings_window(t_chat_data *chat_data);
void gui_leave_from_chat(GtkBuilder *builder, t_address *server_address, id_t user_id, id_t chat_id);

/**
 * @brief loads css to gtk. Should be called after gtk_init function
 * @param css_file_path path to a css file that will be included.
 * If variable is NULL, it'll use DEFAULT_CSS_FILE_PATH
*/
void load_css(char *css_file_path);
/**
 * @brief applies a style from a loaded css file to a widget.
 * If one of the pointers in NULL, then the function does nothing
 * @param widget in which a new style will be loaded
 * @param class css class-name for a style
*/
void apply_style_to_widget(GtkWidget *widget, const char *class);

/**
 * @brief applies style to a gtk widget by id in a .glade file.
 * If one of the pointers in NULL, then the function does nothing
 * @param gui_data contains the builder pointer from which the function
 * gets a widget.
 * @param markup_id is an id from .glade file
 * @param class css class-name for a style
*/
void get_widget_by_id_and_apply_style(t_gui_data gui_data, const char *markup_id, const char *class);
