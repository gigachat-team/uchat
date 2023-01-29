#include "../../server.h"

void db_create_party_table() {
    char *sql_command;
    asprintf(&sql_command, "CREATE TABLE IF NOT EXISTS %s (\
                                %s INTEGER, \
                                %s INTEGER, \
                                FOREIGN KEY (%s) REFERENCES %s (%s), \
                                FOREIGN KEY (%s) REFERENCES %s (%s));",
        PARTY_TABLE_NAME,
        PARTY_CHAT_ID_NAME,
        PARTY_USER_ID_NAME,
        PARTY_CHAT_ID_NAME, CHATS_TABLE_NAME, CHAT_ID_NAME,
        PARTY_USER_ID_NAME, CHATS_TABLE_NAME, CHAT_USER_ID_NAME
    );

    db_execute_sql(sql_command);

    free(sql_command);
}

