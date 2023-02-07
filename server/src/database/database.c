#include "../../server.h"

sqlite3 *db_open() {
    sqlite3 *db;
    if (sqlite3_open(DATABASE_NAME, &db) != SQLITE_OK) {
        fprintf(stderr, "Failed o open database: %s\n", sqlite3_errmsg(db));
        db_close(db);
        exit(EXIT_FAILURE);
    }

    return db;
}

void db_close(sqlite3 *db) {
    if (sqlite3_close(db) != SQLITE_OK) {
        fprintf(stderr, "Failed to close database: %s\n", sqlite3_errmsg(db));
        exit(EXIT_FAILURE);
    }
}

sqlite3_stmt *db_open_statement(sqlite3 *db, char *sql) {
    sqlite3_stmt *statement;
    if (sqlite3_prepare_v2(db, sql, -1, &statement, 0) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare sqlite3 statement: %s\n", sqlite3_errmsg(db));
        db_close(db);
        exit(EXIT_FAILURE);
    }
    return statement;
}

void db_close_statement(sqlite3_stmt *statement, sqlite3 *db) {
    if (sqlite3_finalize(statement) != SQLITE_OK) {
        fprintf(stderr, "Failed to finalize sqlite3 statement: %s\n", sqlite3_errmsg(db));
        db_close(db);
        exit(EXIT_FAILURE);
    }
}

void db_close_statement_and_database(sqlite3_stmt *statement, sqlite3 *db) {
    db_close_statement(statement, db);
    db_close(db);
}

void db_execute_sql(sqlite3 *db, char* sql) {
    char *error_message;
    if (sqlite3_exec(db, sql, NULL, NULL, &error_message) != SQLITE_OK) {
        fprintf(stderr, "Failed to execute sql: %s", error_message);
        db_close(db);
        exit(EXIT_FAILURE);
    }
}

void db_open_and_execute_sql(char *sql) {
    sqlite3 *database = db_open();
    db_execute_sql(database, sql);
    db_close(database);
}

