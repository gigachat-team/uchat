#include "../../server.h"

id_t db_create_user(sqlite3 *db, char *login, char *password) {
    if (db_users_table_has_login(db, login)) {
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

id_t db_create_chat(sqlite3 *db, char *chat_name, id_t owner_id) {
    char *sql = sqlite3_mprintf(" \
        INSERT INTO "CHATS_TABLE" ("CHATS_NAME", "CHATS_USER_ID") \
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
        SELECT "MESSAGES_ORDER" FROM "MESSAGES_TABLE" \
        WHERE "MESSAGES_CHAT_ID" = %d ORDER BY "MESSAGES_ORDER" DESC", chat_id
    );
    sqlite3_stmt *statement = db_open_statement(db, sql);
    sqlite3_free(sql);

    uint32_t new_message_order = sqlite3_step(statement) == SQLITE_ROW ? sqlite3_column_int(statement, 0) + 1 : 1;
    db_close_statement(statement, db);

    sql = sqlite3_mprintf(" \
        INSERT INTO "MESSAGES_TABLE" ("MESSAGES_CHAT_ID", "MESSAGES_USER_ID", "MESSAGES_CONTENT", \
                                      "MESSAGES_CREATION_DATE", "MESSAGES_ORDER") \
        VALUES (%u, %u, %Q, datetime('now'), %u)",
        chat_id, user_id, text_message, new_message_order
    );
    db_execute_sql(db, sql);
    sqlite3_free(sql);
}

