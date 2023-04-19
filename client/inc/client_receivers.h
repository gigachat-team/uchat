#pragma once

#include "socket.h"
#include "receivers.h"
#include "time_converters.h"
#include "client_user_message.h"
#include "client_message_update.h"

list_t *receive_messages_list(int client_socket);
list_t *receive_message_updates_list(int client_socket);
