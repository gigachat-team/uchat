#include "../server.h"

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
        send_and_free_package(client_socket, package);
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
            send_and_free_package(client_socket, package);
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

void handle_chat_creation(int client_socket) {
    char *chat_name = receive_bytes(client_socket);
    id_t owner_id = receive_uint32(client_socket);

    sqlite3 *db = db_open();
    id_t created_chat_id = db_create_chat(db, chat_name, owner_id);
    db_add_new_member_to_chat(db, owner_id, created_chat_id);
    db_close(db);

    send_uint32(client_socket, created_chat_id);

    free(chat_name);
}

void handle_getting_chats(int client_socket) {
    id_t user_id = receive_uint32(client_socket);

    size_t number_of_chats = 0;

    sqlite3 *db = db_open();
    t_chat *chats = db_get_chats_user_is_in(db, user_id, &number_of_chats);
    db_close(db);

    t_package package = create_package(1 + number_of_chats * 2);
    pack_uint32(number_of_chats, &package);
    for (size_t i = 0; i < number_of_chats; i++) {
        pack_uint32(chats[i].id, &package);
        pack_bytes(chats[i].name, &package);
    }
    send_and_free_package(client_socket, package);

    free_chats(chats, number_of_chats);
}

void handle_adding_new_member_to_chat(int client_socket) {
    id_t chat_id = receive_uint32(client_socket);
    char *member_login = receive_bytes(client_socket);

    sqlite3 *db = db_open();
    id_t user_id = db_get_user_id_by_login(db, member_login);
    bool new_member_added = db_add_new_member_to_chat(db, user_id, chat_id);
    db_close(db);

    if (new_member_added) {
        send_byte(client_socket, USER_SUCCESSFULLY_ADDED_TO_CHAT);
    } else {
        send_byte(client_socket, SUCH_USER_IS_ALREADY_IN_CHAT);
    }

    free(member_login);
}

void handle_text_message_sending(int client_socket) {
    id_t user_id = receive_uint32(client_socket);
    id_t chat_id = receive_uint32(client_socket);
    char *text_message = receive_bytes(client_socket);
    sqlite3 *db = db_open();
    db_add_text_message(db, chat_id, user_id, text_message);
    db_close(db);
    send_byte(client_socket, TEXT_MESSAGE_SENT_SUCCESSFULLY);

    free(text_message);
}

void handle_last_messages_getting(int client_socket) {
    uint16_t messages_count = receive_uint16(client_socket);
    id_t chat_id = receive_uint32(client_socket);
    uint32_t msg_number = receive_uint32(client_socket);

    size_t number_of_found = 0;

    sqlite3 *db = db_open();
    t_user_message *last_messages = db_get_last_messages(db, chat_id, msg_number, messages_count, &number_of_found);
    db_close(db);

    t_package package = create_package(1 + number_of_found * 5);
    pack_uint16(number_of_found, &package);
    for (size_t i = 0; i < number_of_found; i++) {
        pack_uint32(last_messages[i].user_id, &package);
        pack_bytes(last_messages[i].user_login, &package);
        pack_bytes(last_messages[i].bytes, &package);
        pack_bytes(last_messages[i].creation_date, &package);
        pack_uint32(last_messages[i].order_in_chat, &package);
    }
    send_and_free_package(client_socket, package);

    free_user_messages(last_messages, number_of_found);
}

void handle_removing_user_from_chat(int client_socket) {
    uint32_t user_id = receive_uint32(client_socket);
    uint32_t chat_id = receive_uint32(client_socket);

    sqlite3 *db = db_open();
    db_remove_user_from_chat(db, user_id, chat_id);
    db_close(db);

    send_byte(client_socket, USER_REMOVED_FROM_CHAT_SUCCESSFULLY);
}

void handle_getting_chat_members(int client_socket) {
    uint32_t chat_id = receive_uint32(client_socket);

    size_t members_count = 0;

    sqlite3 *db = db_open();
    t_user *members = db_get_chat_members(db, chat_id, &members_count);
    db_close(db);

    t_package package = create_package(1 + members_count * 2);
    pack_uint32(members_count, &package);
    for (size_t i = 0; i < members_count; i++) {
        pack_uint32(members[i].id, &package);
        pack_bytes(members[i].login, &package);
    }
    send_and_free_package(client_socket, package);

    free_users(members, members_count);
}

