#include "../inc/database.h"

void create_party_table(sqlite3 *database) {
    char sql_command[SQLITE_COMMAND_SIZE];

    sprintf(sql_command, "CREATE TABLE IF NOT EXISTS %s (\
        %s INTEGER, \
        %s INTEGER, \
        FOREIGN KEY (%s) REFERENCES %s (%s), \
        FOREIGN KEY (%s) REFERENCES %s (%s));",
        
        PARTY_TABLE_NAME,
        PARTY_CHAT_ID_NAME,
        PARTY_USER_ID_NAME,
        PARTY_CHAT_ID_NAME,
        CHAT_TABLE_NAME,
        CHAT_ID_NAME,
        PARTY_USER_ID_NAME,
        CHAT_TABLE_NAME,
        CHAT_USER_ID_NAME
    );
    
    if (sqlite3_exec(database, sql_command, NULL, NULL, NULL) != SQLITE_OK) {
        fprintf(stderr, "Failed to create/open party table.\n");
        sqlite3_close(database);
        exit(EXIT_FAILURE);
    }
}
