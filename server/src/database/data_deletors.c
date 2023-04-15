#include "database.h"

void db_delete_member(sqlite3 *db, id_t user_id, id_t chat_id) {
    char *sql = sqlite3_mprintf(" \
        DELETE FROM "MEMBERS_TABLE" \
        WHERE "MEMBERS_USER_ID" = %u AND "MEMBERS_CHAT_ID" = %u",
        user_id, chat_id
    );
    db_execute_sql(db, sql);
    sqlite3_free(sql);
}

void db_delete_message(sqlite3 *db, id_t message_id) {
    char *sql = sqlite3_mprintf(" \
        DELETE FROM "MESSAGES_TABLE" \
        WHERE "MESSAGES_ID" = %u", message_id
    );
    db_execute_sql(db, sql);
    sqlite3_free(sql);
}
