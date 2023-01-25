#include "../inc/database.h"

void create_messages_statuses_table(sqlite3 *database) {
    char sql_command[SQLITE_COMMAND_SIZE];

    sprintf(sql_command, "CREATE TABLE IF NOT EXISTS %s (\
        %s INTEGER, \
        %s INTEGER, \
        %s INTEGER NOT NULL);",

        MESSAGES_STATUSES_TABLE_NAME,

        MESSAGES_STATUSES_MESSAGES_ID_NAME,
        MESSAGES_STATUSES_USER_ID_NAME,
        MESSAGES_STATUSES_IS_READ_NAME
    );
    
    if (sqlite3_exec(database, sql_command, NULL, NULL, NULL) != SQLITE_OK) {
        fprintf(stderr, "Failed to create/open messages_statuses table.\n");
        sqlite3_close(database);
        exit(EXIT_FAILURE);
    } 
}

