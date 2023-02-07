#include "../../server.h"

int db_create_user(sqlite3 *db, char *login, char *password) {
    if (db_users_table_has_login(db, login)) {
        return -1;
    }

    char *sql_command;
    asprintf(&sql_command, "INSERT INTO "USERS_TABLE" ("USERS_LOGIN", "USERS_PASSWORD") \
                            VALUES ('%s', '%s');", login, password
    );
    db_execute_sql(db, sql_command);
    free(sql_command);

    sqlite3_int64 last_insert_rowid = sqlite3_last_insert_rowid(db);
    asprintf(&sql_command, "SELECT "USERS_ID" FROM "USERS_TABLE" \
                            WHERE rowid = %llu;", last_insert_rowid
    );
    sqlite3_stmt *statement = db_open_statement(db, sql_command);
    sqlite3_step(statement);
    int created_user_id = sqlite3_column_int(statement, 0);

    free(sql_command);
    db_close_statement(statement, db);

    return created_user_id;
}

int db_create_chat(sqlite3 *db, char *chat_name, int owner_id) {
    char *sql_command = NULL;
    asprintf(&sql_command, "INSERT INTO "CHATS_TABLE" ("CHATS_NAME", "CHATS_USER_ID") \
                            VALUES ('%s', '%d');", chat_name, owner_id
    );

    db_execute_sql(db, sql_command);
    free(sql_command);

    sqlite3_int64 last_insert_rowid = sqlite3_last_insert_rowid(db);
    asprintf(&sql_command, "SELECT "CHATS_ID" FROM "CHATS_TABLE" \
                            WHERE rowid = %llu;", last_insert_rowid
    );
    sqlite3_stmt *statement = db_open_statement(db, sql_command);
    sqlite3_step(statement);
    int created_chat_id = sqlite3_column_int(statement, 0);
    
    free(sql_command);
    db_close_statement(statement, db);

    return created_chat_id;
}

bool db_add_new_member_to_chat(sqlite3 *db, int user_id, int chat_id) {
    if (db_user_is_in_chat(db, user_id, chat_id)) {
        return false;
    }

    char *sql_command = NULL;
    asprintf(&sql_command, "INSERT INTO "MEMBERS_TABLE" ("MEMBERS_CHAT_ID", "MEMBERS_USER_ID") \
                            VALUES (%d, %d)", chat_id, user_id
    );

    db_execute_sql(db, sql_command);

    free(sql_command);

    return true;
}

void db_add_text_message(sqlite3 *db, uint32_t chat_id, uint32_t user_id, char *text_message) {
    char *sql_command = NULL;
    asprintf(&sql_command, "INSERT INTO "MESSAGES_TABLE" ("MESSAGES_CHAT_ID", "MESSAGES_USER_ID", "MESSAGES_CONTENT", "MESSAGES_CREATION_DATE") \
                            VALUES (%d, %d, '%s', 'implement later')", chat_id, user_id, text_message);
    db_execute_sql(db, sql_command);
    free(sql_command);
}

