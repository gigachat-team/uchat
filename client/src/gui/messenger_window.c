#include "../../client.h"

static t_chat_data *create_chat_data_ptr(GtkBuilder *gtk_builder, t_address *server_address, id_t user_id, char *chat_name, id_t chat_id) {
    t_chat_data *chat_data = malloc(sizeof(t_chat_data));
    chat_data->gui_data.builder = gtk_builder;
    chat_data->gui_data.server_address = *server_address;
    chat_data->gui_data.user_id = user_id;
    chat_data->chat.name = strdup(chat_name);
    chat_data->chat.id = chat_id;
    chat_data->messages.list = NULL;
    chat_data->messages.size = 0;
    return chat_data;
}

// Create new button in chats list
static void create_button_in_chat_list(GtkBuilder *gtk_builder, t_address *server_address, id_t user_id, t_chat *chat) {
    GtkWidget *new_button = gtk_button_new_with_label(chat->name);
    t_chat_data *chat_data = create_chat_data_ptr(gtk_builder, server_address, user_id, chat->name, chat->id);
    g_signal_connect(new_button, "clicked", G_CALLBACK(on_chat_clicked), chat_data);
    add_to_box_start(gtk_builder, new_button, CHATS_LIST_CONTAINER_ID, 0);
}


void gui_render_chats_list(GtkBuilder *gtk_builder, t_address *server_address, id_t user_id) {
    size_t chats_count = 0;
    t_chat *chats = rq_get_chats_i_am_in(*server_address, user_id, &chats_count);

    clear_container(gtk_builder, CHATS_LIST_CONTAINER_ID);

    if (chats_count != 0) {
        for (size_t i = 0; i < chats_count; i++) {
            create_button_in_chat_list(gtk_builder, server_address, user_id, &chats[i]);
        }
    }
    else {
        printf("You aren't in any chats.\n");
    }

    free_chats(chats, chats_count);
}

void gui_create_chat(GtkBuilder *builder, t_address *server_address, id_t user_id) {
    char *chat_name = get_entry_text(builder, NEW_CHAT_NAME_ENTRY_ID);
    id_t created_chat_id = rq_create_chat(*server_address, chat_name, user_id);
    printf("Chat \"%s\" with id %u created successfully.\n", chat_name, created_chat_id);
    close_window(builder, CREATE_CHAT_WINDOW_ID);
    gui_render_chats_list(builder, server_address, user_id);
}
