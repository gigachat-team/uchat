#include "../server.h"

void send_chat(int socket, t_chat chat) {
    send_unsigned_int(socket, chat.id);
    send_string(socket, chat.name);
}

