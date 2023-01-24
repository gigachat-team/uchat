#pragma once

#include "../../utils/inc/base_includes.h"
#include "../../resources/libraries/sqlite3/sqlite3.h"

#define DATABASE_NAME "uchat.db"

#define USERS_TABLE_NAME "Users"
#define USER_ID_NAME "Id"
#define USER_LOGIN_NAME "Login"
#define USER_PASSWORD_NAME "Password"

sqlite3 *open_database();
void close_database(sqlite3 *database);
void create_users_table(sqlite3 *database);
int insert_to_users_table(sqlite3 *database, char *login, char *password);
int get_password_by_login_in_users_table(sqlite3 *database, const char *login, char **password);

