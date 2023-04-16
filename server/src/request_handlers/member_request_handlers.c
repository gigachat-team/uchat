#include "request_handlers.h"

void handle_adding_new_member_to_chat(int client_socket) {
    id_t chat_id = receive_uint32(client_socket);
    char *member_login = receive_bytes(client_socket);

    sqlite3 *db = db_open();
    id_t user_id = db_get_user_id_by_login(db, member_login);
    bool new_member_added = false;
    if (user_id != 0)
        new_member_added = db_add_new_member_to_chat(db, user_id, chat_id);
    db_close(db);

    if (user_id == 0) {
        send_byte(client_socket, SUCH_LOGIN_DOES_NOT_EXIST);
    } else if (new_member_added) {
        send_byte(client_socket, USER_SUCCESSFULLY_ADDED_TO_CHAT);
    } else {
        send_byte(client_socket, SUCH_USER_IS_ALREADY_IN_CHAT);
    }

    free(member_login);
}

void handle_getting_chat_members(int client_socket) {
    uint32_t chat_id = receive_uint32(client_socket);

    sqlite3 *db = db_open();
    list_t *members_list = db_select_members(db, chat_id);
    db_close(db);

    t_package package = create_package(1 + members_list->len * 2);
    pack_uint32(members_list->len, &package);
    for (list_node_t *i = members_list->head; i != NULL; i = i->next) {
        t_user *member = (t_user *)i->val;
        pack_uint32(member->id, &package);
        pack_bytes(member->login, &package);
    }
    send_and_free_package(client_socket, &package);

    free_users_list(members_list);
}

void handle_removing_user_from_chat(int client_socket) {
    uint32_t user_id = receive_uint32(client_socket);
    uint32_t chat_id = receive_uint32(client_socket);

    sqlite3 *db = db_open();
    db_delete_member(db, user_id, chat_id);
    db_close(db);

    send_byte(client_socket, USER_REMOVED_FROM_CHAT_SUCCESSFULLY);
}
