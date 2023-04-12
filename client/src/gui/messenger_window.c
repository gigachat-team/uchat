#include "../../client.h"

// Create new button in chats list
static void create_button_in_chat_list(GtkBuilder *gtk_builder, t_address *server_address, id_t user_id, t_chat *chat) {
    GtkWidget *new_button = gtk_button_new_with_label(chat->name);
    t_chat_data *chat_data = create_chat_data_ptr(gtk_builder, server_address, user_id, chat->name, chat->id);
    g_signal_connect(new_button, "clicked", G_CALLBACK(open_chat), chat_data);
    add_to_box_start(gtk_builder, new_button, "chats_contener", 0);
}


static void init_chats_list(GtkBuilder *gtk_builder, t_address *server_address, id_t user_id) {
    size_t chats_count = 0;
    t_chat *chats = rq_get_chats_i_am_in(*server_address, user_id, &chats_count);

    if (chats_count != 0) {
        clear_container(gtk_builder, "chats_contener");

        for (size_t i = 0; i < chats_count; i++) {
            create_button_in_chat_list(gtk_builder, server_address, user_id, &chats[i]);
        }
    }
    else {
        printf("You aren't in any chats.\n");
    }

    free_chats(chats, chats_count);
}

// Buttons-events-----------------------------------
void on_open_chat_creator_button_clicked(GtkButton *b, gpointer user_data) {
    t_gui_data *gui_data = (t_gui_data *)user_data;
    open_window(gui_data->builder, CREATE_CHAT_WINDOW_ID);
    (void)b;
}

void on_close_chat_creator_button_clicked(GtkButton *b, gpointer user_data) {
    t_gui_data *gui_data = (t_gui_data *)user_data;
    close_window(gui_data->builder, CREATE_CHAT_WINDOW_ID);
    (void)b;
}

void on_create_chat_button_clicked(GtkButton *b, gpointer user_data) {
    t_gui_data *gui_data = (t_gui_data *)user_data;
    char *chat_name = get_entry_text(gui_data->builder, "wname_room");

    id_t created_chat_id = rq_create_chat(gui_data->server_address, chat_name, gui_data->user_id);
    printf("Chat \"%s\" with id %u created successfully.\n", chat_name, created_chat_id);
    close_window(gui_data->builder, CREATE_CHAT_WINDOW_ID);
    init_chats_list(gui_data->builder, &gui_data->server_address, gui_data->user_id);
    (void)b;
}
//-------------------------------------------------

void open_messenger_window(GtkBuilder *gtk_builder, t_address *server_address, id_t user_id) {
    close_window(gtk_builder, AUTHENTICATION_WINDOW_ID);
    open_window(gtk_builder, MESSENGER_WINDOW_ID);

    init_chats_list(gtk_builder, server_address, user_id);
}
