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

void handle_messages_in_chat_getting(int client_socket) {
    uint32_t chat_id = receive_uint32(client_socket);

    sqlite3 *db = db_open();
    list_t *messages_list = db_select_messages(db, chat_id);
    db_close(db);

    send_messages_list(client_socket, messages_list);

    free_messages_list(messages_list);
}

void handle_message_sending_and_messages_updates_getting(int client_socket) {
    id_t user_id = receive_uint32(client_socket);
    id_t chat_id = receive_uint32(client_socket);
    char *data = receive_bytes(client_socket);
    t_id_and_changes_count_array client_messages = receive_id_and_changes_count_array(client_socket);

    sqlite3 *db = db_open();
    db_add_text_message(db, chat_id, user_id, data);
    list_t *message_updates_list = db_select_message_updates(db, chat_id, &client_messages, true);
    db_close(db);

    send_message_updates_list(client_socket, message_updates_list);

    free(data);
    free(client_messages.arr);
    free_message_updates_list(message_updates_list);
}

void handle_message_deleting_and_messages_updates_getting(int client_socket) {
    uint32_t message_id = receive_uint32(client_socket);
    uint32_t chat_id = receive_uint32(client_socket);
    t_id_and_changes_count_array client_messages = receive_id_and_changes_count_array(client_socket);

    sqlite3 *db = db_open();
    db_delete_message(db, message_id);
    list_t *message_updates_list = db_select_message_updates(db, chat_id, &client_messages, false);
    db_close(db);

    send_message_updates_list(client_socket, message_updates_list);

    free(client_messages.arr);
    free_message_updates_list(message_updates_list);
}

void handle_message_changing_and_message_updates_getting(int client_socket) {
    uint32_t message_id = receive_uint32(client_socket);
    char *new_message_content = receive_bytes(client_socket);
    uint32_t chat_id = receive_uint32(client_socket);
    t_id_and_changes_count_array client_messages = receive_id_and_changes_count_array(client_socket);

    sqlite3 *db = db_open();
    db_change_message(db, message_id, new_message_content);
    list_t *message_updates_list = db_select_message_updates(db, chat_id, &client_messages, false);
    db_close(db);

    send_message_updates_list(client_socket, message_updates_list);

    free(client_messages.arr);
    free_messages_list(message_updates_list);
}

void handle_message_updates_getting(int client_socket) {
    id_t chat_id = receive_uint32(client_socket);
    t_id_and_changes_count_array client_messages = receive_id_and_changes_count_array(client_socket);

    sqlite3 *db = db_open();
    list_t *message_updates_list = db_select_message_updates(db, chat_id, &client_messages, false);
    db_close(db);

    send_message_updates_list(client_socket, message_updates_list);

    free(client_messages.arr);
    free_message_updates_list(message_updates_list);
}
