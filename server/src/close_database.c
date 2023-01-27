#include "../server.h"

void close_database(sqlite3 *database) {
    if (sqlite3_close(database) != SQLITE_OK) {
        fprintf(stderr, "Failed to close database: %s\n", sqlite3_errmsg(database));
        exit(EXIT_FAILURE);
    }
}

