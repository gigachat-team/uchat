#pragma once

#include "../../utils/inc/base_includes.h"
#include "../../resources/libraries/sqlite3/sqlite3.h"

#define DATABASE_NAME "uchat.db"
#define SQLITE_COMMAND_SIZE 500

#define USERS_TABLE_NAME "Users"
#define USER_ID_NAME "Id"
#define USER_LOGIN_NAME "Login"
#define USER_PASSWORD_NAME "Password"

#define CHAT_TABLE_NAME "chat"
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

sqlite3 *open_database();
<<<<<<< HEAD

/*
    users table
*/

=======
void close_database(sqlite3 *database);
>>>>>>> 88c9c2417003f57344d47067a3fda8d501b63a77
void create_users_table(sqlite3 *database);
int insert_to_users_table(sqlite3 *database, char *login, char *password);
int get_password_by_login_in_users_table(sqlite3 *database, const char *login, char **password);

/*
    chat table
*/

void create_chat_table(sqlite3 *database);
int insert_into_chat_table(sqlite3 *database, char *chat_name, int user_id);

/*
    party table
*/

void create_party_table(sqlite3 *database);

/*
    messages table
*/

void create_messages_table(sqlite3 *database);

/*
    messages statuses table
*/

void create_messages_statuses_table(sqlite3 *database);
char *get_current_date(sqlite3 *database);

