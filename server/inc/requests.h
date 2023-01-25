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

void *accept_requests_thread(void *listening_socket_void);

