#include "database.h"

id_t db_create_user(sqlite3 *db, char *login, char *password) {
    if (db_login_exists(db, login)) {
        return 0;
    }

    char *sql = sqlite3_mprintf(" \
        INSERT INTO "USERS_TABLE" ("USERS_LOGIN", "USERS_PASSWORD") \
        VALUES (%Q, %Q);", login, password
    );
    db_execute_sql(db, sql);
    sqlite3_free(sql);

    sqlite3_int64 last_insert_rowid = sqlite3_last_insert_rowid(db);
    sql = sqlite3_mprintf(" \
        SELECT "USERS_ID" FROM "USERS_TABLE" \
        WHERE rowid = %llu;", last_insert_rowid
    );
    sqlite3_stmt *statement = db_open_statement(db, sql);
    sqlite3_step(statement);
    id_t created_user_id = sqlite3_column_int(statement, 0);

    sqlite3_free(sql);
    db_close_statement(statement, db);

    return created_user_id;
}

bool db_change_login(sqlite3 *db, id_t user_id, char *new_login) {
    if (db_login_exists(db, new_login)) {
        return false;
    }

    char *sql = sqlite3_mprintf(" \
        UPDATE "USERS_TABLE" \
        SET "USERS_LOGIN" = %Q \
        WHERE "USERS_ID" = %u", new_login, user_id
    );
    db_execute_sql(db, sql);
    sqlite3_free(sql);

    return true;
}

id_t db_create_chat(sqlite3 *db, char *chat_name, id_t owner_id) {
    char *sql = sqlite3_mprintf(" \
        INSERT INTO "CHATS_TABLE" ("CHATS_NAME", "CHATS_OWNER_ID") \
        VALUES (%Q, %u);", chat_name, owner_id
    );
    db_execute_sql(db, sql);
    sqlite3_free(sql);

    sqlite3_int64 last_insert_rowid = sqlite3_last_insert_rowid(db);
    sql = sqlite3_mprintf(" \
        SELECT "CHATS_ID" FROM "CHATS_TABLE" \
        WHERE rowid = %llu;", last_insert_rowid
    );
    sqlite3_stmt *statement = db_open_statement(db, sql);
    sqlite3_step(statement);
    id_t created_chat_id = sqlite3_column_int(statement, 0);

    sqlite3_free(sql);
    db_close_statement(statement, db);

    return created_chat_id;
}

bool db_add_new_member_to_chat(sqlite3 *db, id_t user_id, id_t chat_id) {
    if (db_user_is_in_chat(db, user_id, chat_id)) {
        return false;
    }

    char *sql = sqlite3_mprintf(" \
        INSERT INTO "MEMBERS_TABLE" ("MEMBERS_CHAT_ID", "MEMBERS_USER_ID") \
        VALUES (%u, %u)", chat_id, user_id
    );
    db_execute_sql(db, sql);

    sqlite3_free(sql);

    return true;
}

void db_add_text_message(sqlite3 *db, id_t chat_id, id_t user_id, char *text_message) {
    char *sql = sqlite3_mprintf(" \
        INSERT INTO "MESSAGES_TABLE" \
        ("MESSAGES_CHAT_ID", "MESSAGES_USER_ID", "MESSAGES_CONTENT", "MESSAGES_CREATION_DATE") \
        VALUES (%u, %u, %Q, strftime('%%s', 'now'))",
        chat_id, user_id, text_message
    );
    db_execute_sql(db, sql);
    sqlite3_free(sql);
}

void db_change_message(sqlite3 *db, id_t message_id, char *new_content) {
    char *sql = sqlite3_mprintf(" \
        UPDATE "MESSAGES_TABLE" \
        SET "MESSAGES_CONTENT" = %Q, "MESSAGES_CHANGES_COUNT" = "MESSAGES_CHANGES_COUNT" + 1 \
        WHERE "MESSAGES_ID" = %u", new_content, message_id
    );
    db_execute_sql(db, sql);
    sqlite3_free(sql);
}

void db_mark_account_as_deleted(sqlite3 *db, id_t user_id) {
    char *sql = sqlite3_mprintf(" \
        UPDATE "USERS_TABLE" \
        SET "USERS_LOGIN" = \"Deleted Account\" \
        WHERE "USERS_ID" = %u", user_id
    );
    db_execute_sql(db, sql);
    sqlite3_free(sql);
}
