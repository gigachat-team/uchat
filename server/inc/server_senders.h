#pragma once

#include "packager.h"
#include "server_message.h"

void send_messages_list(int client_socket, list_t *messages_list);
