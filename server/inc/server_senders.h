#pragma once

#include "utils.h"
#include "packager.h"
#include "message_updates.h"

void send_message_updates_list(int client_socket, list_t *message_updates_list);
