#include "../../server.h"

void db_create_party_table() {
    char *sql_command;
    asprintf(&sql_command, "CREATE TABLE IF NOT EXISTS %s ( \
                                %s INTEGER, \
                                %s INTEGER, \
                                PRIMARY KEY (%s, %s), \
                                FOREIGN KEY (%s) REFERENCES %s (%s), \
                                FOREIGN KEY (%s) REFERENCES %s (%s));",
        PARTY_TABLE_NAME,
        PARTY_CHAT_ID_NAME,
        PARTY_USER_ID_NAME,
        PARTY_CHAT_ID_NAME, PARTY_USER_ID_NAME,
        PARTY_CHAT_ID_NAME, CHATS_TABLE_NAME, CHAT_ID_NAME,
        PARTY_USER_ID_NAME, CHATS_TABLE_NAME, CHAT_USER_ID_NAME
    );

    db_open_and_execute_sql(sql_command);

    free(sql_command);
}

int *db_get_IDs_of_chats_user_is_in(int user_id, size_t *IDs_of_chats_len) {
    char *sql_command = NULL;
    asprintf(&sql_command, "SELECT %s FROM %s WHERE %s = %d",
        PARTY_CHAT_ID_NAME, PARTY_TABLE_NAME, PARTY_USER_ID_NAME, user_id
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
    asprintf(&sql_command, "INSERT INTO %s (%s, %s) VALUES (%d, %d)",
        PARTY_TABLE_NAME, PARTY_CHAT_ID_NAME, PARTY_USER_ID_NAME, chat_id, user_id
    );

    db_open_and_execute_sql(sql_command);

    free(sql_command);

    return true;
}

bool db_user_is_in_chat(int user_id, int chat_id) {
    char *sql_command = NULL;
    asprintf(&sql_command, "SELECT * FROM %s WHERE %s = %d AND %s = %d",
        PARTY_TABLE_NAME, PARTY_USER_ID_NAME, user_id, PARTY_CHAT_ID_NAME, chat_id
    );

    sqlite3 *database = db_open();
    sqlite3_stmt *statement = db_open_statement(database, sql_command);

    bool user_is_in_chat = sqlite3_step(statement) == SQLITE_ROW;

    free(sql_command);
    db_close_statement_and_database(statement, database);

    return user_is_in_chat;
}

