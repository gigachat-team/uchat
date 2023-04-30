#include "gui.h"

static gboolean scroll_to_bottom_message_list(gpointer user_data) {
    GtkBuilder *builder = user_data;
    scroll_to_bottom(builder, MESSAGES_LIST_SCROLLED_WINDOW_ID);
    return FALSE;
}

static char *get_printable_time(time_t _time) {
    time_t now = time(NULL);
    struct tm now_tm = *localtime(&now);
    struct tm time_tm = *localtime(&_time);

    char *printable_time = NULL;

    if (time_tm.tm_year == now_tm.tm_year) {
        if (time_tm.tm_yday == now_tm.tm_yday) {
            printable_time = malloc(6);
            strftime(printable_time, 6, "%2H:%2M", &time_tm);
        } else {
            printable_time = malloc(12);
            strftime(printable_time, 12, "%2m.%2d %2H:%2M", &time_tm);
        }
    } else {
        printable_time = malloc(14);
        strftime(printable_time, 14, "%4y.%2m.%2d %2H:%2M", &time_tm);
    }

    return printable_time;
}

static void create_and_show_message_widget(t_message *message) {
    char *creation_date_str = get_printable_time(message->creation_date);
    char *is_edited_str = message->changes_count ? "edited" : "";

    GtkWidget *reply_box = NULL;

    message->container_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
    GtkWidget *user_icon = get_image_from_path("resources/img/message_icon.jpeg", 45, 45);
    GtkWidget *event_box = gtk_event_box_new();
    GtkWidget *content_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 2);
    GtkWidget *name = gtk_label_new(message->sender_login);
    if (message->reply_message_id != 0) {
        reply_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);
        LoadedMessagesList->match = compare_messages_IDs;
        t_message searching_reply_message_id = {.message_id = message->reply_message_id};

        list_node_t *replied_message_node = list_find(LoadedMessagesList, &searching_reply_message_id);
        if (!replied_message_node) {
            message->replied_message_content_label = gtk_label_new("Deleted Message");
        } else {
            t_message *replied_message = replied_message_node->val;
            message->replied_message_login_label = gtk_label_new(replied_message->sender_login);
            message->replied_message_content_label = gtk_label_new(replied_message->data);
        }

    }
    message->content_label = gtk_label_new((gchar *)message->data);
    GtkWidget *additional_info_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 3);
    message->is_edited_label = gtk_label_new(is_edited_str);
    GtkWidget *creation_date_label = gtk_label_new(creation_date_str);

    // Main box
    gtk_box_pack_start(GTK_BOX(message->container_box), user_icon, false, false, 0);
    gtk_box_pack_start(GTK_BOX(message->container_box), event_box, false, false, 10);

    // Event box
    gtk_container_add(GTK_CONTAINER(event_box), content_box);

    // Box without icon
    gtk_container_add(GTK_CONTAINER(content_box), name);
    if (reply_box)
        gtk_container_add(GTK_CONTAINER(content_box), reply_box);
    gtk_container_add(GTK_CONTAINER(content_box), message->content_label);
    gtk_container_add(GTK_CONTAINER(content_box), additional_info_box);

    // Reply box
    if (reply_box) {
        if (message->replied_message_login_label)
            gtk_container_add(GTK_CONTAINER(reply_box), message->replied_message_login_label);
        gtk_container_add(GTK_CONTAINER(reply_box), message->replied_message_content_label);
    }

    // Additional info box
    gtk_container_add(GTK_CONTAINER(additional_info_box), message->is_edited_label);
    gtk_container_add(GTK_CONTAINER(additional_info_box), creation_date_label);

    if (reply_box) {
        if (message->replied_message_login_label)
            gtk_widget_set_halign(message->replied_message_login_label, GTK_ALIGN_START);
        gtk_widget_set_halign(message->replied_message_content_label, GTK_ALIGN_START);
        gtk_label_set_xalign(GTK_LABEL(message->replied_message_content_label), 0);
        apply_style_to_widget(reply_box, "reply_box");
        if (message->replied_message_login_label)
            apply_style_to_widget(message->replied_message_login_label, "reply_login");
        gtk_label_set_line_wrap(GTK_LABEL(message->replied_message_content_label), TRUE);
        gtk_label_set_line_wrap_mode(GTK_LABEL(message->replied_message_content_label), PANGO_WRAP_WORD_CHAR);
    }

    gtk_widget_set_margin_start(additional_info_box, 10);
    gtk_widget_set_margin_bottom(additional_info_box, 10);
    gtk_widget_set_margin_end(additional_info_box, 10);
    gtk_widget_set_margin_start(name, 10);
    gtk_widget_set_margin_top(name, 10);
    gtk_widget_set_margin_end(name, 10);
    gtk_widget_set_margin_start(message->content_label, 10);
    gtk_widget_set_margin_end(message->content_label, 10);

    gtk_label_set_xalign(GTK_LABEL(name), 0);
    gtk_widget_set_halign(name, GTK_ALIGN_START);
    gtk_label_set_line_wrap(GTK_LABEL(message->content_label), TRUE);
    gtk_label_set_line_wrap_mode(GTK_LABEL(message->content_label), PANGO_WRAP_CHAR);
    gtk_label_set_xalign(GTK_LABEL(message->content_label), 0);
    gtk_widget_set_halign(message->content_label, GTK_ALIGN_START);
    gtk_widget_set_valign(user_icon, GTK_ALIGN_END);
    gtk_widget_set_halign(additional_info_box, GTK_ALIGN_END);

    g_signal_connect(event_box, "button-press-event", G_CALLBACK(on_open_message_settings_clicked), message);

    add_to_box_start(Builder, message->container_box, CHAT_FIELD_CONTENER_ID, 10);

    apply_style_to_widget(message->is_edited_label, ADDITIONAL_MESSAGE_INFO_LABEL_ID);
    apply_style_to_widget(creation_date_label, ADDITIONAL_MESSAGE_INFO_LABEL_ID);
    if (message->sender_id == ThisUser->id) {
        apply_style_to_widget(content_box, "my-message-content-box");
        apply_style_to_widget(name, "my-name-text");
        apply_style_to_widget(message->is_edited_label, MY_ADDITIONAL_MESSAGE_INFO_LABEL_ID);
        apply_style_to_widget(creation_date_label, MY_ADDITIONAL_MESSAGE_INFO_LABEL_ID);
    } else {
        apply_style_to_widget(content_box, "message-content-box");
        apply_style_to_widget(name, CSS_CLASS_TIME_NAME_SETTINGS);
    }

    gtk_widget_show_all(message->container_box);

    g_timeout_add(50, scroll_to_bottom_message_list, Builder);

    free(creation_date_str);
}

