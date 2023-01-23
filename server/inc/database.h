#pragma once

#include "../../utils/inc/base_includes.h"
#include "../../resources/libraries/sqlite3/sqlite3.h"

#define DATABASE_NAME "uchat.db"

#define USERS_TABLE_NAME "Users"
#define USER_ID_NAME "Id"
#define USER_LOGIN_NAME "Login"
#define USER_PASSWORD_NAME "Password"

#define USERS_TABLE_CREATION_SQL    "CREATE TABLE IF NOT EXISTS " USERS_TABLE_NAME " (" \
                                        USER_ID_NAME         " INTEGER PRIMARY KEY AUTOINCREMENT," \
                                        USER_LOGIN_NAME      " TEXT UNIQUE NOT NULL CHECK(" USER_LOGIN_NAME "!= '')," \
                                        USER_PASSWORD_NAME   " TEXT NOT NULL" \
                                    ");"

sqlite3 *open_database();
int insert_to_users_table(sqlite3 *database, char *login, char *password);
int get_password_by_login_in_users_table(sqlite3 *database, const char *login, char **password);

