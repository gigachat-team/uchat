#pragma once

#include "../utils/utils.h"
#include <gtk/gtk.h>

#define DEFAULT_CSS_FILE_PATH "./client/style/common.css"

#define LAST_LOADING_MESSAGES_COUNT 30
#define CHAT_DATA(data) (*(t_chat_data *)data)
#define GUI_DATA(data) (*(t_gui_data *)data)

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
} t_chat_data;

// GUI-----------------------------------------------------------------------------
char *get_entry_text(GtkBuilder *builder, char *entry_name);
void open_messenger_window(t_gui_data data);
void gui_init(int argc, char **argv);
void open_chat(GtkButton *bconfirm, gpointer user_data);
t_chat_data *create_chat_data(t_chat *chat, t_gui_data gui_data);

#pragma region GUIUtils

// x, y is new size image
GtkWidget *get_image_from_path(char *path, gint x, gint y);

// Add widget in box contener whith in builder
void add_to_box_start(GtkBuilder *builder, GtkWidget *new_element, gchar *box_name, gint padding);

void write_label_text(GtkBuilder *builder, char *label_name, char *text);
void open_window(GtkBuilder *builder, char *window_name);
void close_window(GtkBuilder *builder, char *window_name);
void exit_app();

#pragma endregion GUIUtils

// Ne otnositsa k GUI
void create_new_chat_in_server(t_address server_address, id_t user_id, char *chat_name);
void send_message_in_server(t_address server_address, id_t user_id, id_t chat_id, char *text_message);
void handle_chatting(t_address server_address, id_t user_id, id_t chat_id);

void handle_authenticated_user_commands(t_address server_address, id_t user_id);

t_state_code rq_authenticate_user(t_address server_address, t_authentication_data authentication_data, t_authentication_mode authentication_mode, uint *user_id);
/**
 * @return The id of created chat
*/
id_t rq_create_chat(t_address server_address, t_chat_creation_data chat_data);
t_chat *rq_get_chats_i_am_in(t_address server_address, id_t user_id, size_t *chats_count);
t_state_code rq_add_new_member(t_address server_address, t_new_chat_member_data new_chat_member_data);
t_state_code rq_send_text_message(t_address server_address, t_text_message_data text_message_data);
t_user_message *rq_get_messages_in_chat(t_address server_address, id_t chat_id, size_t *found_messages_count);
t_user *rq_get_chat_members(t_address server_address, id_t chat_id, uint32_t *members_count);
t_state_code rq_remove_member_from_chat(t_address server_address, id_t user_id, id_t chat_id);

// Data Input
t_authentication_data get_authentication_data(GtkWidget *enter_login, GtkWidget *enter_password);
t_chat_creation_data get_chat_creation_data(id_t owner_id, char *chat_name);
t_new_chat_member_data get_new_chat_member_data(id_t chat_id);
int console_input_int(char *message);

t_chat receive_chat(int socket);

void free_user_message(t_user_message message);
void free_user_messages(t_user_message *messages, size_t length);



/* ------- css.c ------- */

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
void apply_style_to_widget(GtkWidget *widget, char *class);