static void load_messages(id_t chat_id) {
    list_t *new_messages_in_chat = rq_get_messages_in_chat(ServerAddress, chat_id);
    if (toggle_widget_visibility(!new_messages_in_chat, Builder, CONNECTING_BOX_ID)) {
        free_messages_list(new_messages_in_chat);
        return;
    }
    free_messages_list(LoadedMessagesList);
    LoadedMessagesList = new_messages_in_chat;

    for (list_node_t *i = LoadedMessagesList->head; i != NULL; i = i->next) {
        t_message *message = (t_message *)i->val;
        create_and_show_message_widget(message);
    }
}

void gui_update_messages_list(list_t *message_updates_list, char *sended_message) {
    for (list_node_t *i = message_updates_list->head; i != NULL; i = i->next) {
        t_message *message_update = i->val;
        LoadedMessagesList->match = compare_messages_IDs;
        list_node_t *client_message_node = list_find(LoadedMessagesList, message_update);
        t_message *client_message = client_message_node ? client_message_node->val : NULL;

        if (!message_update->sender_id && !message_update->data) {
            for (list_node_t *i = LoadedMessagesList->head; i != NULL; i = i->next) {
                t_message *msg = i->val;
                if (msg->reply_message_id == client_message->message_id) {
                    set_label_text(msg->replied_message_content_label, "Deleted Message");
                    gtk_widget_destroy(msg->replied_message_login_label);
                }
            }

            gtk_widget_hide(client_message->container_box);
            gtk_widget_destroy(client_message->container_box);
            free(client_message);
            list_remove(LoadedMessagesList, client_message_node);

            continue;
        }

        if (client_message && client_message->changes_count != message_update->changes_count) {
            free(client_message->data);
            client_message->data = message_update->data;
            message_update->data = NULL;
            set_label_text(client_message->content_label, client_message->data);
            set_label_text(client_message->is_edited_label, "edited");
            client_message->changes_count = message_update->changes_count;

            for (list_node_t *i = LoadedMessagesList->head; i != NULL; i = i->next) {
                t_message *msg = i->val;
                if (msg->reply_message_id == client_message->message_id) {
                    set_label_text(msg->replied_message_content_label, client_message->data);
                }
            }

            continue;
        }

        t_message *message = malloc(sizeof(t_message));
        *message = *message_update;
        message_update->sender_login = NULL;
        message_update->data = NULL;

        if (i->next == NULL && sended_message != NULL) {
            free(message->data);
            message->data = strdup(sended_message);
            create_and_show_message_widget(message);
        } else {
            create_and_show_message_widget(message);
        }

        list_rpush(LoadedMessagesList, list_node_new(message));
    }
}

static void gui_send_message_and_update_messages_list(char *message) {
    if (strcmp(message, "") == 0 || message == NULL) return;
    list_t *message_updates_list = rq_send_message_and_get_messages_updates(ServerAddress, ThisUser->id, SelectedChat->id, message, LoadedMessagesList);
    if (toggle_widget_visibility(!message_updates_list, Builder, CONNECTING_BOX_ID)) return;
    gui_update_messages_list(message_updates_list, message);
    free_messages_list(message_updates_list);
    set_entry_text(Builder, NEW_MESSAGE_ENTRY_ID, "");
}

static void update_messages_list() {
    list_t *message_updates_list = rq_get_message_updates(ServerAddress, SelectedChat->id, LoadedMessagesList);
    if (toggle_widget_visibility(!message_updates_list, Builder, CONNECTING_BOX_ID)) return;
    gui_update_messages_list(message_updates_list, NULL);
    free_messages_list(message_updates_list);
}

static gboolean on_update_tick(gpointer user_data) {
    update_messages_list();
    (void)user_data;
    return TRUE;
}

static guint UpdateTickThread = 0;
static void gui_open_chat(t_chat *chat) {
    GtkWidget *message_field = get_widget(Builder, NEW_MESSAGE_ENTRY_ID);
    GtkWidget *chat_settings_window = get_widget(Builder, CHAT_SETTINGS_BUTTON_ID);

    clear_container(Builder, CHAT_FIELD_CONTENER_ID);
    write_label_text(Builder, SELECTED_CHAT_NAME_LABEL_ID, chat->name);
    load_messages(chat->id);

    g_signal_handlers_destroy(message_field);

    g_signal_connect(message_field, "activate", G_CALLBACK(on_send_message_clicked), NULL);
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

void on_send_message_clicked(GtkEntry *entry) {
    char *message_text = (char *)gtk_entry_get_text(entry);
    gui_send_message_and_update_messages_list(message_text);
}
