#include "gui.h"

static char *user_id_to_str(int user_id) {
    char *id;
    asprintf(&id, "%i", user_id);
    return id;
}

static void gui_fill_members_list(GtkBuilder *builder, t_address *server_address, id_t user_id, id_t chat_id) {
    uint32_t members_count = 0;
    GtkWidget *members_list = get_widget(builder, "members_in_chat_list");
    t_user *members = rq_get_chat_members(*server_address, chat_id, &members_count);

    // Remove all items from the combo box
    gtk_combo_box_text_remove_all(GTK_COMBO_BOX_TEXT(members_list));

    for (size_t i = 0; i < members_count; i++) {
        if (members[i].id == user_id) continue;
        gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(members_list), user_id_to_str(members[i].id), strdup(members[i].login));
    }
    free_users(members, members_count);
}

static void gui_init_chat_settings_window(t_chat_data *chat_data) {
    GtkWidget *leave_chat_button = get_widget(chat_data->gui_data.builder, "leave_chat_button");
    GtkWidget *add_member_button = get_widget(chat_data->gui_data.builder, "add_chat_member_button");
    GtkWidget *remove_member_button = get_widget(chat_data->gui_data.builder, "remove_chat_member_button");
    GtkWidget *group_settings_box = get_widget(chat_data->gui_data.builder, GROUP_SETTINGS_BOX);

    g_signal_handlers_destroy(leave_chat_button);
    g_signal_connect(leave_chat_button, "clicked", G_CALLBACK(on_leave_from_chat_clicked), chat_data);

    if (chat_data->chat.owner_id == chat_data->gui_data.user_id) {
        gtk_widget_show(group_settings_box);
    } else {
        gtk_widget_hide(group_settings_box);
    }

    g_signal_handlers_destroy(add_member_button);
    g_signal_connect(add_member_button, "clicked", G_CALLBACK(on_add_chat_member_clicked), chat_data);

    g_signal_handlers_destroy(remove_member_button);
    g_signal_connect(remove_member_button, "clicked", G_CALLBACK(on_remove_chat_member_clicked), chat_data);

    gui_fill_members_list(chat_data->gui_data.builder, &chat_data->gui_data.server_address, chat_data->gui_data.user_id, chat_data->chat.id);
}

static void gui_remove_chat_member(GtkBuilder *builder, t_address *server_address, id_t user_id, id_t chat_id) {
    const gchar *current_user_in_list_id = gtk_combo_box_get_active_id(GTK_COMBO_BOX(get_widget(builder, "members_in_chat_list")));
    if (current_user_in_list_id == NULL) return;

    t_state_code remove_state = rq_remove_member_from_chat(*server_address, atoi(current_user_in_list_id), chat_id);
    if (remove_state == USER_REMOVED_FROM_CHAT_SUCCESSFULLY) {
        printf("The user successfully removed from chat.\n");
    }

    gui_fill_members_list(builder, server_address, user_id, chat_id);
}

static void gui_add_chat_member(GtkBuilder *builder, t_address *server_address, id_t user_id, id_t chat_id) {
    char *name_user = get_entry_text(builder, "entry_add_member");

    t_state_code adding_new_member_result = rq_add_new_member(*server_address, chat_id, name_user);
    if (adding_new_member_result == USER_SUCCESSFULLY_ADDED_TO_CHAT) {
        printf("The user %s successfully added to the chat.\n", name_user);
    }
    else if (adding_new_member_result == SUCH_USER_IS_ALREADY_IN_CHAT) {
        printf("The user %s is already in the chat.\n", name_user);
    }
    gui_fill_members_list(builder, server_address, user_id, chat_id);
}

static void gui_leave_from_chat(GtkBuilder *builder, t_address *server_address, id_t user_id, id_t chat_id) {
    t_state_code response = rq_remove_member_from_chat(*server_address, user_id, chat_id);
    if (response == USER_REMOVED_FROM_CHAT_SUCCESSFULLY) {
        printf("The user removed from the chat.\n");
    }

    write_label_text(builder, CHAT_NAME_LABEL_ID, NULL);
    gui_render_chats_list(builder, server_address, user_id);
    clear_container(builder, CHAT_FIELD_CONTENER_ID);
}

void on_open_chat_settings_clicked(GtkButton *b, gpointer user_data) {
    t_chat_data *chat_data = (t_chat_data *)user_data;
    open_window(chat_data->gui_data.builder, CHAT_SETTINGS_WINDOW_ID);
    gui_init_chat_settings_window(chat_data);
    (void)b;
}

void on_close_chat_settings_clicked(GtkButton *b, gpointer user_data) {
    t_gui_data *gui_data = (t_gui_data *)user_data;
    close_window(gui_data->builder, CHAT_SETTINGS_WINDOW_ID);
    (void)b;
}

void on_leave_from_chat_clicked(GtkButton *b, gpointer user_data) {
    t_chat_data *chat_data = (t_chat_data *)user_data;
    close_window(chat_data->gui_data.builder, CHAT_SETTINGS_WINDOW_ID);
    gui_leave_from_chat(chat_data->gui_data.builder, &chat_data->gui_data.server_address, chat_data->gui_data.user_id, chat_data->chat.id);
    (void)b;
}

void on_add_chat_member_clicked(GtkButton *b, gpointer user_data) {
    t_chat_data *chat_data = (t_chat_data *)user_data;
    gui_add_chat_member(chat_data->gui_data.builder, &chat_data->gui_data.server_address, chat_data->gui_data.user_id, chat_data->chat.id);
    (void)b;
}

void on_remove_chat_member_clicked(GtkButton *b, gpointer user_data) {
    t_chat_data *chat_data = (t_chat_data *)user_data;
    gui_remove_chat_member(chat_data->gui_data.builder, &chat_data->gui_data.server_address, chat_data->gui_data.user_id, chat_data->chat.id);
    (void)b;
}
