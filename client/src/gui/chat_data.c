#include "gui.h"

t_chat_data *create_chat_data_ptr(char *chat_name, id_t chat_id, id_t chat_owner_id) {
    t_chat_data *chat_data = malloc(sizeof(t_chat_data));
    chat_data->chat.name = strdup(chat_name);
    chat_data->chat.id = chat_id;
    chat_data->chat.owner_id = chat_owner_id;
    return chat_data;
}
