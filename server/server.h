#pragma once

#include "../utils/utils.h"
#include "../resources/libraries/sqlite3/sqlite3.h"

#define DATABASE_NAME "uchat.db"

#define USERS_TABLE_NAME "Users"
#define USER_ID_NAME "Id"
#define USER_LOGIN_NAME "Login"
#define USER_PASSWORD_NAME "Password"

#define CHATS_TABLE_NAME "chat"
#define CHAT_ID_NAME "chat_id"
#define CHAT_NAME_NAME "name"
#define CHAT_USER_ID_NAME "user_id"

#define PARTY_TABLE_NAME "party"
#define PARTY_CHAT_ID_NAME "chat_id"
#define PARTY_USER_ID_NAME "user_id"

#define MESSAGES_TABLE_NAME "messages"
#define MESSAGES_ID_NAME "message_id"
#define MESSAGES_CHAT_ID_NAME "chat_id"
#define MESSAGES_USER_ID_NAME "user_id"
#define MESSAGES_CONTEXT_NAME "context"
#define MESSAGES_DATE_NAME "message_date"

#define MESSAGES_STATUSES_TABLE_NAME "messages_statuses"
#define MESSAGES_STATUSES_MESSAGES_ID_NAME "messages_id"
#define MESSAGES_STATUSES_USER_ID_NAME "user_id"
#define MESSAGES_STATUSES_IS_READ_NAME "is_read"

void *accept_requests_thread(void *listening_socket_void);

t_authentication_data recieve_authentication_data(int socket);
t_chat_creation_data recieve_chat_creation_data(int socket);

void handle_registration(int client_socket);
void handle_login(int client_socket);
void handle_chat_creation(int client_socket);

sqlite3 *db_open();
sqlite3_stmt *db_open_statement(sqlite3 *database, char *sql_command);

/**
 * @brief Executes sql command. It opens and closes database inside.
*/
void db_execute_sql(char *sql_command);

void db_close(sqlite3 *database);
void db_close_statement(sqlite3_stmt *sqlite3_statement, sqlite3 *database);
void db_close_statement_and_database(sqlite3_stmt *statement, sqlite3 *database);

/**
 * @brief Creates users table if not exists.
*/
void db_create_users_table();

/**
 * @return false if such login already exists or true if no errors occurred.
*/
bool db_create_user(char *login, char *password);

/**
 * @param password Found password will be written here.
 * @return false if such login does not exist or true if no errors occurred.
*/
bool db_get_password_by_login(const char *login, char **password);

/**
 * @param user_id Found user id will be written here.
 * @return false if such login does not exist or true if no errors occurred.
*/
bool db_get_user_id_by_login(char *login, int *user_id);

/**
 * @return false if such login does not exist or true if exists
*/
bool db_users_table_has_login(char *login);

void db_create_chats_table();

void db_create_chat(char *chat_name, int owner_id);

void db_create_party_table();

void db_create_messages_table();

void db_create_message_statuses_table();
char *get_current_date(sqlite3 *database);
