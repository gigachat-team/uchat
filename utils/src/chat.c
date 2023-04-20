#include "chat.h"

void free_chat(t_chat *chat) {
    free(chat->name);
}

void free_chat_ptr(void *chat) {
    t_chat *chat1 = chat;
    (void)chat1;
    free_chat(chat);
    free(chat);
}

void free_chats(t_chat *chats, size_t length) {
    for (size_t i = 0; i < length; i++) {
        free_chat(&chats[i]);
    }
    free(chats);
}

void free_chats_list(list_t *chats_list) {
    chats_list->free = free_chat_ptr;
    list_destroy(chats_list);
}
