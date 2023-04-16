#include "request_handlers.h"

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
    send_and_free_package(client_socket, &package);

    free_chats(chats, number_of_chats);
}
