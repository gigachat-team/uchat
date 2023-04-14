#include "../../client.h"


void gui_init_chat_settings_window(t_chat_data *chat_data) {
    // uint32_t members_count = 0;
    // t_user *members = rq_get_chat_members(*server_address, chat_id, &members_count);
    // for (size_t i = 0; i < members_count; i++) {
    //     printf("Id: %d; Login: %s\n", members[i].id, members[i].login);
    // }
    // free_users(members, members_count);

    GtkWidget *leave_chat_button = get_widget(chat_data->gui_data.builder, "leave_chat_button");

    g_signal_handlers_destroy(leave_chat_button);
    g_signal_connect(leave_chat_button, "clicked", G_CALLBACK(on_leave_from_chat_clicked), chat_data);
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
