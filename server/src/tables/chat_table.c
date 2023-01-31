#include "../../server.h"

void db_create_chats_table() {
    char *sql_command;
    asprintf(&sql_command, "CREATE TABLE IF NOT EXISTS %s ( \
                                %s INTEGER PRIMARY KEY AUTOINCREMENT, \
                                %s TEXT, \
                                %s INTEGER);",
        CHATS_TABLE_NAME,
        CHAT_ID_NAME,
        CHAT_NAME_NAME,
        CHAT_USER_ID_NAME
    );

    db_execute_sql(sql_command);

    free(sql_command);
}

void db_create_chat(char *chat_name, int owner_id) {
    char *sql_command = NULL;
    asprintf(&sql_command, "INSERT INTO %s (%s, %s) VALUES ('%s', '%d');",
        CHATS_TABLE_NAME, CHAT_NAME_NAME, CHAT_USER_ID_NAME, chat_name, owner_id);

    db_execute_sql(sql_command);

    free(sql_command);
}



char *db_get_chat_name_by_id(int chat_id) {
    char *sql_command = NULL;
    asprintf(&sql_command, "SELECT %s FROM %s WHERE %s = %d",
        CHAT_NAME_NAME, CHATS_TABLE_NAME, CHAT_ID_NAME, chat_id
    );

    sqlite3 *database = db_open();
    sqlite3_stmt *statement = db_open_statement(database, sql_command);

    free(sql_command);

    if (sqlite3_step(statement) != SQLITE_ROW) {
        db_close_statement_and_database(statement, database);
        return NULL;
    }

    char *chat_name = strdup((char *)sqlite3_column_text(statement, 0));

    db_close_statement_and_database(statement, database);

    return chat_name;
}

