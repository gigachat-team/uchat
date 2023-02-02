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
#define MESSAGES_ID "MessageId"
#define MESSAGES_CHAT_ID "ChatId"
#define MESSAGES_USER_ID "UserId"
#define MESSAGES_CONTEXT "Context"
#define MESSAGES_CREATION_DATE "CreationDate"

#define MESSAGE_STATUSES_TABLE "MessageStatuses"
#define MESSAGE_STATUSES_MESSAGE_ID "MessageId"
#define MESSAGE_STATUSES_USER_ID "UserId"
#define MESSAGE_STATUSES_IS_READ "IsRead"

void *accept_requests_thread(void *listening_socket_void);

t_authentication_data receive_authentication_data(int client_socket);
t_chat_creation_data receive_chat_creation_data(int client_socket);
t_new_chat_member_data receive_new_chat_memeber_data(int client_socket);

void send_chat(int socket, t_chat chat);

void handle_registration(int client_socket);
void handle_login(int client_socket);
void handle_chat_creation(int client_socket);
void handle_getting_chats(int client_socket);
void handle_adding_new_member_to_chat(int client_socket);

sqlite3 *db_open();
void db_close(sqlite3 *database);
sqlite3_stmt *db_open_statement(sqlite3 *database, char *sql_command);
void db_close_statement(sqlite3_stmt *sqlite3_statement, sqlite3 *database);
void db_close_statement_and_database(sqlite3_stmt *statement, sqlite3 *database);
void db_execute_sql(sqlite3 *database, char* sql_command);
void db_open_and_execute_sql(char *sql_command);

void db_create_users_table();
void db_create_chats_table();
void db_create_members_table();
void db_create_messages_table();
void db_create_message_statuses_table();

/**
 * @brief Creates new user in the users table with new LOGIN and PASSWORD.
 * @return Positive user id or -1 if the users table already has the user with
 * this LOGIN. 
*/
int db_create_user(char *login, char *password);
int db_create_chat(char *chat_name, int owner_id);
bool db_add_new_member_to_chat(int user_id, int chat_id);

/**
 * @brief Searches for password by ID.
 * @return New allocated string or NULL if ID not found.
*/
char *db_get_password_by_id(const int id);
/**
 * @return -1 if user id didn't find by the login. Positive number if a user id found
*/
int db_get_user_id_by_login(char *login);
char *db_get_chat_name_by_id(int chat_id);
int *db_get_IDs_of_chats_user_is_in(int user_id, size_t *IDs_of_chats_len);
t_chat *db_get_chats_user_is_in(int user_id, size_t *number_of_chats);

/**
 * @return false if such login does not exist or true if exists
*/
bool db_users_table_has_login(char *login);
bool db_user_is_in_chat(int user_id, int chat_id);

