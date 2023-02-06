#include "../client.h"

t_chat receive_chat(int socket) {
    int chat_id = receive_unsigned_int(socket);
    char *chat_name = receive_string(socket);

    t_chat chat = {chat_id, chat_name};
    return chat;
}

