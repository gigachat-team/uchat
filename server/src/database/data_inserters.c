#include "../../server.h"

id_t db_create_user(sqlite3 *db, char *login, char *password) {
    if (db_users_table_has_login(db, login)) {
        return 0;
    }

    char *sql;
    asprintf(&sql, "INSERT INTO "USERS_TABLE" ("USERS_LOGIN", "USERS_PASSWORD") \
                    VALUES ('%s', '%s');", login, password
    );
    db_execute_sql(db, sql);
    free(sql);

    sqlite3_int64 last_insert_rowid = sqlite3_last_insert_rowid(db);
    asprintf(&sql, "SELECT "USERS_ID" FROM "USERS_TABLE" \
                    WHERE rowid = %llu;", last_insert_rowid
    );
    sqlite3_stmt *statement = db_open_statement(db, sql);
    sqlite3_step(statement);
    id_t created_user_id = sqlite3_column_int(statement, 0);

    free(sql);
    db_close_statement(statement, db);

    return created_user_id;
}

id_t db_create_chat(sqlite3 *db, char *chat_name, id_t owner_id) {
    char *sql = NULL;
    asprintf(&sql, "INSERT INTO "CHATS_TABLE" ("CHATS_NAME", "CHATS_USER_ID") \
                    VALUES ('%s', '%d');", chat_name, owner_id
    );
    db_execute_sql(db, sql);
    free(sql);

    sqlite3_int64 last_insert_rowid = sqlite3_last_insert_rowid(db);
    asprintf(&sql, "SELECT "CHATS_ID" FROM "CHATS_TABLE" \
                    WHERE rowid = %llu;", last_insert_rowid
    );
    sqlite3_stmt *statement = db_open_statement(db, sql);
    sqlite3_step(statement);
    id_t created_chat_id = sqlite3_column_int(statement, 0);
    
    free(sql);
    db_close_statement(statement, db);

    return created_chat_id;
}

bool db_add_new_member_to_chat(sqlite3 *db, id_t user_id, id_t chat_id) {
    if (db_user_is_in_chat(db, user_id, chat_id)) {
        return false;
    }

    char *sql = NULL;
    asprintf(&sql, "INSERT INTO "MEMBERS_TABLE" ("MEMBERS_CHAT_ID", "MEMBERS_USER_ID") \
                    VALUES (%d, %d)", chat_id, user_id
    );
    db_execute_sql(db, sql);

    free(sql);

    return true;
}

void db_add_text_message(sqlite3 *db, id_t chat_id, id_t user_id, char *text_message) {
    char *sql = NULL;
    asprintf(&sql, "SELECT "MESSAGES_ORDER" FROM "MESSAGES_TABLE" \
                    WHERE "MESSAGES_CHAT_ID" = %d ORDER BY "MESSAGES_ORDER" DESC", chat_id);
    sqlite3_stmt *statement = db_open_statement(db, sql);
    free(sql);

    uint32_t new_message_order = sqlite3_step(statement) == SQLITE_ROW ? sqlite3_column_int(statement, 0) + 1 : 1;
    db_close_statement(statement, db);

    sql = sqlite3_mprintf("INSERT INTO "MESSAGES_TABLE" ("MESSAGES_CHAT_ID", "MESSAGES_USER_ID", "MESSAGES_CONTENT", "MESSAGES_CREATION_DATE", "MESSAGES_ORDER") \
                    VALUES (%d, %d, %Q, datetime('now'), %d)", chat_id, user_id, text_message, new_message_order);
    db_execute_sql(db, sql);
    sqlite3_free(sql);
}

