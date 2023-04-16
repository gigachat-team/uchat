#include "request_handlers.h"

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

static void send_messages_list(int client_socket, list_t *messages_list) {
    t_package package = create_package(1 + messages_list->len * 5);
    pack_uint32(messages_list->len, &package);
    for (list_node_t *i = messages_list->head; i != NULL; i = i->next) {
        t_user_message *user_message = (t_user_message *)i->val;
        pack_uint32(user_message->message_id, &package);
        pack_uint32(user_message->sender_id, &package);
        pack_bytes(user_message->sender_login, &package);
        pack_bytes(user_message->data, &package);
        pack_bytes(user_message->creation_date, &package);
    }
    send_and_free_package(client_socket, &package);
}

void handle_messages_in_chat_getting(int client_socket) {
    uint32_t chat_id = receive_uint32(client_socket);

    sqlite3 *db = db_open();
    list_t *messages_list = db_select_messages(db, chat_id);
    db_close(db);

    send_messages_list(client_socket, messages_list);

    free_user_messages_list(messages_list);
}

void handle_message_sending_and_messages_updates_getting(int client_socket) {
    id_t user_id = receive_uint32(client_socket);
    id_t chat_id = receive_uint32(client_socket);
    char *data = receive_bytes(client_socket);
    t_uint32_array all_message_IDs_array = allocate_uint32_array(receive_uint32(client_socket));
    for (size_t i = 0; i < all_message_IDs_array.size; i++) {
        all_message_IDs_array.arr[i] = receive_uint32(client_socket);
    }

    sqlite3 *db = db_open();
    db_add_text_message(db, chat_id, user_id, data);
    list_t *message_updates_list = db_select_message_updates(db, chat_id, &all_message_IDs_array, true);
    db_close(db);

    send_message_updates_list(client_socket, message_updates_list);

    free(data);
    free(all_message_IDs_array.arr);
    free_message_updates_list(message_updates_list);
}

void handle_message_deleting_and_messages_updates_getting(int client_socket) {
    uint32_t message_id = receive_uint32(client_socket);
    uint32_t chat_id = receive_uint32(client_socket);
    t_uint32_array present_message_IDs_array = allocate_uint32_array(receive_uint32(client_socket));
    for (size_t i = 0; i < present_message_IDs_array.size; i++) {
        present_message_IDs_array.arr[i] = receive_uint32(client_socket);
    }

    sqlite3 *db = db_open();
    db_delete_message(db, message_id);
    list_t *message_updates_list = db_select_message_updates(db, chat_id, &present_message_IDs_array, false);
    db_close(db);

    send_message_updates_list(client_socket, message_updates_list);

    free(present_message_IDs_array.arr);
    free_message_updates_list(message_updates_list);
}

void handle_message_updates_getting(int client_socket) {
    id_t chat_id = receive_uint32(client_socket);
    t_uint32_array all_message_IDs_array = allocate_uint32_array(receive_uint32(client_socket));
    for (size_t i = 0; i < all_message_IDs_array.size; i++) {
        all_message_IDs_array.arr[i] = receive_uint32(client_socket);
    }

    sqlite3 *db = db_open();
    list_t *message_updates_list = db_select_message_updates(db, chat_id, &all_message_IDs_array, false);
    db_close(db);

    send_message_updates_list(client_socket, message_updates_list);

    free(all_message_IDs_array.arr);
    free_message_updates_list(message_updates_list);
}
