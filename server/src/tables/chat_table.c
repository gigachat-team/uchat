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

