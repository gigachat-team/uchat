#include "request_handlers.h"

void handle_registration(int client_socket) {
    char *login = receive_bytes(client_socket);
    char *password = receive_bytes(client_socket);

    sqlite3 *db = db_open();
    id_t user_id = db_create_user(db, login, password);
    db_close(db);

    if (user_id != 0) {
        t_package package = create_package(2);
        pack_byte(SUCCESSFUL_REGISTRATION, &package);
        pack_uint32(user_id, &package);
        send_and_free_package(client_socket, &package);
    } else {
        send_byte(client_socket, SUCH_LOGIN_ALREADY_EXISTS);
    }

    free(login);
    free(password);
}

void handle_login(int client_socket) {
    char *login = receive_bytes(client_socket);
    char *password = receive_bytes(client_socket);

    sqlite3 *db = db_open();
    id_t user_id = db_get_user_id_by_login(db, login);
    char *found_password = db_get_password_by_id(db, user_id);
    db_close(db);

    if (found_password != NULL) {
        if (strcmp(password, found_password) == 0) {
            t_package package = create_package(2);
            pack_byte(SUCCESSFUL_LOGIN, &package);
            pack_uint32(user_id, &package);
            send_and_free_package(client_socket, &package);
        } else {
            send_byte(client_socket, WRONG_PASSWORD);
        }
    } else {
        send_byte(client_socket, SUCH_LOGIN_DOES_NOT_EXIST);
    }

    free(login);
    free(password);
    free(found_password);
}
