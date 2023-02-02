#include "../client.h"

t_chat recieve_chat(int socket) {
    int chat_id = recieve_unsigned_int(socket);
    send_unsigned_char(socket, SUCCESSFULLY_READ);

    char *chat_name = recieve_string(socket);
    send_unsigned_char(socket, SUCCESSFULLY_READ);

    t_chat chat = {chat_id, chat_name};
    return chat;
}

