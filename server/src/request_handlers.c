#include "../server.h"

void handle_registration(int client_socket) {
    char *login = receive_string(client_socket);
    char *password = receive_string(client_socket);

    sqlite3 *db = db_open();
    id_t user_id = db_create_user(db, login, password);
    db_close(db);

    if (user_id != 0) {
        send_unsigned_char(client_socket, SUCCESSFUL_REGISTRATION);
        send_unsigned_int(client_socket, user_id);
    } else {
        send_unsigned_char(client_socket, SUCH_LOGIN_ALREADY_EXISTS);
    }
}

void handle_login(int client_socket) {
    char *login = receive_string(client_socket);
    char *password = receive_string(client_socket);

    sqlite3 *db = db_open();
    id_t user_id = db_get_user_id_by_login(db, login);
    char *found_password = db_get_password_by_id(db, user_id);
    db_close(db);

    if (found_password != NULL) {
        if (strcmp(password, found_password) == 0) {
            send_unsigned_char(client_socket, SUCCESSFUL_LOGIN);
            send_unsigned_int(client_socket, user_id);
        } else {
            send_unsigned_char(client_socket, WRONG_PASSWORD);
        }
    } else {
        send_unsigned_char(client_socket, SUCH_LOGIN_DOES_NOT_EXIST);
    }

    free(found_password);
}

void handle_chat_creation(int client_socket) {
    char *chat_name = receive_string(client_socket);
    id_t owner_id = receive_unsigned_int(client_socket);

    sqlite3 *db = db_open();
    id_t created_chat_id = db_create_chat(db, chat_name, owner_id);
    db_add_new_member_to_chat(db, owner_id, created_chat_id);
    db_close(db);

    send_unsigned_char(client_socket, CHAT_CREATED_SUCCESSFULLY);
}

void handle_getting_chats(int client_socket) {
    id_t user_id = receive_unsigned_int(client_socket);

    size_t number_of_chats = 0;

    sqlite3 *db = db_open();
    t_chat *chats = db_get_chats_user_is_in(db, user_id, &number_of_chats);
    db_close(db);

    send_unsigned_int(client_socket, number_of_chats);
    for (size_t i = 0; i < number_of_chats; i++){
        send_unsigned_int(client_socket, chats[i].id);
        send_string(client_socket, chats[i].name);
    }

    free_chats(chats, number_of_chats);
}

void handle_adding_new_member_to_chat(int client_socket) {
    id_t chat_id = receive_unsigned_int(client_socket);
    char *member_login = receive_string(client_socket);

    sqlite3 *db = db_open();
    id_t user_id = db_get_user_id_by_login(db, member_login);
    bool new_member_added = db_add_new_member_to_chat(db, user_id, chat_id);
    db_close(db);

    if (new_member_added) {
        send_unsigned_char(client_socket, USER_SUCCESSFULLY_ADDED_TO_CHAT);
    } else {
        send_unsigned_char(client_socket, SUCH_USER_IS_ALREADY_IN_CHAT);
    }
}

void handle_text_message_sending(int client_socket) {
    id_t user_id = receive_unsigned_int(client_socket);
    id_t chat_id = receive_unsigned_int(client_socket);
    char *text_message = receive_string(client_socket);
    sqlite3 *db = db_open();
    db_add_text_message(db, chat_id, user_id, text_message);
    db_close(db);
    send_unsigned_char(client_socket, TEXT_MESSAGE_SENT_SUCCESSFULLY);
}

void handle_last_messages_getting(int client_socket) {
    uint16_t messages_count = receive_unsigned_short(client_socket);
    id_t chat_id = receive_unsigned_int(client_socket);

    size_t number_of_found = 0;

    sqlite3 *db = db_open();
    t_user_message *last_messages = db_get_last_messages(db, chat_id, messages_count, &number_of_found);
    db_close(db);

    send_unsigned_short(client_socket, number_of_found);
    for (size_t i = 0; i < number_of_found; i++) {
        send_unsigned_int(client_socket, last_messages[i].user_id);
        send_string(client_socket, last_messages[i].user_login);
        send_string(client_socket, last_messages[i].bytes);
    }

    free_user_messages_array(last_messages, number_of_found);
}

