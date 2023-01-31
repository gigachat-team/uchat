#include "../../server.h"

t_chat *db_get_chats_user_is_in(int user_id, size_t *number_of_chats) {
    int *IDs_of_chats_user_is_in = db_get_IDs_of_chats_user_is_in(user_id,  number_of_chats);

    t_chat *descriptions_of_chats = malloc(*number_of_chats * sizeof(t_chat));

    for (size_t i = 0; i < *number_of_chats; i++) {
        descriptions_of_chats[i].id = IDs_of_chats_user_is_in[i];
        descriptions_of_chats[i].name = db_get_chat_name_by_id(IDs_of_chats_user_is_in[i]);
    }

    free(IDs_of_chats_user_is_in);

    return descriptions_of_chats;
}

