#include "../../client.h"

void open_chat(GtkButton *bconfirm, gpointer user_data) {
    t_chat_data data = *(t_chat_data *)user_data;

    write_label_text(data.gui_data.builder, "chat_name", data.chat.name);
    // handle_chatting(data.gui_data.server_address, data.gui_data.user_id, 0);

    (void)bconfirm;
}

//Memmory leak:)
t_chat_data *create_chat_data(char *chat_name, t_gui_data gui_data) {
    t_chat_data *chat_data = malloc(sizeof(t_chat_data));

    chat_data->gui_data.builder = gui_data.builder;
    chat_data->chat.name = strdup(chat_name);

    return chat_data;
}
