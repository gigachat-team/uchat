#include "../../client.h"

void on_register_button_clicked(GtkButton *bconfirm, gpointer user_data) {
    t_gui_data *gui_data = (t_gui_data *)user_data;
    gui_register(gui_data->builder, &gui_data->server_address, &gui_data->user_id);
    (void)bconfirm;
}

// void on_login_button_clicked(GtkButton *bconfirm, gpointer user_data) {

// }
