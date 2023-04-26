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

    sqlite3 *db = db_open();
    list_t *chats_list = db_select_chats_by_member_id(db, user_id);
    db_close(db);

    t_package package = create_package(1 + chats_list->len * 3);
    pack_uint32(chats_list->len, &package);
    for (list_node_t *i = chats_list->head; i != NULL; i = i->next) {
        t_chat *chat = i->val;
        pack_uint32(chat->id, &package);
        pack_bytes(chat->name, &package);
        pack_uint32(chat->owner_id, &package);
    }
    send_and_free_package(client_socket, &package);

    free_chats_list(chats_list);
}
