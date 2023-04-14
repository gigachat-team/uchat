#include "../../client.h"

static GtkWidget *create_and_show_message_widget(GtkBuilder *builder, char *message_text) {
    GtkWidget *message = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
    GtkWidget *message_label = gtk_label_new((gchar *)message_text);
    GtkWidget *user_icon = get_image_from_path("client/message_icon.jpeg", 45, 45);

    gtk_label_set_line_wrap(GTK_LABEL(message_label), TRUE);
    gtk_label_set_line_wrap_mode(GTK_LABEL(message_label), PANGO_WRAP_CHAR);
    gtk_widget_set_valign(user_icon, GTK_ALIGN_END); // Align to the bottom vertically within the box

    gtk_box_pack_start(GTK_BOX(message), GTK_WIDGET(user_icon), false, false, 0);
    gtk_box_pack_start(GTK_BOX(message), message_label, false, false, 5);
    add_to_box_start(builder, message, CHAT_FIELD_CONTENER_ID, 10);

    gtk_widget_show_all(message);

    scroll_to_bottom(builder, "chat_scrolled_field");

    return message;
}

static void load_messages(GtkBuilder *builder, t_address *server_address, id_t chat_id, t_list_with_size *messages_in_chat) {
    free_user_messages_list(messages_in_chat);
    *messages_in_chat = rq_get_messages_in_chat(*server_address, chat_id);
    for (t_list *i = messages_in_chat->list; i != NULL; i = i->next) {
        t_user_message *message = (t_user_message *)i->data;
        message->widget = create_and_show_message_widget(builder, message->data);
    }
}

void gui_send_message(GtkBuilder *builder, t_address *server_address, id_t user_id, id_t chat_id, char *message, t_list_with_size *messages_in_chat) {
    t_list_with_size updated_messages = rq_send_message_and_get_messages_updates(*server_address, user_id, chat_id, message, messages_in_chat);
    for (t_list *i = updated_messages.list; i != NULL; i = i->next) {
        t_user_message *updated_message = (t_user_message *)i->data;
        if (i->next == NULL) {
            updated_message->widget = create_and_show_message_widget(builder, message);
            free(updated_message->data);
            updated_message->data = strdup(message);
        } else {
            updated_message->widget = create_and_show_message_widget(builder, updated_message->data);
        }
        mx_push_back(&messages_in_chat->list, updated_message);
        messages_in_chat->size++;
    }
    mx_clear_list(&updated_messages.list);
}

void gui_open_chat(t_chat_data *chat_data) {
    GtkWidget *message_field = get_widget(chat_data->gui_data.builder, "message_field");
    GtkWidget *chat_settings_window = get_widget(chat_data->gui_data.builder, CHAT_SETTINGS_BUTTON_ID);

    clear_container(chat_data->gui_data.builder, CHAT_FIELD_CONTENER_ID);
    write_label_text(chat_data->gui_data.builder, CHAT_NAME_LABEL_ID, chat_data->chat.name);
    load_messages(chat_data->gui_data.builder, &chat_data->gui_data.server_address, chat_data->chat.id, &chat_data->messages);

    g_signal_handlers_destroy(message_field);

    g_signal_connect(message_field, "activate", G_CALLBACK(on_send_message_clicked), chat_data);
    g_signal_connect(chat_settings_window, "clicked", G_CALLBACK(on_open_chat_settings_clicked), chat_data);
}
