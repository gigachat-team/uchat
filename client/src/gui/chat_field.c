#include "../../client.h"

void create_chat_message(t_gui_data data, char *message_text) {
    GtkWidget *message = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
    GtkWidget *message_label = gtk_label_new((gchar *)message_text);
    GtkWidget *user_icon = get_image_from_path("client/message_icon.jpeg", 45, 45);

    gtk_label_set_line_wrap(GTK_LABEL(message_label), TRUE);
    gtk_label_set_line_wrap_mode(GTK_LABEL(message_label), PANGO_WRAP_CHAR);
    gtk_widget_set_valign(user_icon, GTK_ALIGN_END); // Align to the bottom vertically within the box

    gtk_box_pack_start(GTK_BOX(message), GTK_WIDGET(user_icon), false, false, 0);
    gtk_box_pack_start(GTK_BOX(message), message_label, false, false, 5);
    add_to_box_start(data.builder, message, "chat_field", 10);

    gtk_widget_show_all(message);
}

void send_message(GtkEntry *entry, gpointer user_data) {
    t_chat_data data = CHAT_DATA(user_data);
    char *message_text = (char *)gtk_entry_get_text(GTK_ENTRY(entry));

    send_message_in_server(data.gui_data.server_address, data.gui_data.user_id, data.chat.id, message_text);
    create_chat_message(data.gui_data, message_text);
}

void load_messages(t_chat_data data) {
    size_t messages_count = 0;
    t_user_message *messages = rq_get_messages_in_chat(data.gui_data.server_address, data.chat.id, &messages_count);

    for (size_t i = 0; i < messages_count; i++) {
        create_chat_message(data.gui_data, messages[i].data);
    }

    free_user_messages(messages, messages_count);
}

void open_chat(GtkButton *bconfirm, gpointer user_data) {
    t_chat_data data = CHAT_DATA(user_data);
    GtkWidget *message_field = GTK_WIDGET(gtk_builder_get_object(data.gui_data.builder, "message_field"));

    clear_container(data.gui_data.builder, "chat_field");
    write_label_text(data.gui_data.builder, "chat_name", data.chat.name);
    load_messages(data);

    g_signal_handlers_destroy(message_field);
    g_signal_connect(message_field, "activate", G_CALLBACK(send_message), user_data);

    (void)bconfirm;
}

// Memmory leak:)
t_chat_data *create_chat_data(t_chat *chat, t_gui_data gui_data) {
    t_chat_data *chat_data = malloc(sizeof(t_chat_data));

    chat_data->gui_data = gui_data;
    chat_data->chat.name = strdup(chat->name);
    chat_data->chat.id = chat->id;

    return chat_data;
}
