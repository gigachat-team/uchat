#include "../../server.h"

bool db_users_table_has_login(char *login) {
    char *sql_command = NULL;
    asprintf(&sql_command, "SELECT * FROM "USERS_TABLE" \
                            WHERE "USERS_LOGIN" = '%s'", login
    );

    sqlite3 *database = db_open();
    sqlite3_stmt *statement = db_open_statement(database, sql_command);

    bool has_login = sqlite3_step(statement) == SQLITE_ROW;

    free(sql_command);
    db_close_statement_and_database(statement, database);

    return has_login;
}

bool db_user_is_in_chat(int user_id, int chat_id) {
    char *sql_command = NULL;
    asprintf(&sql_command, "SELECT * FROM "MEMBERS_TABLE" \
        WHERE "MEMBERS_USER_ID" = %d AND "MEMBERS_CHAT_ID" = %d", user_id, chat_id
    );

    sqlite3 *database = db_open();
    sqlite3_stmt *statement = db_open_statement(database, sql_command);

    bool user_is_in_chat = sqlite3_step(statement) == SQLITE_ROW;

    free(sql_command);
    db_close_statement_and_database(statement, database);

    return user_is_in_chat;
}

