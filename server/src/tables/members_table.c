#include "../../server.h"

void db_create_members_table() {
    char *sql_command = "CREATE TABLE IF NOT EXISTS "MEMBERS_TABLE" ( \
        "MEMBERS_CHAT_ID" INTEGER, \
        "MEMBERS_USER_ID" INTEGER, \
        PRIMARY KEY ("MEMBERS_CHAT_ID", "MEMBERS_USER_ID"), \
        FOREIGN KEY ("MEMBERS_CHAT_ID") REFERENCES "CHATS_TABLE" ("CHATS_ID"), \
        FOREIGN KEY ("MEMBERS_USER_ID") REFERENCES "CHATS_TABLE" ("CHATS_USER_ID"));"
    ;

    db_open_and_execute_sql(sql_command);
}

int *db_get_IDs_of_chats_user_is_in(int user_id, size_t *IDs_of_chats_len) {
    char *sql_command = NULL;
    asprintf(&sql_command, "SELECT "MEMBERS_CHAT_ID" FROM "MEMBERS_TABLE" \
                            WHERE "MEMBERS_USER_ID" = %d", user_id
    );

    sqlite3 *database = db_open();
    sqlite3_stmt *statement = db_open_statement(database, sql_command);

    *IDs_of_chats_len = 0;
    int *IDs_of_chats = NULL;
    while (sqlite3_step(statement) == SQLITE_ROW) {
        IDs_of_chats = realloc(IDs_of_chats, sizeof(int) * ++(*IDs_of_chats_len));
        IDs_of_chats[*IDs_of_chats_len - 1] = sqlite3_column_int(statement, 0);
    }

    db_close_statement_and_database(statement, database);
    free(sql_command);

    return IDs_of_chats;
}

bool db_add_new_member_to_chat(int user_id, int chat_id) {
    if (db_user_is_in_chat(user_id, chat_id)) {
        return false;
    }

    char *sql_command = NULL;
    asprintf(&sql_command, "INSERT INTO "MEMBERS_TABLE" ("MEMBERS_CHAT_ID", "MEMBERS_USER_ID") \
                            VALUES (%d, %d)", chat_id, user_id
    );

    db_open_and_execute_sql(sql_command);

    free(sql_command);

    return true;
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

