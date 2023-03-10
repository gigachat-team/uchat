#include "../../server.h"

void db_remove_user_from_chat(sqlite3 *db, id_t user_id, id_t chat_id) {
    char *sql = sqlite3_mprintf(" \
        DELETE FROM "MEMBERS_TABLE" \
        WHERE "MEMBERS_USER_ID" = %u AND "MEMBERS_CHAT_ID" = %u",
        user_id, chat_id
    );
    db_execute_sql(db, sql);
    sqlite3_free(sql);
}

