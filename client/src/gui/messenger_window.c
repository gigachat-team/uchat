#include "../../client.h"

// Create new button in chats list
static void create_button_in_chat_list(t_gui_data data, t_chat* chat_data) {
    GtkWidget* new_button = gtk_button_new_with_label(chat_data->name);
    g_signal_connect(new_button, "clicked", G_CALLBACK(open_chat), create_chat_data(chat_data, data));
    add_to_box_start(data.builder, new_button, "chats_contener", 0);
}


static void init_chats_list(t_gui_data data) {
    size_t chats_count = 0;
    t_chat* chats = rq_get_chats_i_am_in(data.server_address, data.user_id, &chats_count);

    if (chats_count != 0) {
        clear_container(data.builder, "chats_contener");

        for (size_t i = 0; i < chats_count; i++) {
            create_button_in_chat_list(data, &chats[i]);
        }
    }
    else {
        printf("You aren't in any chats.\n");
    }

    free_chats(chats, chats_count);
}

// Buttons-events-----------------------------------
void open_creater_chat_window(GtkButton* bconfirm, gpointer user_data) {
    t_gui_data data = GUI_DATA(user_data);

    open_window(data.builder, "Create_room_window");

    (void)bconfirm;
}

void close_creater_chat_window(GtkButton* bconfirm, gpointer user_data) {
    t_gui_data data = GUI_DATA(user_data);

    close_window(data.builder, "Create_room_window");

    (void)bconfirm;
}

void create_new_chat(GtkButton* bconfirm, gpointer user_data) {
    t_gui_data data = GUI_DATA(user_data);
    char* chat_name = get_entry_text(data.builder, "wname_room");

    create_new_chat_in_server(data.server_address, data.user_id, chat_name);
    close_creater_chat_window(bconfirm, user_data);
    init_chats_list(data);
}
//-------------------------------------------------

void open_messenger_window(t_gui_data data) {
    close_window(data.builder, "Authorization");
    open_window(data.builder, "Messenger");

    init_chats_list(data);
}
