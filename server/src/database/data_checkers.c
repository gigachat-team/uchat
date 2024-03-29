#include "database.h"

bool db_login_exists(sqlite3 *db, char *login) {
    char *sql = sqlite3_mprintf(" \
        SELECT * FROM "USERS_TABLE" \
        WHERE "USERS_LOGIN" = %Q", login
    );

    sqlite3_stmt *statement = db_open_statement(db, sql);

    bool has_login = sqlite3_step(statement) == SQLITE_ROW;

    sqlite3_free(sql);
    db_close_statement(statement, db);

    return has_login;
}

bool db_user_is_in_chat(sqlite3 *db, id_t user_id, id_t chat_id) {
    char *sql = sqlite3_mprintf(" \
        SELECT * FROM "MEMBERS_TABLE" \
        WHERE "MEMBERS_USER_ID" = %u AND "MEMBERS_CHAT_ID" = %u",
        user_id, chat_id
    );

    sqlite3_stmt *statement = db_open_statement(db, sql);

    bool user_is_in_chat = sqlite3_step(statement) == SQLITE_ROW;

    sqlite3_free(sql);
    db_close_statement(statement, db);

    return user_is_in_chat;
}

bool db_chat_has_members(sqlite3 *db, id_t chat_id) {
    char *sql = sqlite3_mprintf(" \
        SELECT "MEMBERS_CHAT_ID" FROM "MEMBERS_TABLE" \
        WHERE "MEMBERS_CHAT_ID" = %u", chat_id
    );
    sqlite3_stmt *statement = db_open_statement(db, sql);
    sqlite3_free(sql);
    bool chat_has_members = sqlite3_step(statement) == SQLITE_ROW;
    db_close_statement(statement, db);

    return chat_has_members;
}
