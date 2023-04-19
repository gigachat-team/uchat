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
        t_user_message *user_message = malloc(sizeof(t_user_message));
        user_message->message_id = sqlite3_column_int(statement, 0);
        user_message->sender_id = sqlite3_column_int(statement, 1);
        user_message->sender_login = strdup((char *)sqlite3_column_text(statement, 2));
        user_message->data = strdup(sqlite3_column_blob(statement, 3));
        user_message->creation_date = sqlite3_column_int(statement, 4);
        user_message->changes_count = sqlite3_column_int(statement, 5);
        list_rpush(messages_list, list_node_new(user_message));
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
                t_message_update *message_update = create_empty_message_update_ptr();
                message_update->message.message_id = message_id_in_db;
                message_update->message.data = strdup(sqlite3_column_blob(statement, 3));
                message_update->message.changes_count = message_changes_count;
                message_update->remove = false;
                list_lpush(message_updates_list, list_node_new(message_update));
            }
            if (step_result != SQLITE_DONE)
                step_result = sqlite3_step(statement);
            i--;
            continue;
        }

        t_message_update *message_update = create_empty_message_update_ptr();
        if (client_messages->len > 0 && message_id_in_db < (int)client_messages->arr[i].id) {
            message_update->message.message_id = client_messages->arr[i].id;
            message_update->remove = true;
            i--;
        } else {
            message_update->message.message_id = message_id_in_db;
            message_update->message.sender_id = sqlite3_column_int(statement, 1);
            message_update->message.sender_login = strdup((char *)sqlite3_column_text(statement, 2));
            if (ignore_last_selected_message_data) {
                message_update->message.data = NULL;
                ignore_last_selected_message_data = false;
            }
            else
                message_update->message.data = strdup(sqlite3_column_blob(statement, 3));
            message_update->message.creation_date = sqlite3_column_int(statement, 4);
            message_update->message.changes_count = sqlite3_column_int(statement, 5);
            message_update->remove = false;
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
