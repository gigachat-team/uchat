#include "gui.h"

void on_message_delete_clicked(GtkButton *b, gpointer user_data) {
    t_message_data *data = (t_message_data *)user_data;

    printf("%u\n", data->message_id);
    list_t *message_updates_list = rq_delete_message_and_get_message_updates(&data->chat_data->gui_data.server_address, data->message_id, data->chat_data->chat.id, data->chat_data->messages);

    gui_update_messages_list(data->chat_data->gui_data.builder, data->chat_data->messages, message_updates_list, NULL, data->chat_data);
    close_window(data->chat_data->gui_data.builder, "message_settings");

    list_destroy(message_updates_list);

    (void)b;
}

gboolean on_close_message_settings(GtkWidget *widget, GdkEventFocus *event, gpointer user_data) {

    t_message_data *data = (t_message_data *)user_data;
    close_window(data->chat_data->gui_data.builder, "message_settings");

    (void)widget;
    (void)event;

    return FALSE;
}

gboolean on_open_message_settings_clicked(GtkWidget *widget, GdkEventButton *event, gpointer user_data) {
    if (event->button != GDK_BUTTON_SECONDARY) return TRUE;

    t_message_data *data = (t_message_data *)user_data;
    open_window(data->chat_data->gui_data.builder, "message_settings");

    GtkWidget *message_settings = get_widget(data->chat_data->gui_data.builder, "message_settings");
    GtkWidget *delete_message_button = get_widget(data->chat_data->gui_data.builder, "delete_message_button");

    g_signal_handlers_destroy(message_settings);
    g_signal_handlers_destroy(delete_message_button);
    g_signal_connect(message_settings, "focus-out-event", G_CALLBACK(on_close_message_settings), user_data);
    g_signal_connect(delete_message_button, "clicked", G_CALLBACK(on_message_delete_clicked), user_data);

    (void)widget;
    return TRUE;
}

