#include "../server.h"

void create_users_table(sqlite3 *database) {
    char sql_command[SQLITE_COMMAND_SIZE];
    sprintf(sql_command,    "CREATE TABLE IF NOT EXISTS %s ( \
                                %s INTEGER PRIMARY KEY AUTOINCREMENT, \
                                %s TEXT UNIQUE NOT NULL CHECK(%s != ''), \
                                %s TEXT NOT NULL);",
    USERS_TABLE_NAME, USER_ID_NAME, USER_LOGIN_NAME, USER_LOGIN_NAME, USER_PASSWORD_NAME);
    
    if (sqlite3_exec(database, sql_command, NULL, NULL, NULL) != SQLITE_OK) {
        fprintf(stderr, "Failed to create users table.\n");
        close_database(database);
        exit(EXIT_FAILURE);
    }
}

int insert_to_users_table(sqlite3 *database, char *login, char *password) {
    char sql_command[300];
    sprintf(sql_command, "INSERT INTO %s (%s, %s) VALUES ('%s', '%s');", USERS_TABLE_NAME, USER_LOGIN_NAME, USER_PASSWORD_NAME, login, password);
    char *error_message; // for debug
    return sqlite3_exec(database, sql_command, NULL, NULL, &error_message);
}

int get_password_by_login_in_users_table(sqlite3 *database, const char *login, char **password) {
    char sql_command[300];
    sprintf(sql_command, "SELECT %s FROM %s WHERE %s = '%s'", USER_PASSWORD_NAME, USERS_TABLE_NAME, USER_LOGIN_NAME, login);

    sqlite3_stmt *sqlite3_statement;

    if (sqlite3_prepare_v2(database, sql_command, -1, &sqlite3_statement, 0) != SQLITE_OK) {
        printf("sqlite3_prepare_v2 error: %s\n", sqlite3_errmsg(database));
        close_database(database);
        exit(EXIT_FAILURE);
    }

    if (sqlite3_step(sqlite3_statement) != SQLITE_ROW) {
        int a = sqlite3_finalize(sqlite3_statement);
        (void)a;
        return SQLITE_ERROR;
    }

    *password = mx_strdup((char *)sqlite3_column_text(sqlite3_statement, 0));

    return sqlite3_finalize(sqlite3_statement);
}

