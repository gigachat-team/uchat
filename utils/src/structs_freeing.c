#include "utils.h"

void free_chat(t_chat chat) {
    free(chat.name);
}

void free_chats(t_chat *chats, size_t length) {
    for (size_t i = 0; i < length; i++) {
        free_chat(chats[i]);
    }
    free(chats);
}

void free_new_chat_member_data(t_new_chat_member_data new_chat_member_data) {
    free(new_chat_member_data.member_login);
}


