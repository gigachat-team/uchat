#include "gui.h"

void on_message_delete_clicked(GtkButton *b, gpointer user_data) {
    t_message *message = user_data;

    list_t *message_updates_list = rq_delete_message_and_get_message_updates(ServerAddress, message->message_id, SelectedChat->id, LoadedMessagesList);
    if (!message_updates_list) return;

    gui_update_messages_list(message_updates_list, NULL);
    close_window(Builder, "message_settings");

    free_messages_list(message_updates_list);

    (void)b;
}

gboolean on_update_message_entry(gpointer user_data) {
    GtkWidget *message_field = get_widget(Builder, NEW_MESSAGE_ENTRY_ID);

    g_signal_handlers_destroy(message_field);
    g_signal_connect(message_field, "activate", G_CALLBACK(on_send_message_clicked), NULL);

    (void)user_data;
    return FALSE;
}

void on_change_message(GtkEntry *entry, gpointer user_data) {
    t_message *message = user_data;

    char *message_text = (char *)gtk_entry_get_text(entry);

    list_t *message_updates_list = rq_change_message_and_get_message_updates(ServerAddress, message->message_id, message_text, SelectedChat->id, LoadedMessagesList);
    if (!message_updates_list) return;

    gui_update_messages_list(message_updates_list, NULL);

    g_timeout_add(100, on_update_message_entry, message);

    set_entry_text(Builder, NEW_MESSAGE_ENTRY_ID, "");

    free_messages_list(message_updates_list);
}

void on_message_edit_clicked(GtkButton *b, gpointer user_data) {
    t_message *message = user_data;

    GtkWidget *message_field = get_widget(Builder, NEW_MESSAGE_ENTRY_ID);

    g_signal_handlers_destroy(message_field);
    g_signal_connect(message_field, "activate", G_CALLBACK(on_change_message), user_data);

    close_window(Builder, "message_settings");

    set_entry_text(Builder, NEW_MESSAGE_ENTRY_ID, message->data);

    (void)b;
}

gboolean on_close_message_settings(GtkWidget *widget, GdkEventFocus *event) {
    close_window(Builder, "message_settings");

    (void)widget;
    (void)event;

    return FALSE;
}

static void on_reply_to_message(GtkEntry *entry, gpointer user_data) {
    t_message *message = user_data;
    char *message_text = (char *)gtk_entry_get_text(entry);

    list_t *message_updates_list = rq_reply_to_message_and_get_message_updates(ServerAddress, ThisUser->id, message->message_id, message_text, SelectedChat->id, LoadedMessagesList);
    if (toggle_widget_visibility(!message_updates_list, Builder, CONNECTING_BOX_ID)) return;

    gui_update_messages_list(message_updates_list, message_text);
    g_timeout_add(100, on_update_message_entry, message);
    set_entry_text(Builder, NEW_MESSAGE_ENTRY_ID, "");
    hide_widget(Builder, "reply_message_box");

    free_messages_list(message_updates_list);
}

void on_reply_to_message_button_clicked(GtkButton *b, gpointer user_data) {
    t_message *message = user_data;

    show_widget(Builder, "reply_message_box");

    GtkWidget *message_field = get_widget(Builder, NEW_MESSAGE_ENTRY_ID);
    set_label_text(get_widget(Builder, "reply_message_login_id"), message->sender_login);
    set_label_text(get_widget(Builder, "reply_message_text_id"), message->data);

    g_signal_handlers_destroy(message_field);
    g_signal_connect(message_field, "activate", G_CALLBACK(on_reply_to_message), user_data);

    close_window(Builder, "message_settings");

    (void)b;
}

gboolean on_open_message_settings_clicked(GtkWidget *widget, GdkEventButton *event, gpointer user_data) {
    if (event->button != GDK_BUTTON_SECONDARY) return TRUE;

    t_message *message = user_data;


    GtkWidget *message_settings = get_widget(Builder, "message_settings");
    GtkWidget *delete_message_button = get_widget(Builder, "delete_message_button");
    GtkWidget *edit_message_button = get_widget(Builder, "edit_message_button");
    GtkWidget *reply_to_message_button = get_widget(Builder, "reply_to_message_button");

    gtk_widget_show_all(message_settings);

    if (message->sender_id == ThisUser->id) {
        gtk_widget_show_all(delete_message_button);
        gtk_widget_show_all(edit_message_button);
    } else {
        gtk_widget_hide(delete_message_button);
        gtk_widget_hide(edit_message_button);
    }

    g_signal_handlers_destroy(message_settings);
    g_signal_handlers_destroy(delete_message_button);
    g_signal_handlers_destroy(edit_message_button);
    g_signal_handlers_destroy(reply_to_message_button);
    g_signal_connect(message_settings, "focus-out-event", G_CALLBACK(on_close_message_settings), user_data);
    g_signal_connect(delete_message_button, "clicked", G_CALLBACK(on_message_delete_clicked), user_data);
    g_signal_connect(edit_message_button, "clicked", G_CALLBACK(on_message_edit_clicked), user_data);
    g_signal_connect(reply_to_message_button, "clicked", G_CALLBACK(on_reply_to_message_button_clicked), user_data);


    (void)widget;
    return TRUE;
}
