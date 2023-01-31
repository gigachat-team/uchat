#include "../../server.h"

void db_create_chat(char *chat_name, int owner_id) {
    char *sql_command = NULL;
    asprintf(&sql_command, "INSERT INTO %s (%s, %s) VALUES ('%s', '%d');",
        CHATS_TABLE_NAME, CHAT_NAME_NAME, CHAT_USER_ID_NAME, chat_name, owner_id);

    db_execute_sql(sql_command);

    free(sql_command);
}

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

t_chat *db_get_chats_by_user_id(int user_id, size_t *number_of_chats) {
    int *IDs_of_chats_user_is_in = db_get_IDs_of_chats_user_is_in(user_id,  number_of_chats);

    t_chat *descriptions_of_chats = malloc(*number_of_chats * sizeof(t_chat));

    for (size_t i = 0; i < *number_of_chats; i++) {
        descriptions_of_chats[i].id = IDs_of_chats_user_is_in[i];
        descriptions_of_chats[i].name = db_get_chat_name_by_id(IDs_of_chats_user_is_in[i]);
    }

    free(IDs_of_chats_user_is_in);

    return descriptions_of_chats;
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

