#include "../../client.h"

static void create_chat_message(GtkBuilder *builder, char *message_text) {
    GtkWidget *message = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
    GtkWidget *message_label = gtk_label_new((gchar *)message_text);
    GtkWidget *user_icon = get_image_from_path("client/message_icon.jpeg", 45, 45);

    gtk_label_set_line_wrap(GTK_LABEL(message_label), TRUE);
    gtk_label_set_line_wrap_mode(GTK_LABEL(message_label), PANGO_WRAP_CHAR);
    gtk_widget_set_valign(user_icon, GTK_ALIGN_END); // Align to the bottom vertically within the box

    gtk_box_pack_start(GTK_BOX(message), GTK_WIDGET(user_icon), false, false, 0);
    gtk_box_pack_start(GTK_BOX(message), message_label, false, false, 5);
    add_to_box_start(builder, message, "chat_field", 10);

    gtk_widget_show_all(message);
}

static void load_messages(GtkBuilder *builder, t_address *server_address, id_t chat_id) {
    t_list_with_size messages_list = rq_get_messages_in_chat(*server_address, chat_id);

    for (t_list *i = messages_list.list; i != NULL; i = i->next) {
        create_chat_message(builder, ((t_user_message *)i->data)->data);
    }

    free_user_messages_list(&messages_list);
}

void gui_send_message(GtkBuilder *builder, t_address *server_address, id_t user_id, id_t chat_id, char *message) {
    if (rq_send_text_message(*server_address, user_id, chat_id, message)) {
        printf("A message sent successfully.");
    }
    create_chat_message(builder, message);
}

void gui_open_chat(t_chat_data *chat_data) {
    GtkWidget *message_field = get_widget(chat_data->gui_data.builder, "message_field");

    clear_container(chat_data->gui_data.builder, "chat_field");
    write_label_text(chat_data->gui_data.builder, "chat_name", chat_data->chat.name);
    load_messages(chat_data->gui_data.builder, &chat_data->gui_data.server_address, chat_data->chat.id);

    g_signal_handlers_destroy(message_field);
    g_signal_connect(message_field, "activate", G_CALLBACK(on_send_message_clicked), chat_data);
}
