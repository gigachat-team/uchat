#include "../../server.h"

sqlite3 *db_open() {
    sqlite3 *database;
    if (sqlite3_open(DATABASE_NAME, &database) != SQLITE_OK) {
        fprintf(stderr, "Failed o open database: %s\n", sqlite3_errmsg(database));
        db_close(database);
        exit(EXIT_FAILURE);
    }

    return database;
}

void db_close(sqlite3 *database) {
    if (sqlite3_close(database) != SQLITE_OK) {
        fprintf(stderr, "Failed to close database: %s\n", sqlite3_errmsg(database));
        exit(EXIT_FAILURE);
    }
}

sqlite3_stmt *db_open_statement(sqlite3 *database, char *sql_command) {
    sqlite3_stmt *statement;
    if (sqlite3_prepare_v2(database, sql_command, -1, &statement, 0) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare sqlite3 statement: %s\n", sqlite3_errmsg(database));
        db_close(database);
        exit(EXIT_FAILURE);
    }
    return statement;
}

void db_close_statement(sqlite3_stmt *statement, sqlite3 *database) {
    if (sqlite3_finalize(statement) != SQLITE_OK) {
        fprintf(stderr, "Failed to finalize sqlite3 statement: %s\n", sqlite3_errmsg(database));
        db_close(database);
        exit(EXIT_FAILURE);
    }
}

void db_close_statement_and_database(sqlite3_stmt *statement, sqlite3 *database) {
    db_close_statement(statement, database);
    db_close(database);
}

void db_execute_sql(sqlite3 *database, char* sql_command) {
    char *error_message;
    if (sqlite3_exec(database, sql_command, NULL, NULL, &error_message) != SQLITE_OK) {
        fprintf(stderr, "Failed to execute sql: %s", error_message);
        db_close(database);
        exit(EXIT_FAILURE);
    }
}

void db_open_and_execute_sql(char *sql_command) {
    sqlite3 *database = db_open();
    db_execute_sql(database, sql_command);
    db_close(database);
}

