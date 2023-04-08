#include "../../client.h"

void create_chat_message(t_gui_data data, char *message_text)
{
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

void send_message(GtkEntry *entry, gpointer user_data)
{
    t_chat_data data = CHAT_DATA(user_data);
    char *message_text = (char *)gtk_entry_get_text(GTK_ENTRY(entry));

    send_message_in_server(data.gui_data.server_address, data.gui_data.user_id, data.chat.id, message_text);
    create_chat_message(data.gui_data, message_text);
}

void open_chat(GtkButton *bconfirm, gpointer user_data)
{
    t_chat_data data = CHAT_DATA(user_data);
    GtkWidget *message_field = GTK_WIDGET(gtk_builder_get_object(data.gui_data.builder, "message_field"));

    write_label_text(data.gui_data.builder, "chat_name", data.chat.name);
    g_signal_connect(message_field, "activate", G_CALLBACK(send_message), user_data);

    (void)bconfirm;
}

// Memmory leak:)
t_chat_data *create_chat_data(t_chat *chat, t_gui_data gui_data)
{
    t_chat_data *chat_data = malloc(sizeof(t_chat_data));

    chat_data->gui_data = gui_data;
    chat_data->chat.name = strdup(chat->name);
    chat_data->chat.id = chat->id;

    return chat_data;
}
