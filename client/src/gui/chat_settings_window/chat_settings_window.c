#include "gui.h"

static char *user_id_to_str(int user_id) {
    char *id;
    asprintf(&id, "%i", user_id);
    return id;
}

static void gui_fill_members_list(id_t chat_id) {
    uint32_t members_count = 0;
    GtkWidget *members_list = get_widget(Builder, "members_in_chat_list");
    t_user *members = rq_get_chat_members(ServerAddress, chat_id, &members_count);
    if (toggle_widget_visibility(!members, Builder, CONNECTING_BOX_ID)) return;

    // Remove all items from the combo box
    gtk_combo_box_text_remove_all(GTK_COMBO_BOX_TEXT(members_list));

    for (size_t i = 0; i < members_count; i++) {
        if (members[i].id == ThisUserId) continue;
        gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(members_list), user_id_to_str(members[i].id), strdup(members[i].login));
    }
    free_users(members, members_count);
}

static void gui_init_chat_settings_window(t_chat *chat) {
    GtkWidget *leave_chat_button = get_widget(Builder, "leave_chat_button");
    GtkWidget *add_member_button = get_widget(Builder, "add_chat_member_button");
    GtkWidget *remove_member_button = get_widget(Builder, "remove_chat_member_button");
    GtkWidget *group_settings_box = get_widget(Builder, GROUP_SETTINGS_BOX);

    g_signal_handlers_destroy(leave_chat_button);
    g_signal_connect(leave_chat_button, "clicked", G_CALLBACK(on_leave_from_chat_clicked), chat);

    if (chat->owner_id == ThisUserId) {
        gtk_widget_show(group_settings_box);
    } else {
        gtk_widget_hide(group_settings_box);
    }

    g_signal_handlers_destroy(add_member_button);
    g_signal_connect(add_member_button, "clicked", G_CALLBACK(on_add_chat_member_clicked), chat);

    g_signal_handlers_destroy(remove_member_button);
    g_signal_connect(remove_member_button, "clicked", G_CALLBACK(on_remove_chat_member_clicked), chat);

    gui_fill_members_list(chat->id);
}

static void gui_remove_chat_member(id_t chat_id) {
    const gchar *current_user_in_list_id = gtk_combo_box_get_active_id(GTK_COMBO_BOX(get_widget(Builder, "members_in_chat_list")));
    if (current_user_in_list_id == NULL) return;

    t_state_code remove_state = rq_remove_member_from_chat(ServerAddress, atoi(current_user_in_list_id), chat_id);
    if (toggle_widget_visibility(!remove_state, Builder, CONNECTING_BOX_ID)) return;

    if (remove_state == USER_REMOVED_FROM_CHAT_SUCCESSFULLY) {
        printf("The user successfully removed from chat.\n");
    }

    gui_fill_members_list(chat_id);
}

static void gui_add_chat_member(id_t chat_id) {
    char *name_user = get_entry_text(Builder, "entry_add_member");

    t_state_code adding_new_member_result = rq_add_new_member(ServerAddress, chat_id, name_user);
    if (toggle_widget_visibility(!adding_new_member_result, Builder, CONNECTING_BOX_ID)) return;

    if (adding_new_member_result == USER_SUCCESSFULLY_ADDED_TO_CHAT) {
        printf("The user %s successfully added to the chat.\n", name_user);
    }
    else if (adding_new_member_result == SUCH_USER_IS_ALREADY_IN_CHAT) {
        printf("The user %s is already in the chat.\n", name_user);
    }
    gui_fill_members_list(chat_id);
}

static void gui_leave_from_chat(id_t chat_id) {
    t_state_code response = rq_remove_member_from_chat(ServerAddress, ThisUserId, chat_id);
    if (toggle_widget_visibility(!response, Builder, CONNECTING_BOX_ID)) return;

    if (response == USER_REMOVED_FROM_CHAT_SUCCESSFULLY) {
        printf("The user removed from the chat.\n");
    }

    write_label_text(Builder, CHAT_NAME_LABEL_ID, NULL);
    gui_render_chats_list();
    clear_container(Builder, CHAT_FIELD_CONTENER_ID);
}

void on_open_chat_settings_clicked(GtkButton *b, gpointer user_data) {
    t_chat *chat = user_data;
    open_window(Builder, CHAT_SETTINGS_WINDOW_ID);
    apply_styles_to_chat_settings_window(Builder);
    gui_init_chat_settings_window(chat);
    (void)b;
}

void on_close_chat_settings_clicked(GtkButton *b, gpointer user_data) {
    close_window(Builder, CHAT_SETTINGS_WINDOW_ID);
    (void)b;
    (void)user_data;
}

void on_leave_from_chat_clicked(GtkButton *b, gpointer user_data) {
    t_chat *chat = user_data;
    close_window(Builder, CHAT_SETTINGS_WINDOW_ID);
    gui_leave_from_chat(chat->id);
    (void)b;
}

void on_add_chat_member_clicked(GtkButton *b, gpointer user_data) {
    t_chat *chat = user_data;
    gui_add_chat_member(chat->id);
    (void)b;
}

void on_remove_chat_member_clicked(GtkButton *b, gpointer user_data) {
    t_chat *chat = user_data;
    gui_remove_chat_member(chat->id);
    (void)b;
}
