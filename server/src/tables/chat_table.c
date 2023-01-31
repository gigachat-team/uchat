#include "../../server.h"

void db_create_chats_table() {
    char *sql_command = "CREATE TABLE IF NOT EXISTS "CHATS_TABLE" ( \
                                "CHATS_ID"      INTEGER PRIMARY KEY AUTOINCREMENT, \
                                "CHATS_NAME"    TEXT, \
                                "CHATS_USER_ID" INTEGER);"
    ;

    db_open_and_execute_sql(sql_command);

}

 int db_create_chat(char *chat_name, int owner_id) {
    char *sql_command = NULL;
    asprintf(&sql_command, "INSERT INTO "CHATS_TABLE" ("CHATS_NAME", "CHATS_USER_ID") \
                            VALUES ('%s', '%d');", chat_name, owner_id
    );

    sqlite3 *database = db_open();

    db_execute_sql(database, sql_command);
    free(sql_command);

    sqlite3_int64 last_insert_rowid = sqlite3_last_insert_rowid(database);
    asprintf(&sql_command, "SELECT "CHATS_ID" FROM "CHATS_TABLE" \
                            WHERE rowid = %llu;", last_insert_rowid
    );
    sqlite3_stmt *statement = db_open_statement(database, sql_command);
    sqlite3_step(statement);
    int created_chat_id = sqlite3_column_int(statement, 0);
    
    free(sql_command);
    db_close_statement_and_database(statement, database);

    return created_chat_id;
}



char *db_get_chat_name_by_id(int chat_id) {
    char *sql_command = NULL;
    asprintf(&sql_command, "SELECT "CHATS_NAME" FROM "CHATS_TABLE" \
                            WHERE "CHATS_ID" = %d", chat_id
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

