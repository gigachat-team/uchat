#include "../../server.h"

void db_create_message_statuses_table() {
    char *sql_command;
    asprintf(&sql_command, "CREATE TABLE IF NOT EXISTS %s (\
                            %s INTEGER, \
                            %s INTEGER, \
                            %s INTEGER NOT NULL);",
        MESSAGES_STATUSES_TABLE_NAME,
        MESSAGES_STATUSES_MESSAGES_ID_NAME,
        MESSAGES_STATUSES_USER_ID_NAME,
        MESSAGES_STATUSES_IS_READ_NAME
    );
    db_execute_sql(sql_command);

    free(sql_command);
}

