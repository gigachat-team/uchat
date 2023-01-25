#include "../inc/database.h"

sqlite3 *open_database() {
    sqlite3 *database;
    if (sqlite3_open(DATABASE_NAME, &database) != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(database));
        sqlite3_close(database);
        exit(EXIT_FAILURE);
    }

    return database;
}
