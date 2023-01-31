#include "../../server.h"

void db_create_users_table() {
    char *sql_command = NULL;
    asprintf(&sql_command,    "CREATE TABLE IF NOT EXISTS %s ( \
                                %s INTEGER PRIMARY KEY AUTOINCREMENT, \
                                %s TEXT UNIQUE NOT NULL CHECK(%s != ''), \
                                %s TEXT NOT NULL);",
    USERS_TABLE_NAME,
    USER_ID_NAME,
    USER_LOGIN_NAME, USER_LOGIN_NAME,
    USER_PASSWORD_NAME);

    db_open_and_execute_sql(sql_command);

    free(sql_command);
}

bool db_create_user(char *login, char *password) {
    if (db_users_table_has_login(login)) {
        return false;
    }

    char *sql_command;
    asprintf(&sql_command, "INSERT INTO %s (%s, %s) VALUES ('%s', '%s');",
        USERS_TABLE_NAME, USER_LOGIN_NAME, USER_PASSWORD_NAME, login, password);

    db_open_and_execute_sql(sql_command);

    free(sql_command);

    return true;
}

bool db_get_password_by_login(const char *login, char **password) {
    char *sql_command = NULL;
    asprintf(&sql_command, "SELECT %s FROM %s WHERE %s = '%s'",
        USER_PASSWORD_NAME, USERS_TABLE_NAME, USER_LOGIN_NAME, login);

    sqlite3 *database = db_open();
    sqlite3_stmt *statement = db_open_statement(database, sql_command);

    if (sqlite3_step(statement) != SQLITE_ROW) {
        db_close_statement_and_database(statement, database);
        free(sql_command);
        return false;
    }

    *password = mx_strdup((char *)sqlite3_column_text(statement, 0));
    
    db_close_statement_and_database(statement, database);
    free(sql_command);

    return true;
}

int db_get_user_id_by_login(char *login) {
    char *sql_command = NULL;
    asprintf(&sql_command, "SELECT %s FROM %s WHERE %s = '%s'",
        USER_ID_NAME, USERS_TABLE_NAME, USER_LOGIN_NAME, login);
    
    sqlite3 *database = db_open();
    sqlite3_stmt *statement = db_open_statement(database, sql_command);

    free(sql_command);

    if (sqlite3_step(statement) != SQLITE_ROW) {
        db_close_statement_and_database(statement, database);
        return -1;
    }

    int user_id = sqlite3_column_int(statement, 0);

    db_close_statement_and_database(statement, database);

    return user_id;
}

bool db_users_table_has_login(char *login) {
    char *sql_command = NULL;
    asprintf(&sql_command, "SELECT * FROM %s WHERE %s = '%s'",
        USERS_TABLE_NAME, USER_LOGIN_NAME, login);

    sqlite3 *database = db_open();
    sqlite3_stmt *statement = db_open_statement(database, sql_command);

    bool has_login = sqlite3_step(statement) == SQLITE_ROW;

    free(sql_command);
    db_close_statement_and_database(statement, database);

    return has_login;
}

