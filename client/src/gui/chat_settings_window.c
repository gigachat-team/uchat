#include "client_main.h"

void gui_fill_members_list(GtkBuilder *builder, t_address *server_address, id_t chat_id) {
    GtkWidget *members_list = get_widget(builder, "members_in_chat_list");

    uint32_t members_count = 0;
    t_user *members = rq_get_chat_members(*server_address, chat_id, &members_count);
    for (size_t i = 0; i < members_count; i++) {
        gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(members_list), strdup(members[i].login));
    }
    free_users(members, members_count);
}

void gui_init_chat_settings_window(t_chat_data *chat_data) {
    GtkWidget *leave_chat_button = get_widget(chat_data->gui_data.builder, "leave_chat_button");
    GtkWidget *add_member_button = get_widget(chat_data->gui_data.builder, "add_chat_member_button");

    g_signal_handlers_destroy(leave_chat_button);
    g_signal_connect(leave_chat_button, "clicked", G_CALLBACK(on_leave_from_chat_clicked), chat_data);

    g_signal_handlers_destroy(add_member_button);
    g_signal_connect(add_member_button, "clicked", G_CALLBACK(on_add_chat_member_clicked), chat_data);

    gui_fill_members_list(chat_data->gui_data.builder, &chat_data->gui_data.server_address, chat_data->chat.id);
}

void gui_add_chat_member(GtkBuilder *builder, t_address *server_address, id_t chat_id) {
    char *name_user = get_entry_text(builder, "entry_add_member");

    t_new_chat_member_data new_chat_member_data = { chat_id, strdup(name_user) };
    t_state_code adding_new_member_result = rq_add_new_member(*server_address, new_chat_member_data);
    if (adding_new_member_result == USER_SUCCESSFULLY_ADDED_TO_CHAT) {
        printf("The user %s successfully added to the chat.\n", new_chat_member_data.member_login);
    }
    else if (adding_new_member_result == SUCH_USER_IS_ALREADY_IN_CHAT) {
        printf("The user %s is already in the chat.\n", new_chat_member_data.member_login);
    }
    free_new_chat_member_data(new_chat_member_data);
}

void gui_leave_from_chat(GtkBuilder *builder, t_address *server_address, id_t user_id, id_t chat_id) {
    t_state_code response = rq_remove_member_from_chat(*server_address, user_id, chat_id);
    if (response == USER_REMOVED_FROM_CHAT_SUCCESSFULLY) {
        printf("The user removed from the chat.\n");
    }

    write_label_text(builder, CHAT_NAME_LABEL_ID, NULL);
    gui_render_chats_list(builder, server_address, user_id);
    clear_container(builder, CHAT_FIELD_CONTENER_ID);
}
