#include "request_handlers.h"

void handle_registration(int client_socket) {
    char *login = receive_bytes(client_socket);
    char *password = receive_bytes(client_socket);

    if (strcmp(login, DELETED_ACCOUNT_NAME) == 0) {
        send_byte(client_socket, SUCH_LOGIN_ALREADY_EXISTS);
    } else {
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
    }

    free(login);
    free(password);
}

void handle_login(int client_socket) {
    char *login = receive_bytes(client_socket);
    char *password = receive_bytes(client_socket);

    if (strcmp(login, DELETED_ACCOUNT_NAME) == 0) {
        send_byte(client_socket, SUCH_LOGIN_DOES_NOT_EXIST);
    } else {
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
        free(found_password);
    }

    free(login);
    free(password);
}

void handle_login_changing(int client_socket) {
    uint32_t user_id = receive_uint32(client_socket);
    char *new_login = receive_bytes(client_socket);

    if (strcmp(new_login, DELETED_ACCOUNT_NAME) == 0) {
        send_byte(client_socket, SUCH_LOGIN_ALREADY_EXISTS);
    } else {
        sqlite3 *db = db_open();
        bool login_already_exists = db_change_login(db, user_id, new_login);
        db_close(db);

        if (login_already_exists) {
            send_byte(client_socket, SUCH_LOGIN_ALREADY_EXISTS);
        } else {
            send_byte(client_socket, LOGIN_SUCCESSFULLY_CHANGED);
        }
    }

    free(new_login);
}

void handle_account_deleting(int client_socket) {
    uint32_t user_id = receive_uint32(client_socket);

    sqlite3 *db = db_open();
    db_delete_account(db, user_id);
    db_close(db);
}
