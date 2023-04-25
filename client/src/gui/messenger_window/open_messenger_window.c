#include "gui.h"

gboolean chat_list_updater(gpointer user_data) {
    gui_render_chats_list();
    (void)user_data;
    return TRUE;
}

void open_messenger_window() {
    close_window(Builder, AUTHENTICATION_WINDOW_ID);
    open_window(Builder, MESSENGER_WINDOW_ID);
    apply_styles_for_messenger_window(Builder);
    gui_render_chats_list();
    g_timeout_add(UPDATE_INTERVAL, chat_list_updater, NULL);

    hide_widget(Builder, "chat_area");
}
