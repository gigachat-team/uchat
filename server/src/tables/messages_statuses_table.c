#include "../../server.h"

void db_create_message_statuses_table() {
    char *sql_command = "CREATE TABLE IF NOT EXISTS "MESSAGE_STATUSES_TABLE" ( \
                            "MESSAGE_STATUSES_MESSAGE_ID"   INTEGER, \
                            "MESSAGE_STATUSES_USER_ID"      INTEGER, \
                            "MESSAGE_STATUSES_IS_READ"      INTEGER NOT NULL);"
    ;
    
    db_open_and_execute_sql(sql_command);
}

