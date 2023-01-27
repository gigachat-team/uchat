#include "../server.h"

int insert_into_chat_table(sqlite3 *database, char *chat_name, int user_id) {
    char sql_command[SQLITE_COMMAND_SIZE];

    sprintf(sql_command, "INSERT INTO %s (%s, %s) VALUES ('%s', '%d');", 
        CHAT_TABLE_NAME, 
        CHAT_NAME_NAME, 
        CHAT_USER_ID_NAME, 
        chat_name, 
        user_id
    );

    char *error_message; 
    return sqlite3_exec(database, sql_command, NULL, NULL, &error_message);
}

void create_chat_table(sqlite3 *database) {
    char sql_command[SQLITE_COMMAND_SIZE];

    sprintf(sql_command, "CREATE TABLE IF NOT EXISTS %s (\
        %s INTEGER PRIMARY KEY AUTOINCREMENT, \
        %s TEXT UNIQUE DEFAULT 'Undefined chat' CHECK(length(%s) >= 2), \
        %s INTEGER);",

        CHAT_TABLE_NAME, 
        CHAT_ID_NAME, 
        CHAT_NAME_NAME, 
        CHAT_NAME_NAME, 
        CHAT_USER_ID_NAME
    );
    
    if (sqlite3_exec(database, sql_command, NULL, NULL, NULL) != SQLITE_OK) {
        fprintf(stderr, "Failed to create/open chat table.\n");
        close_database(database);
        exit(EXIT_FAILURE);
    }
}

