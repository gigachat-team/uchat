#include "gui.h"

t_chat_data *create_chat_data_ptr(GtkBuilder *gtk_builder, t_address *server_address, id_t user_id, char *chat_name, id_t chat_id, id_t chat_owner_id) {
    t_chat_data *chat_data = malloc(sizeof(t_chat_data));
    chat_data->gui_data.builder = gtk_builder;
    chat_data->gui_data.server_address = *server_address;
    chat_data->gui_data.user_id = user_id;
    chat_data->chat.name = strdup(chat_name);
    chat_data->chat.id = chat_id;
    chat_data->chat.owner_id = chat_owner_id;
    chat_data->messages = list_new();
    return chat_data;
}
