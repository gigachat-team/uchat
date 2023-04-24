#include "gui.h"

// Create new button in chats list
static void create_button_in_chat_list(GtkBuilder *gtk_builder, t_address *server_address, id_t user_id, t_chat *chat) {
    GtkWidget *new_button = gtk_button_new_with_label(chat->name);
    t_chat_data *chat_data = create_chat_data_ptr(gtk_builder, server_address, user_id, chat->name, chat->id, chat->owner_id);
    g_signal_connect(new_button, "clicked", G_CALLBACK(on_chat_clicked), chat_data);
    add_to_box_start(gtk_builder, new_button, CHATS_LIST_CONTAINER_ID, 0);
}

void gui_render_chats_list(GtkBuilder *gtk_builder, t_address *server_address, id_t user_id) {
    list_t *chats_list = rq_get_chats_i_am_in(*server_address, user_id);
    if (toggle_widget_visibility(!chats_list, gtk_builder, CONNECTING_BOX_ID)) return;

    clear_container(gtk_builder, CHATS_LIST_CONTAINER_ID);

    if (chats_list->len != 0) {
        for (list_node_t *i = chats_list->head; i != NULL; i = i->next) {
            create_button_in_chat_list(gtk_builder, server_address, user_id, i->val);
        }
    }
    else {
        hide_widget(gtk_builder, "chat_area");
        show_widget(gtk_builder, "warning_text");
        printf("You aren't in any chats.\n");
    }

    free_chats_list(chats_list);
}

static void gui_create_chat(GtkBuilder *builder, t_address *server_address, id_t user_id) {
    char *chat_name = get_entry_text(builder, NEW_CHAT_NAME_ENTRY_ID);
    id_t created_chat_id = rq_create_chat(*server_address, chat_name, user_id);
    if (toggle_widget_visibility(!created_chat_id, builder, CONNECTING_BOX_ID)) return;

    printf("Chat \"%s\" with id %u created successfully.\n", chat_name, created_chat_id);
    close_window(builder, CREATE_CHAT_WINDOW_ID);
    gui_render_chats_list(builder, server_address, user_id);
}

void on_open_chat_creator_button_clicked(GtkButton *b, gpointer user_data) {
    t_gui_data *gui_data = (t_gui_data *)user_data;
    open_window(gui_data->builder, CREATE_CHAT_WINDOW_ID);

    apply_styles_to_create_chat_window(gui_data->builder);

    (void)b;
}

void on_close_chat_creator_button_clicked(GtkButton *b, gpointer user_data) {
    t_gui_data *gui_data = (t_gui_data *)user_data;
    close_window(gui_data->builder, CREATE_CHAT_WINDOW_ID);
    (void)b;
}

void on_create_chat_button_clicked(GtkButton *b, gpointer user_data) {
    t_gui_data *gui_data = (t_gui_data *)user_data;
    gui_create_chat(gui_data->builder, &gui_data->server_address, gui_data->user_id);
    (void)b;
}
