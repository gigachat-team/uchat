#pragma once

#include "utils.h"
#include "message_updates.h"

void send_message_updates_list(int client_socket, t_list_with_size *message_updates_list);
