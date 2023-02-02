#include "../../server.h"

bool db_get_password_by_login(const char *login, char **password) {
    char *sql_command = NULL;
    asprintf(&sql_command, "SELECT "USERS_PASSWORD" FROM "USERS_TABLE" \
                            WHERE "USERS_LOGIN" = '%s'", login
    );

    sqlite3 *database = db_open();
    sqlite3_stmt *statement = db_open_statement(database, sql_command);

    if (sqlite3_step(statement) != SQLITE_ROW) {
        db_close_statement_and_database(statement, database);
        free(sql_command);
        return false;
    }

    *password = mx_strdup((char *)sqlite3_column_text(statement, 0));
    
    db_close_statement_and_database(statement, database);
    free(sql_command);

    return true;
}

int db_get_user_id_by_login(char *login) {
    char *sql_command = NULL;
    asprintf(&sql_command, "SELECT "USERS_ID" FROM "USERS_TABLE" \
                            WHERE "USERS_LOGIN" = '%s'", login
    );
    
    sqlite3 *database = db_open();
    sqlite3_stmt *statement = db_open_statement(database, sql_command);

    free(sql_command);

    if (sqlite3_step(statement) != SQLITE_ROW) {
        db_close_statement_and_database(statement, database);
        return -1;
    }

    int user_id = sqlite3_column_int(statement, 0);

    db_close_statement_and_database(statement, database);

    return user_id;
}

char *db_get_chat_name_by_id(int chat_id) {
    char *sql_command = NULL;
    asprintf(&sql_command, "SELECT "CHATS_NAME" FROM "CHATS_TABLE" \
                            WHERE "CHATS_ID" = %d", chat_id
    );

    sqlite3 *database = db_open();
    sqlite3_stmt *statement = db_open_statement(database, sql_command);

    free(sql_command);

    if (sqlite3_step(statement) != SQLITE_ROW) {
        db_close_statement_and_database(statement, database);
        return NULL;
    }

    char *chat_name = strdup((char *)sqlite3_column_text(statement, 0));

    db_close_statement_and_database(statement, database);

    return chat_name;
}

int *db_get_IDs_of_chats_user_is_in(int user_id, size_t *IDs_of_chats_len) {
    char *sql_command = NULL;
    asprintf(&sql_command, "SELECT "MEMBERS_CHAT_ID" FROM "MEMBERS_TABLE" \
                            WHERE "MEMBERS_USER_ID" = %d", user_id
    );

    sqlite3 *database = db_open();
    sqlite3_stmt *statement = db_open_statement(database, sql_command);

    *IDs_of_chats_len = 0;
    int *IDs_of_chats = NULL;
    while (sqlite3_step(statement) == SQLITE_ROW) {
        IDs_of_chats = realloc(IDs_of_chats, sizeof(int) * ++(*IDs_of_chats_len));
        IDs_of_chats[*IDs_of_chats_len - 1] = sqlite3_column_int(statement, 0);
    }

    db_close_statement_and_database(statement, database);
    free(sql_command);

    return IDs_of_chats;
}

t_chat *db_get_chats_user_is_in(int user_id, size_t *number_of_chats) {
    int *IDs_of_chats_user_is_in = db_get_IDs_of_chats_user_is_in(user_id,  number_of_chats);

    t_chat *descriptions_of_chats = malloc(*number_of_chats * sizeof(t_chat));

    for (size_t i = 0; i < *number_of_chats; i++) {
        descriptions_of_chats[i].id = IDs_of_chats_user_is_in[i];
        descriptions_of_chats[i].name = db_get_chat_name_by_id(IDs_of_chats_user_is_in[i]);
    }

    free(IDs_of_chats_user_is_in);

    return descriptions_of_chats;
}

