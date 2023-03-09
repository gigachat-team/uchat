#pragma once

#include "../utils/utils.h"
#include "../resources/libraries/sqlite3/sqlite3.h"

#define DATABASE_NAME "uchat.db"

#define USERS_TABLE "Users"
#define USERS_ID "Id"
#define USERS_LOGIN "Login"
#define USERS_PASSWORD "Password"

#define CHATS_TABLE "Chats"
#define CHATS_ID "Id"
#define CHATS_NAME "Name"
#define CHATS_USER_ID "UserId"

#define MEMBERS_TABLE "Members"
#define MEMBERS_CHAT_ID "ChatId"
#define MEMBERS_USER_ID "UserId"

#define MESSAGES_TABLE "Messages"
#define MESSAGES_ID "Id"
#define MESSAGES_CHAT_ID "ChatId"
#define MESSAGES_USER_ID "UserId"
#define MESSAGES_CONTENT "Content"
#define MESSAGES_CREATION_DATE "CreationDate"
#define MESSAGES_ORDER "OrderInChat"

#define MESSAGE_STATUSES_TABLE "MessageStatuses"
#define MESSAGE_STATUSES_MESSAGE_ID "MessageId"
#define MESSAGE_STATUSES_USER_ID "UserId"
#define MESSAGE_STATUSES_IS_READ "IsRead"

typedef struct s_user_message {
    id_t user_id;
    char *user_login;
    char *bytes;
    char *creation_date;
    uint32_t order_in_chat;
} t_user_message;

void *handle_request_thread(void *client_socket_void);

void send_chat(int socket, t_chat chat);

void handle_registration(int client_socket);
void handle_login(int client_socket);
void handle_chat_creation(int client_socket);
void handle_getting_chats(int client_socket);
void handle_adding_new_member_to_chat(int client_socket);
/**
 * @brief Receives text message data from CLIENT_SOCKET, creates entry in database
 * and send response to CLIENT_SOCKET: TEXT_MESSAGE_SEND_SUCCESSFULLY for success.
*/
void handle_text_message_sending(int client_socket);
void handle_last_messages_getting(int client_socket);
void handle_removing_user_from_chat(int client_socket);
void handle_getting_chat_members(int client_socket);

/**
 * @brief Opens new database connection. Prints error and close application on error.
 * @return New sqlite3 database connection.
*/
sqlite3 *db_open();
/**
 * @brief Closes database connection. Prints error and close application on error.
*/
void db_close(sqlite3 *db);
/**
 * @brief Prepares sqlite3 statement. Prints error and close application on error.
 * @return Prepared sqlite3 statement.
*/
sqlite3_stmt *db_open_statement(sqlite3 *db, char *sql);
/**
 * @brief Finalizes sqlite3 statement. Prints error and close application on error.
*/
void db_close_statement(sqlite3_stmt *statement, sqlite3 *db);
/**
 * @brief Executes SQL command. Prints error and close application on error.
*/
void db_execute_sql(sqlite3 *db, char* sql);

void db_create_users_table(sqlite3 *db);
void db_create_chats_table(sqlite3 *db);
void db_create_members_table(sqlite3 *db);
void db_create_messages_table(sqlite3 *db);
void db_create_message_statuses_table(sqlite3 *db);

void db_remove_user_from_chat(sqlite3 *db, id_t user_id, id_t chat_id);

/**
 * @brief Creates new user in the users table with new LOGIN and PASSWORD.
 * @return Positive user id or 0 if the users table already has the user with
 * this LOGIN. 
*/
id_t db_create_user(sqlite3 *db, char *login, char *password);
id_t db_create_chat(sqlite3 *db, char *chat_name, id_t owner_id);
bool db_add_new_member_to_chat(sqlite3 *db, id_t user_id, id_t chat_id);
/**
 * @brief Creates new text message in the messages table.
*/
void db_add_text_message(sqlite3 *db, id_t chat_id, id_t user_id, char *text_message);

/**
 * @brief Searches for password by ID.
 * @return New allocated string or NULL if ID not found.
*/
char *db_get_password_by_id(sqlite3 *db, id_t id);
/**
 * @return 0 if user id didn't find by the login. Positive number if a user id found
*/
id_t db_get_user_id_by_login(sqlite3 *db, char *login);
char *db_get_user_login_by_id(sqlite3 *db, id_t user_id);
char *db_get_chat_name_by_id(sqlite3 *db, id_t chat_id);
id_t *db_get_IDs_of_chats_user_is_in(sqlite3 *db, id_t user_id, size_t *IDs_of_chats_len);
t_chat *db_get_chats_user_is_in(sqlite3 *db, id_t user_id, size_t *number_of_chats);
/**
 * @brief Searches COUNT messages from LAST_MESSAGE_ORDER by CHAT_ID in messages table.
 * Number of found messages writes to NUMBER_OF_FOUND variable.
 *
 * Examples:
 * 1) There're 50 messages in chat;
 * db_get_last_messages(db, id, 25, 6, number_of_found) will return messages with orders:
 * 25, 24, 23, 22, 21, 20;
 *
 * 2) There're 100 messages in chat;
 * db_get_last_messages(db, id, UINT32_MAX, 6, number_of_found) will return messages with orders:
 * 100, 99, 98, 97, 96, 95.
 * @return Allocated array of messages
*/
t_user_message *db_get_last_messages(sqlite3 *db, id_t chat_id, uint32_t last_message_order, size_t count, size_t *number_of_found);
/**
 * @brief Searches for members in chat by CHAT_ID. Number of found members writes to
 * MEMBERS_COUNT variable.
 * @return Allocated array of members.
*/
t_user *db_get_chat_members(sqlite3 *db, id_t chat_id, size_t *members_count);

/**
 * @return false if such login does not exist or true if exists
*/
bool db_users_table_has_login(sqlite3 *db, char *login);
bool db_user_is_in_chat(sqlite3 *db, id_t user_id, id_t chat_id);

/**
 * @return nothing but turns server into the daemon state
*/
void daemon_server();

void free_user_message(t_user_message message);
void free_user_messages(t_user_message *messages, size_t length);
