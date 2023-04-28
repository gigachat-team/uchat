#include "database.h"

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

list_t *db_select_chats_by_member_id(sqlite3 *db, id_t member_id) {
    char *sql = sqlite3_mprintf(" \
        SELECT "CHATS_ID", "CHATS_NAME", "CHATS_OWNER_ID" \
        FROM "CHATS_TABLE" \
        INNER JOIN "MEMBERS_TABLE" ON "CHATS_TABLE"."CHATS_ID" = "MEMBERS_TABLE"."MEMBERS_CHAT_ID" \
        WHERE "MEMBERS_USER_ID" = %u", member_id
    );
    sqlite3_stmt *statement = db_open_statement(db, sql);
    sqlite3_free(sql);

    list_t *chats_list = list_new();
    while (sqlite3_step(statement) == SQLITE_ROW) {
        t_chat *chat = malloc(sizeof(t_chat));
        chat->id = sqlite3_column_int(statement, 0);
        chat->name = strdup((char *)sqlite3_column_text(statement, 1));
        chat->owner_id = sqlite3_column_int(statement, 2);
        list_rpush(chats_list, list_node_new(chat));
    }
    db_close_statement(statement, db);

    return chats_list;
}

list_t *db_select_messages(sqlite3 *db, id_t chat_id) {
    char *sql = sqlite3_mprintf(" \
        SELECT "MESSAGES_ID", "MESSAGES_USER_ID", \
        (SELECT "USERS_LOGIN" FROM "USERS_TABLE" WHERE "USERS_TABLE"."USERS_ID" = "MESSAGES_TABLE"."MESSAGES_USER_ID"), \
        "MESSAGES_CONTENT", "MESSAGES_CREATION_DATE", "MESSAGES_CHANGES_COUNT" \
        FROM "MESSAGES_TABLE" \
        WHERE "MESSAGES_CHAT_ID" = %u", chat_id
    );
    sqlite3_stmt *statement = db_open_statement(db, sql);
    sqlite3_free(sql);

    list_t *messages_list = list_new();
    for (; sqlite3_step(statement) == SQLITE_ROW; ) {
        t_message *message = malloc(sizeof(t_message));
        message->message_id = sqlite3_column_int(statement, 0);
        message->sender_id = sqlite3_column_int(statement, 1);
        message->sender_login = strdup((char *)sqlite3_column_text(statement, 2));
        message->data = strdup(sqlite3_column_blob(statement, 3));
        message->creation_date = sqlite3_column_int(statement, 4);
        message->changes_count = sqlite3_column_int(statement, 5);
        message->reply_message_id = sqlite3_column_int(statement, 6);
        list_rpush(messages_list, list_node_new(message));
    }
    db_close_statement(statement, db);

    return messages_list;
}

list_t *db_select_message_updates(sqlite3 *db, id_t chat_id, t_id_and_changes_count_array *client_messages, bool ignore_last_selected_message_data) {
    char *sql = sqlite3_mprintf(" \
        SELECT "MESSAGES_ID", "MESSAGES_USER_ID", \
        (SELECT "USERS_LOGIN" FROM "USERS_TABLE" WHERE "USERS_TABLE"."USERS_ID" = "MESSAGES_TABLE"."MESSAGES_USER_ID"), \
        "MESSAGES_CONTENT", "MESSAGES_CREATION_DATE", "MESSAGES_CHANGES_COUNT" \
        FROM "MESSAGES_TABLE" \
        WHERE "MESSAGES_CHAT_ID" = %u \
        ORDER BY "MESSAGES_ID" DESC", chat_id
    );

    sqlite3_stmt *statement = db_open_statement(db, sql);
    sqlite3_free(sql);

    list_t *message_updates_list = list_new();
    int step_result = sqlite3_step(statement);
    for (int i = client_messages->len - 1; step_result == SQLITE_ROW || i >= 0;) {
        int message_id_in_db = sqlite3_column_int(statement, 0);
        if (client_messages->len > 0 && message_id_in_db == (int)client_messages->arr[i].id) {
            int message_changes_count = sqlite3_column_int(statement, 5);

            if (message_changes_count != client_messages->arr[i].changes_count) {
                t_message *message_update = create_message_ptr();
                message_update->message_id = message_id_in_db;
                message_update->data = strdup(sqlite3_column_blob(statement, 3));
                message_update->changes_count = message_changes_count;
                message_update->reply_message_id = sqlite3_column_int(statement, 6);
                list_lpush(message_updates_list, list_node_new(message_update));
            }
            if (step_result != SQLITE_DONE)
                step_result = sqlite3_step(statement);
            i--;
            continue;
        }

        t_message *message_update = create_message_ptr();
        if (client_messages->len > 0 && message_id_in_db < (int)client_messages->arr[i].id) {
            message_update->message_id = client_messages->arr[i].id;
            i--;
        } else {
            message_update->message_id = message_id_in_db;
            message_update->sender_id = sqlite3_column_int(statement, 1);
            message_update->sender_login = strdup((char *)sqlite3_column_text(statement, 2));
            if (ignore_last_selected_message_data) {
                message_update->data = NULL;
            } else {
                message_update->data = strdup(sqlite3_column_blob(statement, 3));
            }
            message_update->creation_date = sqlite3_column_int(statement, 4);
            message_update->changes_count = sqlite3_column_int(statement, 5);
            message_update->reply_message_id = sqlite3_column_int(statement, 6);
            if (step_result != SQLITE_DONE)
                step_result = sqlite3_step(statement);
        }

        list_lpush(message_updates_list, list_node_new(message_update));
    }
    db_close_statement(statement, db);

    return message_updates_list;
}

list_t *db_select_members(sqlite3 *db, id_t chat_id) {
    char *sql = sqlite3_mprintf(" \
        SELECT "MEMBERS_USER_ID", \
            (SELECT "USERS_LOGIN" FROM "USERS_TABLE" \
            WHERE "USERS_TABLE"."USERS_ID" = "MEMBERS_TABLE"."MEMBERS_USER_ID") \
        FROM "MEMBERS_TABLE" WHERE "MEMBERS_CHAT_ID" = %u", chat_id
    );
    sqlite3_stmt *statement = db_open_statement(db, sql);
    sqlite3_free(sql);

    list_t *members_list = list_new();
    while (sqlite3_step(statement) == SQLITE_ROW) {
        t_user *member = malloc(sizeof(t_user));
        member->id = sqlite3_column_int(statement, 0);
        member->login = strdup((char *)sqlite3_column_text(statement, 1));
        list_rpush(members_list, list_node_new(member));
    }
    db_close_statement(statement, db);

    return members_list;
}
