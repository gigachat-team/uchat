#include "gui.h"

void on_message_delete_clicked(GtkButton *b, gpointer user_data) {
    t_user_message *message = user_data;

    list_t *message_updates_list = rq_delete_message_and_get_message_updates(ServerAddress, message->message_id, SelectedChat->id, LoadedMessagesList);
    if (!message_updates_list) return;

    gui_update_messages_list(message_updates_list, NULL);
    close_window(Builder, "message_settings");

    list_destroy(message_updates_list);

    (void)b;
}

gboolean on_update_message_entry(gpointer user_data) {
    t_user_message *message = user_data;

    GtkWidget *message_field = get_widget(Builder, NEW_MESSAGE_ENTRY_ID);

    g_signal_handlers_destroy(message_field);
    g_signal_connect(message_field, "activate", G_CALLBACK(on_send_message_clicked), message);

    return FALSE;
}

void on_change_message(GtkEntry *entry, gpointer user_data) {
    t_user_message *message = user_data;

    char *message_text = (char *)gtk_entry_get_text(entry);

    list_t *message_updates_list = rq_change_message_and_get_message_updates(ServerAddress, message->message_id, message_text, SelectedChat->id, LoadedMessagesList);
    if (!message_updates_list) return;

    gui_update_messages_list(message_updates_list, NULL);

    g_timeout_add(100, on_update_message_entry, message);

    set_entry_text(Builder, NEW_MESSAGE_ENTRY_ID, "");

    list_destroy(message_updates_list);
}

void on_message_edit_clicked(GtkButton *b, gpointer user_data) {
    GtkWidget *message_field = get_widget(Builder, NEW_MESSAGE_ENTRY_ID);

    g_signal_handlers_destroy(message_field);
    g_signal_connect(message_field, "activate", G_CALLBACK(on_change_message), user_data);

    close_window(Builder, "message_settings");

    (void)b;
}

gboolean on_close_message_settings(GtkWidget *widget, GdkEventFocus *event) {
    close_window(Builder, "message_settings");

    (void)widget;
    (void)event;

    return FALSE;
}

gboolean on_open_message_settings_clicked(GtkWidget *widget, GdkEventButton *event, gpointer user_data) {
    if (event->button != GDK_BUTTON_SECONDARY) return TRUE;

    open_window(Builder, "message_settings");

    GtkWidget *message_settings = get_widget(Builder, "message_settings");
    GtkWidget *delete_message_button = get_widget(Builder, "delete_message_button");
    GtkWidget *edit_message_button = get_widget(Builder, "edit_message_button");

    g_signal_handlers_destroy(message_settings);
    g_signal_handlers_destroy(delete_message_button);
    g_signal_handlers_destroy(edit_message_button);
    g_signal_connect(message_settings, "focus-out-event", G_CALLBACK(on_close_message_settings), user_data);
    g_signal_connect(delete_message_button, "clicked", G_CALLBACK(on_message_delete_clicked), user_data);
    g_signal_connect(edit_message_button, "clicked", G_CALLBACK(on_message_edit_clicked), user_data);

    (void)widget;
    return TRUE;
}
