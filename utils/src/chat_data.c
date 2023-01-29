#include "../utils.h"

void free_chat_creation_data(t_chat_creation_data chat_data) {
    free(chat_data.chat_name);
    free(chat_data.owner_login);
}

