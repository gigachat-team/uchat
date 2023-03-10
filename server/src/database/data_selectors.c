#include "../../server.h"

char *db_get_password_by_id(sqlite3 *db, id_t id) {
    char *sql = sqlite3_mprintf(" \
        SELECT "USERS_PASSWORD" FROM "USERS_TABLE" \
        WHERE "USERS_ID" = %u", id
    );
    sqlite3_stmt *statement = db_open_statement(db, sql);
    sqlite3_free(sql);

    if (sqlite3_step(statement) != SQLITE_ROW) {
        db_close_statement(statement, db);
        return NULL;
    }

    char *password = strdup((char *)sqlite3_column_text(statement, 0));

    db_close_statement(statement, db);

    return password;
}

id_t db_get_user_id_by_login(sqlite3 *db, char *login) {
    char *sql = sqlite3_mprintf(" \
        SELECT "USERS_ID" FROM "USERS_TABLE" \
        WHERE "USERS_LOGIN" = %Q", login
    );
    sqlite3_stmt *statement = db_open_statement(db, sql);
    sqlite3_free(sql);

    if (sqlite3_step(statement) != SQLITE_ROW) {
        db_close_statement(statement, db);
        return 0;
    }

    id_t user_id = sqlite3_column_int(statement, 0);

    db_close_statement(statement, db);

    return user_id;
}

char *db_get_user_login_by_id(sqlite3 *db, id_t user_id) {
    char *sql = sqlite3_mprintf(" \
        SELECT "USERS_LOGIN" FROM "USERS_TABLE" \
        WHERE "USERS_ID" = %u", user_id
    );
    sqlite3_stmt *statement = db_open_statement(db, sql);
    sqlite3_free(sql);

    if (sqlite3_step(statement) != SQLITE_ROW) {
        db_close_statement(statement, db);
        return NULL;
    }

    char *user_login = strdup((char *)sqlite3_column_text(statement, 0));

    db_close_statement(statement, db);

    return user_login;
}

char *db_get_chat_name_by_id(sqlite3 *db, id_t chat_id) {
    char *sql = sqlite3_mprintf(" \
        SELECT "CHATS_NAME" FROM "CHATS_TABLE" \
        WHERE "CHATS_ID" = %u", chat_id
    );
    sqlite3_stmt *statement = db_open_statement(db, sql);
    sqlite3_free(sql);

    if (sqlite3_step(statement) != SQLITE_ROW) {
        db_close_statement(statement, db);
        return NULL;
    }

    char *chat_name = strdup((char *)sqlite3_column_text(statement, 0));

    db_close_statement(statement, db);

    return chat_name;
}

id_t *db_get_IDs_of_chats_user_is_in(sqlite3 *db, id_t user_id, size_t *IDs_of_chats_len) {
    char *sql = sqlite3_mprintf(" \
        SELECT "MEMBERS_CHAT_ID" FROM "MEMBERS_TABLE" \
        WHERE "MEMBERS_USER_ID" = %u", user_id
    );
    sqlite3_stmt *statement = db_open_statement(db, sql);
    sqlite3_free(sql);

    *IDs_of_chats_len = 0;
    id_t *IDs_of_chats = NULL;
    while (sqlite3_step(statement) == SQLITE_ROW) {
        IDs_of_chats = realloc(IDs_of_chats, sizeof(id_t) * ++(*IDs_of_chats_len));
        IDs_of_chats[*IDs_of_chats_len - 1] = sqlite3_column_int(statement, 0);
    }

    db_close_statement(statement, db);

    return IDs_of_chats;
}

t_chat *db_get_chats_user_is_in(sqlite3 *db, id_t user_id, size_t *number_of_chats) {
    id_t *IDs_of_chats_user_is_in = db_get_IDs_of_chats_user_is_in(db, user_id,  number_of_chats);

    t_chat *descriptions_of_chats = malloc(*number_of_chats * sizeof(t_chat));

    for (size_t i = 0; i < *number_of_chats; i++) {
        descriptions_of_chats[i].id = IDs_of_chats_user_is_in[i];
        descriptions_of_chats[i].name = db_get_chat_name_by_id(db, IDs_of_chats_user_is_in[i]);
    }

    free(IDs_of_chats_user_is_in);

    return descriptions_of_chats;
}

t_user_message *db_get_last_messages(sqlite3 *db, id_t chat_id, uint32_t last_message_order, size_t count, size_t *number_of_found) {
    char *sql = sqlite3_mprintf(" \
        SELECT "MESSAGES_USER_ID", "MESSAGES_CONTENT", "MESSAGES_CREATION_DATE", "MESSAGES_ORDER" \
        FROM "MESSAGES_TABLE" \
        WHERE "MESSAGES_CHAT_ID" = %u AND "MESSAGES_ORDER" <= %u \
        ORDER BY "MESSAGES_ID" DESC", chat_id, last_message_order
    );
    sqlite3_stmt *statement = db_open_statement(db, sql);
    sqlite3_free(sql);

    t_user_message *messages = malloc(count * sizeof(t_user_message));

    *number_of_found = 0;
    for (; sqlite3_step(statement) == SQLITE_ROW && *number_of_found <= count; (*number_of_found)++) {
        messages[*number_of_found].user_id = sqlite3_column_int(statement, 0);
        messages[*number_of_found].user_login = db_get_user_login_by_id(db, messages[*number_of_found].user_id);
        messages[*number_of_found].bytes = strdup(sqlite3_column_blob(statement, 1));
        messages[*number_of_found].creation_date = strdup(sqlite3_column_blob(statement, 2));
        messages[*number_of_found].order_in_chat = sqlite3_column_int(statement, 3);
    }
    db_close_statement(statement, db);

    if (*number_of_found == 0) {
        free(messages);
        return NULL;
    }
    if (*number_of_found != count) {
        messages = realloc(messages, *number_of_found * sizeof(t_user_message));
    }

    return messages;
}

t_user *db_get_chat_members(sqlite3 *db, id_t chat_id, size_t *members_count) {
    char *sql = sqlite3_mprintf(" \
        SELECT COUNT(*) FROM "MEMBERS_TABLE" \
        WHERE "MEMBERS_CHAT_ID" = %u", chat_id
    );
    sqlite3_stmt *statement = db_open_statement(db, sql);
    sqlite3_free(sql);
    sqlite3_step(statement);
    *members_count = sqlite3_column_int(statement, 0);
    db_close_statement(statement, db);

    if (*members_count == 0) {
        return NULL;
    }

    sql = sqlite3_mprintf(" \
        SELECT "MEMBERS_USER_ID", \
            (SELECT "USERS_LOGIN" FROM "USERS_TABLE" \
            WHERE "USERS_TABLE"."USERS_ID" = "MEMBERS_TABLE"."MEMBERS_USER_ID") \
        FROM "MEMBERS_TABLE" WHERE "MEMBERS_CHAT_ID" = %u", chat_id
    );
    statement = db_open_statement(db, sql);
    sqlite3_free(sql);
    sqlite3_step(statement);
    t_user *members = malloc(*members_count * sizeof(t_user));
    for (size_t i = 0; i < *members_count; i++) {
        members[i].id = sqlite3_column_int(statement, 0);
        members[i].login = strdup((char *)sqlite3_column_text(statement, 1));
        sqlite3_step(statement);
    }
    db_close_statement(statement, db);

    return members;
}
