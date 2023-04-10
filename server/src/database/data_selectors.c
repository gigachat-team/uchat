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

static t_list *select_messages_list(sqlite3 *db, char *sql, size_t *found_messages_count) {
    sqlite3_stmt *statement = db_open_statement(db, sql);

    t_list *messages_list = NULL;

    *found_messages_count = 0;
    for (; sqlite3_step(statement) == SQLITE_ROW; (*found_messages_count)++) {
        t_user_message *user_message = malloc(sizeof(t_user_message));
        user_message->message_id = sqlite3_column_int(statement, 0);
        user_message->sender_id = sqlite3_column_int(statement, 1);
        user_message->sender_login = strdup((char *)sqlite3_column_text(statement, 2));
        user_message->data = strdup(sqlite3_column_blob(statement, 3));
        user_message->creation_date = strdup(sqlite3_column_blob(statement, 4));
        mx_push_front(&messages_list, user_message);
    }
    db_close_statement(statement, db);

    return messages_list;
}

t_list *db_get_messages_in_chat(sqlite3 *db, id_t chat_id, size_t *found_messages_count) {
    char *sql = sqlite3_mprintf(" \
        SELECT "MESSAGES_ID", "MESSAGES_USER_ID", (SELECT "USERS_LOGIN" FROM "USERS_TABLE" WHERE "USERS_TABLE"."USERS_ID" = "MESSAGES_TABLE"."MESSAGES_USER_ID"), "MESSAGES_CONTENT", "MESSAGES_CREATION_DATE" \
        FROM "MESSAGES_TABLE" \
        WHERE "MESSAGES_CHAT_ID" = %u \
        ORDER BY "MESSAGES_ID" DESC", chat_id
    );

    t_list *messages_list = select_messages_list(db, sql, found_messages_count);
    sqlite3_free(sql);

    return messages_list;
}

t_list_with_size db_select_message_updates(sqlite3 *db, id_t chat_id, t_uint32_array *message_IDs, bool ignore_last_selected_message_data) {
    char *sql = sqlite3_mprintf(" \
        SELECT "MESSAGES_ID", "MESSAGES_USER_ID", (SELECT "USERS_LOGIN" FROM "USERS_TABLE" WHERE "USERS_TABLE"."USERS_ID" = "MESSAGES_TABLE"."MESSAGES_USER_ID"), "MESSAGES_CONTENT", "MESSAGES_CREATION_DATE" \
        FROM "MESSAGES_TABLE" \
        WHERE "MESSAGES_CHAT_ID" = %u \
        ORDER BY "MESSAGES_ID" DESC", chat_id
    );

    sqlite3_stmt *statement = db_open_statement(db, sql);

    t_list_with_size list_with_size = {NULL, 0};
    for (size_t i = 0;sqlite3_step(statement) == SQLITE_ROW; i++) {
        int message_id = sqlite3_column_int(statement, 0);
        if (binary_search_uint32(message_IDs, message_id) != -1) {
            continue;
        }

        t_user_message *user_message = malloc(sizeof(t_user_message));
        user_message->message_id = message_id;
        user_message->sender_id = sqlite3_column_int(statement, 1);
        user_message->sender_login = strdup((char *)sqlite3_column_text(statement, 2));
        if (ignore_last_selected_message_data && i == 0)
            user_message->data = strdup("ne to otrenderiv, ruslanchik");
        else
            user_message->data = strdup(sqlite3_column_blob(statement, 3));
        user_message->creation_date = strdup(sqlite3_column_blob(statement, 4));
        mx_push_front(&list_with_size.list, user_message);
        list_with_size.size++;
    }
    db_close_statement(statement, db);

    return list_with_size;
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
