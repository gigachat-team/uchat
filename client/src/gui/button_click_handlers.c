#include "../../client.h"

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
