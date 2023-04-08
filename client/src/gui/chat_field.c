#include "../../client.h"

void send_message(GtkEntry *entry, gpointer user_data)
{
    t_chat_data data = CHAT_DATA(user_data);

    // printf("%s\n", (gchar *)gtk_entry_get_text(GTK_ENTRY(entry)));

    char *message_text = (char *)gtk_entry_get_text(GTK_ENTRY(entry));
    send_message_in_server(data.gui_data.server_address, data.gui_data.user_id, data.chat.id, message_text);
    (void)entry;
    (void)message_text;
    (void)data;
}

void open_chat(GtkButton *bconfirm, gpointer user_data)
{
    t_chat_data data = CHAT_DATA(user_data);

    write_label_text(data.gui_data.builder, "chat_name", data.chat.name);
    // handle_chatting(data.gui_data.server_address, data.gui_data.user_id, 0);

    GtkWidget *message_field = GTK_WIDGET(gtk_builder_get_object(data.gui_data.builder, "message_field"));
    g_signal_connect(message_field, "activate", G_CALLBACK(send_message), user_data);

    (void)bconfirm;
}

void create_chat_message()
{
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
