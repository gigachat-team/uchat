#include "../../server.h"

void db_create_users_table(sqlite3 *db) {
    char *sql = "CREATE TABLE IF NOT EXISTS "USERS_TABLE" ( \
        "USERS_ID"          INTEGER PRIMARY KEY AUTOINCREMENT, \
        "USERS_LOGIN"       TEXT UNIQUE NOT NULL CHECK("USERS_LOGIN" != ''), \
        "USERS_PASSWORD"    TEXT NOT NULL);";
    db_execute_sql(db, sql);
}

void db_create_chats_table(sqlite3 *db) {
    char *sql = "CREATE TABLE IF NOT EXISTS "CHATS_TABLE" ( \
                    "CHATS_ID"      INTEGER PRIMARY KEY AUTOINCREMENT, \
                    "CHATS_NAME"    TEXT, \
                    "CHATS_USER_ID" INTEGER);";
    db_execute_sql(db, sql);
}

void db_create_members_table(sqlite3 *db) {
    char *sql = "CREATE TABLE IF NOT EXISTS "MEMBERS_TABLE" ( \
        "MEMBERS_CHAT_ID" INTEGER, \
        "MEMBERS_USER_ID" INTEGER, \
        PRIMARY KEY ("MEMBERS_CHAT_ID", "MEMBERS_USER_ID"), \
        FOREIGN KEY ("MEMBERS_CHAT_ID") REFERENCES "CHATS_TABLE" ("CHATS_ID"), \
        FOREIGN KEY ("MEMBERS_USER_ID") REFERENCES "CHATS_TABLE" ("CHATS_USER_ID"));";
    db_execute_sql(db, sql);
}

void db_create_messages_table(sqlite3 *db) {
    char *sql = "CREATE TABLE IF NOT EXISTS "MESSAGES_TABLE" ( \
        "MESSAGES_ID"               INTEGER PRIMARY KEY AUTOINCREMENT, \
        "MESSAGES_CHAT_ID"          INTEGER, \
        "MESSAGES_USER_ID"          INTEGER, \
        "MESSAGES_CONTENT"          BLOB NOT NULL, \
        "MESSAGES_CREATION_DATE"    TEXT NOT NULL, \
        "MESSAGES_ORDER"            INTEGER, \
        FOREIGN KEY ("MESSAGES_CHAT_ID")    REFERENCES "MEMBERS_TABLE" ("MEMBERS_CHAT_ID"), \
        FOREIGN KEY ("MESSAGES_USER_ID")    REFERENCES "MEMBERS_TABLE" ("MEMBERS_USER_ID"), \
        FOREIGN KEY ("MESSAGES_ID")         REFERENCES "MESSAGE_STATUSES_TABLE" ("MESSAGE_STATUSES_MESSAGE_ID"), \
        FOREIGN KEY ("MESSAGES_USER_ID")    REFERENCES "MESSAGE_STATUSES_TABLE" ("MESSAGE_STATUSES_USER_ID"));";
    db_execute_sql(db, sql);
}

void db_create_message_statuses_table(sqlite3 *db) {
    char *sql = "CREATE TABLE IF NOT EXISTS "MESSAGE_STATUSES_TABLE" ( \
                    "MESSAGE_STATUSES_MESSAGE_ID"   INTEGER, \
                    "MESSAGE_STATUSES_USER_ID"      INTEGER, \
                    "MESSAGE_STATUSES_IS_READ"      INTEGER NOT NULL);";
    db_execute_sql(db, sql);
}

