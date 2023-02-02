#include "../client.h"

t_chat recieve_chat(int socket) {
    int chat_id = recieve_unsigned_int(socket);
    char *chat_name = recieve_string(socket);

    t_chat chat = {chat_id, chat_name};
    return chat;
}

