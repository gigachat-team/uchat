#include "gui.h"

// Create new button in chats list
static void create_button_in_chat_list(t_chat *chat) {
    GtkWidget *new_button = gtk_button_new_with_label(chat->name);
    g_signal_connect(new_button, "clicked", G_CALLBACK(on_chat_clicked), chat);
    add_to_box_start(Builder, new_button, CHATS_LIST_CONTAINER_ID, 0);
}

void gui_render_chats_list() {
    list_t *chats_list = rq_get_chats_i_am_in(ServerAddress, ThisUserId);
    if (toggle_widget_visibility(!chats_list, Builder, CONNECTING_BOX_ID)) return;

    clear_container(Builder, CHATS_LIST_CONTAINER_ID);

    if (chats_list->len != 0) {
        for (list_node_t *i = chats_list->head; i != NULL; i = i->next) {
            create_button_in_chat_list(i->val);
        }
    }
    else {
        hide_widget(Builder, "chat_area");
        show_widget(Builder, "warning_text");
        printf("You aren't in any chats.\n");
    }
}

static void gui_create_chat() {
    char *chat_name = get_entry_text(Builder, NEW_CHAT_NAME_ENTRY_ID);
    id_t created_chat_id = rq_create_chat(ServerAddress, chat_name, ThisUserId);
    if (toggle_widget_visibility(!created_chat_id, Builder, CONNECTING_BOX_ID)) return;

    printf("Chat \"%s\" with id %u created successfully.\n", chat_name, created_chat_id);
    close_window(Builder, CREATE_CHAT_WINDOW_ID);
    gui_render_chats_list();
}

void on_open_chat_creator_button_clicked(GtkButton *b) {
    open_window(Builder, CREATE_CHAT_WINDOW_ID);
    apply_styles_to_create_chat_window(Builder);
    (void)b;
}

void on_close_chat_creator_button_clicked(GtkButton *b) {
    close_window(Builder, CREATE_CHAT_WINDOW_ID);
    (void)b;
}

void on_create_chat_button_clicked(GtkButton *b) {
    gui_create_chat();
    (void)b;
}
