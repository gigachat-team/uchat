#include "gui.h"

static gboolean scroll_to_bottom_message_list(gpointer user_data) {
    GtkBuilder *builder = user_data;
    scroll_to_bottom(builder, "chat_scrolled_field");
    return FALSE;
}

static GtkWidget *create_and_show_message_widget(char *message_text, time_t datetime, GtkWidget **message_label, t_chat_data *chat_data, id_t message_id) {
    GtkWidget *message = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
    *message_label = gtk_label_new((gchar *)message_text);
    GtkWidget *user_icon = get_image_from_path("resources/img/message_icon.jpeg", 45, 45);

    gtk_label_set_line_wrap(GTK_LABEL(*message_label), TRUE);
    gtk_label_set_line_wrap_mode(GTK_LABEL(*message_label), PANGO_WRAP_CHAR);
    gtk_widget_set_valign(user_icon, GTK_ALIGN_END); // Align to the bottom vertically within the box

    GtkWidget *event_box = gtk_event_box_new();
    gtk_container_add(GTK_CONTAINER(event_box), *message_label);
    g_signal_connect(event_box, "button-press-event", G_CALLBACK(on_open_message_settings_clicked), create_message_data(chat_data, message, message_id));

    gtk_box_pack_start(GTK_BOX(message), GTK_WIDGET(user_icon), false, false, 0);
    gtk_box_pack_start(GTK_BOX(message), event_box, false, false, 5);
    add_to_box_start(Builder, message, CHAT_FIELD_CONTENER_ID, 10);

    char time_str[DEFAULT_TIME_FORMAT_LEN];
    strftime(time_str, DEFAULT_TIME_FORMAT_LEN, DEFAULT_TIME_FORMAT, localtime(&datetime));
    printf("%s\n", time_str);

    gtk_widget_show_all(message);

    g_timeout_add(50, scroll_to_bottom_message_list, Builder);

    return message;
}

static void load_messages(id_t chat_id, t_chat_data *chat_data) {
    list_t *new_messages_in_chat = rq_get_messages_in_chat(ServerAddress, chat_id);
    if (toggle_widget_visibility(!new_messages_in_chat, Builder, CONNECTING_BOX_ID)) {
        free_user_messages_list(new_messages_in_chat);
        return;
    }
    free_user_messages_list(LoadedMessagesList);
    LoadedMessagesList = new_messages_in_chat;

    for (list_node_t *i = LoadedMessagesList->head; i != NULL; i = i->next) {
        t_user_message *message = (t_user_message *)i->val;
        message->widget = create_and_show_message_widget(message->data, message->creation_date, &message->label_widget, chat_data, message->message_id);
    }
}

void gui_update_messages_list(list_t *message_updates_list, char *sended_message, t_chat_data *chat_data) {
    for (list_node_t *i = message_updates_list->head; i != NULL; i = i->next) {
        t_message_update *message_update = (t_message_update *)i->val;
        LoadedMessagesList->match = compare_user_messages_IDs;
        list_node_t *client_message_node = list_find(LoadedMessagesList, message_update);
        t_user_message *client_message = client_message_node ? client_message_node->val : NULL;

        if (message_update->remove) {
            gtk_widget_hide(client_message->widget);
            gtk_widget_destroy(client_message->widget);
            list_remove(LoadedMessagesList, client_message_node);
            continue;
        }

        if (client_message && client_message->changes_count != message_update->message.changes_count) {
            free(client_message->data);
            client_message->data = message_update->message.data;
            set_label_text(client_message->label_widget, client_message->data);
            client_message->changes_count = message_update->message.changes_count;
            continue;
        }

        if (i->next == NULL && sended_message != NULL) {
            message_update->message.widget = create_and_show_message_widget(sended_message, message_update->message.creation_date, &message_update->message.label_widget, chat_data, message_update->message.message_id);
            free(message_update->message.data);
            message_update->message.data = strdup(sended_message);
        }
        else {
            message_update->message.widget = create_and_show_message_widget(message_update->message.data, message_update->message.creation_date, &message_update->message.label_widget, chat_data, message_update->message.message_id);
        }

        list_rpush(LoadedMessagesList, list_node_new(message_update));
    }
}

static void gui_send_message_and_update_messages_list(id_t chat_id, char *message, t_chat_data *chat_data) {
    list_t *message_updates_list = rq_send_message_and_get_messages_updates(ServerAddress, ThisUserId, chat_id, message, LoadedMessagesList);
    if (toggle_widget_visibility(!message_updates_list, Builder, CONNECTING_BOX_ID)) return;
    gui_update_messages_list(message_updates_list, message, chat_data);
    list_destroy(message_updates_list);
    set_entry_text(Builder, NEW_MESSAGE_ENTRY_ID, "");
}

static void update_messages_list(id_t chat_id, t_chat_data *chat_data) {
    list_t *message_updates_list = rq_get_message_updates(ServerAddress, chat_id, LoadedMessagesList);
    if (toggle_widget_visibility(!message_updates_list, Builder, CONNECTING_BOX_ID)) return;
    gui_update_messages_list(message_updates_list, NULL, chat_data);
    list_destroy(message_updates_list);
}

static gboolean on_update_tick(gpointer user_data) {
    t_chat_data *chat_data = (t_chat_data *)user_data;
    update_messages_list(chat_data->chat.id, chat_data);
    return TRUE;
}

static guint UpdateTickThread = 0;
static void gui_open_chat(t_chat_data *chat_data) {
    GtkWidget *message_field = get_widget(Builder, NEW_MESSAGE_ENTRY_ID);
    GtkWidget *chat_settings_window = get_widget(Builder, CHAT_SETTINGS_BUTTON_ID);

    clear_container(Builder, CHAT_FIELD_CONTENER_ID);
    write_label_text(Builder, CHAT_NAME_LABEL_ID, chat_data->chat.name);
    load_messages(chat_data->chat.id, chat_data);

    g_signal_handlers_destroy(message_field);

    g_signal_connect(message_field, "activate", G_CALLBACK(on_send_message_clicked), chat_data);
    g_signal_connect(chat_settings_window, "clicked", G_CALLBACK(on_open_chat_settings_clicked), chat_data);

    if (UpdateTickThread != 0) {
        g_source_remove(UpdateTickThread);
        UpdateTickThread = 0;
    }
    UpdateTickThread = g_timeout_add(MESSAGES_LIST_UPDATE_INTERVAL, on_update_tick, chat_data);
}

void on_chat_clicked(GtkButton *b, gpointer user_data) {
    t_chat_data *chat_data = (t_chat_data *)user_data;
    gui_open_chat(chat_data);
    show_widget(Builder, "chat_area");
    hide_widget(Builder, "warning_text");
    (void)b;
}

void on_send_message_clicked(GtkEntry *entry, gpointer *user_data) {
    t_chat_data *chat_data = (t_chat_data *)user_data;
    char *message_text = (char *)gtk_entry_get_text(entry);
    gui_send_message_and_update_messages_list(chat_data->chat.id, message_text, chat_data);
}
