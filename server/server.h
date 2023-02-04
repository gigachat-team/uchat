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

void *handle_request_thread(void *client_socket_void);

t_authentication_data recieve_authentication_data(int client_socket);
t_chat_creation_data recieve_chat_creation_data(int client_socket);
t_new_chat_member_data recieve_new_chat_memeber_data(int client_socket);

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
 * @return false if such login already exists or true if no errors occurred.
*/
bool db_create_user(char *login, char *password);

/**
 * @param password Found password will be written here.
 * @return false if such login does not exist or true if no errors occurred.
*/
bool db_get_password_by_login(const char *login, char **password);

/**
 * @return -1 if user id didn't find by the login. Positive number if a user id found
*/
int db_get_user_id_by_login(char *login);

/**
 * @return false if such login does not exist or true if exists
*/
bool db_users_table_has_login(char *login);

t_chat *db_get_chats_user_is_in(int user_id, size_t *number_of_chats);

char *db_get_chat_name_by_id(int chat_id);

int db_create_chat(char *chat_name, int owner_id);

int *db_get_IDs_of_chats_user_is_in(int user_id, size_t *IDs_of_chats_len);

bool db_add_new_member_to_chat(int user_id, int chat_id);

bool db_user_is_in_chat(int user_id, int chat_id);

void daemon_server();
