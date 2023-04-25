#include "database.h"

void db_delete_chat(sqlite3 *db, id_t chat_id) {
    char *sql = sqlite3_mprintf(" \
        "ENABLE_FOREIGN_KEYS_SUPPORT" \
        DELETE FROM "CHATS_TABLE" \
        WHERE "CHATS_ID" = %u", chat_id
    );
    db_execute_sql(db, sql);
}

void db_delete_member(sqlite3 *db, id_t user_id, id_t chat_id) {
    char *sql = sqlite3_mprintf(" \
        DELETE FROM "MEMBERS_TABLE" \
        WHERE "MEMBERS_USER_ID" = %u AND "MEMBERS_CHAT_ID" = %u",
        user_id, chat_id
    );
    db_execute_sql(db, sql);
    sqlite3_free(sql);

    if(!db_chat_has_members(db, chat_id)) {
        db_delete_chat(db, chat_id);
    }
}

void db_delete_message(sqlite3 *db, id_t message_id) {
    char *sql = sqlite3_mprintf(" \
        DELETE FROM "MESSAGES_TABLE" \
        WHERE "MESSAGES_ID" = %u", message_id
    );
    db_execute_sql(db, sql);
    sqlite3_free(sql);
}

void db_delete_account(sqlite3 *db, id_t user_id) {
    char *sql = sqlite3_mprintf(" \
        UPDATE "USERS_TABLE" \
        SET "USERS_LOGIN" = \"%Q\" \
        WHERE "USERS_ID" = %u", DELETED_ACCOUNT_NAME, user_id
    );
    db_execute_sql(db, sql);
    sqlite3_free(sql);

    sql = sqlite3_mprintf(" \
        DELETE FROM "MEMBERS_TABLE" \
        WHERE "MEMBERS_USER_ID" = %u", user_id
    );
    db_execute_sql(db, sql);
    sqlite3_free(sql);
}
