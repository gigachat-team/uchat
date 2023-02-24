#include "../../server.h"

bool db_users_table_has_login(sqlite3 *db, char *login) {
    char *sql = NULL;
    asprintf(&sql, "SELECT * FROM "USERS_TABLE" \
                    WHERE "USERS_LOGIN" = '%s'", login
    );

    sqlite3_stmt *statement = db_open_statement(db, sql);

    bool has_login = sqlite3_step(statement) == SQLITE_ROW;

    free(sql);
    db_close_statement(statement, db);

    return has_login;
}

bool db_user_is_in_chat(sqlite3 *db, id_t user_id, id_t chat_id) {
    char *sql = NULL;
    asprintf(&sql, "SELECT * FROM "MEMBERS_TABLE" \
        WHERE "MEMBERS_USER_ID" = %d AND "MEMBERS_CHAT_ID" = %d", user_id, chat_id
    );

    sqlite3_stmt *statement = db_open_statement(db, sql);

    bool user_is_in_chat = sqlite3_step(statement) == SQLITE_ROW;

    free(sql);
    db_close_statement(statement, db);

    return user_is_in_chat;
}

