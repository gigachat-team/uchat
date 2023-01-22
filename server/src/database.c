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

// void create_users_table(sqlite3 *database) {
//     sqlite3_exec(database, USERS_TABLE_CREATION_SQL, NULL, )
// }

int insert_to_users_table(sqlite3 *database, char *login, char *password) {
    char command[300];
    sprintf(command, "INSERT INTO %s (%s, %s) VALUES ('%s', '%s');", USERS_TABLE_NAME, USER_LOGIN_NAME, USER_PASSWORD_NAME, login, password);
    char *error_message; // for debug
    return sqlite3_exec(database, command, NULL, NULL, &error_message);
}

