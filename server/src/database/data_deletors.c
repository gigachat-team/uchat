#include "../../server.h"

void db_remove_user_from_chat(sqlite3 *db, id_t user_id, id_t chat_id) {
    char *sql = NULL;
    asprintf(&sql, "DELETE FROM "MEMBERS_TABLE" \
        WHERE "MEMBERS_USER_ID" = %d AND "MEMBERS_CHAT_ID" = %d", user_id, chat_id);
    db_execute_sql(db, sql);
    free(sql);
}

