#include "client_main.h"

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

static void load_messages(GtkBuilder *builder, t_address *server_address, id_t chat_id, list_t **messages_in_chat) {
    free_user_messages_list(*messages_in_chat);
    *messages_in_chat = rq_get_messages_in_chat(*server_address, chat_id);
    for (list_node_t *i = (*messages_in_chat)->head; i != NULL; i = i->next) {
        t_user_message *message = (t_user_message *)i->val;
        message->widget = create_and_show_message_widget(builder, message->data);
    }
}

static void gui_update_messages_list(GtkBuilder *builder, list_t *messages_list, list_t *message_updates_list, char *sended_message) {
    for (list_node_t *i = message_updates_list->head; i != NULL; i = i->next) {
        t_message_update *message_update = (t_message_update *)i->val;
        if (message_update->remove) {
            for (list_node_t *j = messages_list->head; j != NULL; j = j->next) {
                t_user_message *message_in_chat = (t_user_message *)j->val;
                if (message_update->message.message_id == message_in_chat->message_id) {
                    gtk_widget_hide(message_in_chat->widget);
                    gtk_widget_destroy(message_in_chat->widget);
                    free(message_in_chat);
                    list_remove(messages_list, j);
                    break;
                }
            }
        } else {
            if (i->next == NULL && sended_message != NULL) {
                message_update->message.widget = create_and_show_message_widget(builder, sended_message);
                free(message_update->message.data);
                message_update->message.data = strdup(sended_message);
            } else {
                message_update->message.widget = create_and_show_message_widget(builder, message_update->message.data);
            }
            list_rpush(messages_list, list_node_new(message_update));
        }
    }
}

void gui_send_message_and_update_messages_list(GtkBuilder *builder, t_address *server_address, id_t user_id, id_t chat_id, char *message, list_t *messages_in_chat) {
    list_t *message_updates_list = rq_send_message_and_get_messages_updates(*server_address, user_id, chat_id, message, messages_in_chat);
    gui_update_messages_list(builder, messages_in_chat, message_updates_list, message);
    list_destroy(message_updates_list);
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
