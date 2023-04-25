#include "gui.h"

t_chat_data *create_chat_data_ptr(char *chat_name, id_t chat_id, id_t chat_owner_id) {
    t_chat_data *chat_data = malloc(sizeof(t_chat_data));
    chat_data->chat.name = strdup(chat_name);
    chat_data->chat.id = chat_id;
    chat_data->chat.owner_id = chat_owner_id;
    chat_data->messages = list_new();
    return chat_data;
}

t_message_data *create_message_data(t_chat_data *chat_data, GtkWidget *message_contener, id_t message_id) {
    t_message_data *data = malloc(sizeof(t_message_data));
    data->chat_data = chat_data;
    data->message_contener = message_contener;
    data->message_id = message_id;
    return data;
}
