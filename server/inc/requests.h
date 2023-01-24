#pragma once

#include "../../resources/libraries/sqlite3/sqlite3.h"
#include "../../utils/inc/base_includes.h"
#include "../../utils/inc/state_codes.h"
#include "../../utils/inc/recievers.h"
#include "../../utils/inc/requests.h"
#include "../../utils/inc/senders.h"
#include "../../utils/inc/threads.h"
#include "../../utils/inc/socket.h"

#include "database.h"

typedef struct s_database_and_socket {
    sqlite3 *database;
    int socket;
} t_database_and_socket;

pthread_t accept_requests_in_new_thread(sqlite3 *database, int listening_socket);
pthread_t handle_request_in_new_thread(sqlite3 *database, int client_socket);

