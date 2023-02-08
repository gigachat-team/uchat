#include "../../server.h"

char *db_get_password_by_id(sqlite3 *db, const int id) {
    char *sql = NULL;
    asprintf(&sql, "SELECT "USERS_PASSWORD" FROM "USERS_TABLE" \
                    WHERE "USERS_ID" = '%d'", id
    );

    sqlite3_stmt *statement = db_open_statement(db, sql);

    free(sql);

    if (sqlite3_step(statement) != SQLITE_ROW) {
        db_close_statement(statement, db);
        return NULL;
    }

    char *password = strdup((char *)sqlite3_column_text(statement, 0));

    db_close_statement(statement, db);

    return password;
}

int db_get_user_id_by_login(sqlite3 *db, char *login) {
    char *sql = NULL;
    asprintf(&sql, "SELECT "USERS_ID" FROM "USERS_TABLE" \
                    WHERE "USERS_LOGIN" = '%s'", login
    );
    
    sqlite3_stmt *statement = db_open_statement(db, sql);

    free(sql);

    if (sqlite3_step(statement) != SQLITE_ROW) {
        db_close_statement(statement, db);
        return -1;
    }

    int user_id = sqlite3_column_int(statement, 0);

    db_close_statement(statement, db);

    return user_id;
}

char *db_get_user_login_by_id(sqlite3 *db, int user_id) {
    char *sql = NULL;
    asprintf(&sql, "SELECT "USERS_LOGIN" FROM "USERS_TABLE" \
                    WHERE "USERS_ID" = %d", user_id);

    sqlite3_stmt *statement = db_open_statement(db, sql);

    free(sql);

    if (sqlite3_step(statement) != SQLITE_ROW) {
        db_close_statement(statement, db);
        return NULL;
    }

    char *user_login = strdup((char *)sqlite3_column_text(statement, 0));

    db_close_statement(statement, db);

    return user_login;
}

char *db_get_chat_name_by_id(sqlite3 *db, int chat_id) {
    char *sql = NULL;
    asprintf(&sql, "SELECT "CHATS_NAME" FROM "CHATS_TABLE" \
                    WHERE "CHATS_ID" = %d", chat_id
    );

    sqlite3_stmt *statement = db_open_statement(db, sql);

    free(sql);

    if (sqlite3_step(statement) != SQLITE_ROW) {
        db_close_statement(statement, db);
        return NULL;
    }

    char *chat_name = strdup((char *)sqlite3_column_text(statement, 0));

    db_close_statement(statement, db);

    return chat_name;
}

int *db_get_IDs_of_chats_user_is_in(sqlite3 *db, int user_id, size_t *IDs_of_chats_len) {
    char *sql = NULL;
    asprintf(&sql, "SELECT "MEMBERS_CHAT_ID" FROM "MEMBERS_TABLE" \
                    WHERE "MEMBERS_USER_ID" = %d", user_id
    );

    sqlite3_stmt *statement = db_open_statement(db, sql);

    free(sql);

    *IDs_of_chats_len = 0;
    int *IDs_of_chats = NULL;
    while (sqlite3_step(statement) == SQLITE_ROW) {
        IDs_of_chats = realloc(IDs_of_chats, sizeof(int) * ++(*IDs_of_chats_len));
        IDs_of_chats[*IDs_of_chats_len - 1] = sqlite3_column_int(statement, 0);
    }

    db_close_statement(statement, db);

    return IDs_of_chats;
}

t_chat *db_get_chats_user_is_in(sqlite3 *db, int user_id, size_t *number_of_chats) {
    int *IDs_of_chats_user_is_in = db_get_IDs_of_chats_user_is_in(db, user_id,  number_of_chats);

    t_chat *descriptions_of_chats = malloc(*number_of_chats * sizeof(t_chat));

    for (size_t i = 0; i < *number_of_chats; i++) {
        descriptions_of_chats[i].id = IDs_of_chats_user_is_in[i];
        descriptions_of_chats[i].name = db_get_chat_name_by_id(db, IDs_of_chats_user_is_in[i]);
    }

    free(IDs_of_chats_user_is_in);

    return descriptions_of_chats;
}

t_message *db_get_last_messages(sqlite3 *db, uint32_t chat_id, size_t count, size_t *number_of_found) {
    char *sql = NULL;
    asprintf(&sql, "SELECT "MESSAGES_USER_ID", "MESSAGES_CONTENT" FROM "MESSAGES_TABLE" \
                    WHERE "MESSAGES_CHAT_ID" = %d ORDER BY "MESSAGES_ID" DESC", chat_id);

    sqlite3_stmt *statement = db_open_statement(db, sql);

    free(sql);

    t_message *messages = malloc(count * sizeof(t_message));

    *number_of_found = 0;
    for (; sqlite3_step(statement) == SQLITE_ROW && *number_of_found <= count; (*number_of_found)++) {
        messages[*number_of_found].user_id = sqlite3_column_int(statement, 0);
        messages[*number_of_found].user_login = db_get_user_login_by_id(db, messages[*number_of_found].user_id);
        messages[*number_of_found].bytes = strdup(sqlite3_column_blob(statement, 1));
    }
    db_close_statement(statement, db);

    if (*number_of_found == 0) {
        free(messages);
        return NULL;
    }
    if (*number_of_found != count) {
        messages = realloc(messages, *number_of_found * sizeof(t_message));
    }

    return messages;
}

