#include "gui.h"

static gboolean scroll_to_bottom_message_list(gpointer user_data) {
    GtkBuilder *builder = user_data;
    scroll_to_bottom(builder, "chat_scrolled_field");
    return FALSE;
}

static void create_and_show_message_widget(t_user_message *message) {
    message->widget = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
    message->label_widget = gtk_label_new((gchar *)message->data);
    GtkWidget *user_icon = get_image_from_path("resources/img/message_icon.jpeg", 45, 45);

    gtk_label_set_line_wrap(GTK_LABEL(message->label_widget), TRUE);
    gtk_label_set_line_wrap_mode(GTK_LABEL(message->label_widget), PANGO_WRAP_CHAR);
    gtk_widget_set_valign(user_icon, GTK_ALIGN_END); // Align to the bottom vertically within the box

    GtkWidget *event_box = gtk_event_box_new();
    gtk_container_add(GTK_CONTAINER(event_box), message->label_widget);
    g_signal_connect(event_box, "button-press-event", G_CALLBACK(on_open_message_settings_clicked), message);

    gtk_box_pack_start(GTK_BOX(message->widget), GTK_WIDGET(user_icon), false, false, 0);
    gtk_box_pack_start(GTK_BOX(message->widget), event_box, false, false, 5);
    add_to_box_start(Builder, message->widget, CHAT_FIELD_CONTENER_ID, 10);

    char time_str[DEFAULT_TIME_FORMAT_LEN];
    strftime(time_str, DEFAULT_TIME_FORMAT_LEN, DEFAULT_TIME_FORMAT, localtime(&message->creation_date));
    printf("%s\n", time_str);

    gtk_widget_show_all(message->widget);

    g_timeout_add(50, scroll_to_bottom_message_list, Builder);
}

static void load_messages(id_t chat_id) {
    list_t *new_messages_in_chat = rq_get_messages_in_chat(ServerAddress, chat_id);
    if (toggle_widget_visibility(!new_messages_in_chat, Builder, CONNECTING_BOX_ID)) {
        free_user_messages_list(new_messages_in_chat);
        return;
    }
    free_user_messages_list(LoadedMessagesList);
    LoadedMessagesList = new_messages_in_chat;

    for (list_node_t *i = LoadedMessagesList->head; i != NULL; i = i->next) {
        t_user_message *message = (t_user_message *)i->val;
        create_and_show_message_widget(message);
    }
}

void gui_update_messages_list(list_t *message_updates_list, char *sended_message) {
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

        t_user_message *message = malloc(sizeof(t_user_message));
        *message = message_update->message;

        if (i->next == NULL && sended_message != NULL) {
            free(message_update->message.data);
            message->data = strdup(sended_message);
            create_and_show_message_widget(message);
        }
        else {
            create_and_show_message_widget(message);
        }


        list_rpush(LoadedMessagesList, list_node_new(message));
    }
}

static void gui_send_message_and_update_messages_list(id_t chat_id, char *message) {
    list_t *message_updates_list = rq_send_message_and_get_messages_updates(ServerAddress, ThisUser->id, chat_id, message, LoadedMessagesList);
    if (toggle_widget_visibility(!message_updates_list, Builder, CONNECTING_BOX_ID)) return;
    gui_update_messages_list(message_updates_list, message);
    list_destroy(message_updates_list);
    set_entry_text(Builder, NEW_MESSAGE_ENTRY_ID, "");
}

static void update_messages_list(id_t chat_id) {
    list_t *message_updates_list = rq_get_message_updates(ServerAddress, chat_id, LoadedMessagesList);
    if (toggle_widget_visibility(!message_updates_list, Builder, CONNECTING_BOX_ID)) return;
    gui_update_messages_list(message_updates_list, NULL);
    list_destroy(message_updates_list);
}

static gboolean on_update_tick(gpointer user_data) {
    t_chat *chat = user_data;
    update_messages_list(chat->id);
    return TRUE;
}

static guint UpdateTickThread = 0;
static void gui_open_chat(t_chat *chat) {
    GtkWidget *message_field = get_widget(Builder, NEW_MESSAGE_ENTRY_ID);
    GtkWidget *chat_settings_window = get_widget(Builder, CHAT_SETTINGS_BUTTON_ID);

    clear_container(Builder, CHAT_FIELD_CONTENER_ID);
    write_label_text(Builder, CHAT_NAME_LABEL_ID, chat->name);
    load_messages(chat->id);

    g_signal_handlers_destroy(message_field);

    g_signal_connect(message_field, "activate", G_CALLBACK(on_send_message_clicked), chat);
    g_signal_connect(chat_settings_window, "clicked", G_CALLBACK(on_open_chat_settings_clicked), chat);

    if (UpdateTickThread != 0) {
        g_source_remove(UpdateTickThread);
        UpdateTickThread = 0;
    }
    UpdateTickThread = g_timeout_add(MESSAGES_LIST_UPDATE_INTERVAL, on_update_tick, chat);
}

void on_chat_clicked(GtkButton *b, gpointer user_data) {
    t_chat *chat = user_data;
    SelectedChat = chat;
    gui_open_chat(chat);
    show_widget(Builder, "chat_area");
    hide_widget(Builder, "warning_text");
    (void)b;
}

void on_send_message_clicked(GtkEntry *entry, gpointer user_data) {
    t_chat *chat = user_data;
    char *message_text = (char *)gtk_entry_get_text(entry);
    gui_send_message_and_update_messages_list(chat->id, message_text);
}
