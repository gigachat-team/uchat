#pragma once

#include "socket.h"
#include "receivers.h"
#include "time_converters.h"
#include "client_message.h"

list_t *receive_messages_list(int client_socket);
