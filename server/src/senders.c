#include "../server.h"

void send_chat(int socket, t_chat chat) {
    send_unsigned_int(socket, chat.id);
    recieve_unsigned_char(socket);

    send_string(socket, chat.name);
    recieve_unsigned_char(socket);
}

