#include "request_handlers.h"

void handle_login_changing(int client_socket) {
    uint32_t user_id = receive_uint32(client_socket);
    char *new_login = receive_bytes(client_socket);

    sqlite3 *db = db_open();
    bool login_already_exists = db_change_login(db, user_id, new_login);
    db_close(db);

    if (login_already_exists) {
        send_byte(client_socket, SUCH_LOGIN_ALREADY_EXISTS);
    } else {
        send_byte(client_socket, LOGIN_SUCCESSFULLY_CHANGED);
    }

    free(new_login);
}
