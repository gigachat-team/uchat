#include "../../client.h"

#pragma region BUTTON_EVENTS

void on_register_button_clicked(GtkButton *b, gpointer user_data) {
    t_gui_data *gui_data = (t_gui_data *)user_data;
    gui_register(gui_data->builder, &gui_data->server_address, &gui_data->user_id);
    (void)b;
}

void on_login_button_clicked(GtkButton *b, gpointer user_data) {
    t_gui_data *gui_data = (t_gui_data *)user_data;
    gui_login(gui_data->builder, &gui_data->server_address, &gui_data->user_id);
    (void)b;
}

void on_open_chat_creator_button_clicked(GtkButton *b, gpointer user_data) {
    t_gui_data *gui_data = (t_gui_data *)user_data;
    open_window(gui_data->builder, CREATE_CHAT_WINDOW_ID);
    (void)b;
}

void on_close_chat_creator_button_clicked(GtkButton *b, gpointer user_data) {
    t_gui_data *gui_data = (t_gui_data *)user_data;
    close_window(gui_data->builder, CREATE_CHAT_WINDOW_ID);
    (void)b;
}

void on_create_chat_button_clicked(GtkButton *b, gpointer user_data) {
    t_gui_data *gui_data = (t_gui_data *)user_data;
    gui_create_chat(gui_data->builder, &gui_data->server_address, gui_data->user_id);
    (void)b;
}

void on_chat_clicked(GtkButton *b, gpointer user_data) {
    t_chat_data *chat_data = (t_chat_data *)user_data;
    gui_open_chat(chat_data);
    (void)b;
}

void on_open_chat_settings_clicked(GtkButton *b, gpointer user_data) {
    t_chat_data *chat_data = (t_chat_data *)user_data;
    open_window(chat_data->gui_data.builder, CHAT_SETTINGS_WINDOW_ID);
    gui_init_chat_settings_window(chat_data);
    (void)b;
}

void on_close_chat_settings_clicked(GtkButton *b, gpointer user_data) {
    t_gui_data *gui_data = (t_gui_data *)user_data;
    close_window(gui_data->builder, CHAT_SETTINGS_WINDOW_ID);
    (void)b;
}

void on_leave_from_chat_clicked(GtkButton *b, gpointer user_data) {
    t_chat_data *chat_data = (t_chat_data *)user_data;
    close_window(chat_data->gui_data.builder, CHAT_SETTINGS_WINDOW_ID);
    gui_leave_from_chat(chat_data->gui_data.builder, &chat_data->gui_data.server_address, chat_data->gui_data.user_id, chat_data->chat.id);
    (void)b;
}

#pragma endregion BUTTON_EVENTS

void on_send_message_clicked(GtkEntry *entry, gpointer *user_data) {
    t_chat_data *chat_data = (t_chat_data *)user_data;
    char *message_text = (char *)gtk_entry_get_text(entry);
    gui_send_message(chat_data->gui_data.builder, &chat_data->gui_data.server_address, chat_data->gui_data.user_id, chat_data->chat.id, message_text, &chat_data->messages);
}
