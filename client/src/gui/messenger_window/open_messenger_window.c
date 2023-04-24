#include "gui.h"

gboolean chat_list_updater(gpointer user_data) {
    t_gui_data *gui_data = (t_gui_data *)user_data;

    gui_render_chats_list(&gui_data->server_address, gui_data->user_id);
    return TRUE;
}

void open_messenger_window(t_gui_data *data) {
    close_window(Builder, AUTHENTICATION_WINDOW_ID);
    open_window(Builder, MESSENGER_WINDOW_ID);
    apply_styles_for_messenger_window(Builder);
    gui_render_chats_list(&data->server_address, data->user_id);
    g_timeout_add(UPDATE_INTERVAL, chat_list_updater, data);

    hide_widget(Builder, "chat_area");
}
