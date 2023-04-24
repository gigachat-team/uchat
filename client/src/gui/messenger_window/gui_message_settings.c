#include "gui.h"

// void on_message_delete_clicked(GtkButton *b, gpointer user_data) {
//     t_chat_data *chat_data = (t_chat_data *)user_data;

//     // chat_data->messages = rq_delete_message_and_get_message_updates()
//     load_messages(chat_data->gui_data.builder, &chat_data->gui_data.server_address, 
//     chat_data->chat.id, chat_data->messages, chat_data);

//     (void)chat_data;
// }

gboolean on_close_message_settings(GtkWidget *widget, GdkEventFocus *event, gpointer user_data) {

    GtkBuilder *builder = (GtkBuilder *)user_data;
    close_window(builder, "message_settings");

    (void)widget;
    (void)event;

    return FALSE;
}

gboolean on_open_message_settings_clicked(GtkWidget *widget, GdkEventButton *event, gpointer user_data) {
    if (event->button != GDK_BUTTON_SECONDARY) return TRUE;

    GtkBuilder *builder = (GtkBuilder *)user_data;
    open_window(builder, "message_settings");

    GtkWidget *message_settings = get_widget(builder, "message_settings");
    g_signal_connect(message_settings, "focus-out-event", G_CALLBACK(on_close_message_settings), builder);

    // GtkWidget *delete_message_button = get_widget(builder, "delete_message_button");

    // g_signal_handlers_destroy(delete_message_button);
    // g_signal_connect(delete_message_button, "clicked", G_CALLBACK(on_message_delete_clicked), chat_data);

    (void)widget;
    return TRUE;
}

