#pragma once

#include "client_user_message.h"
#include "client_message_update.h"
#include "time_converters.h"

list_t *receive_messages_list(int client_socket);
list_t *receive_message_updates_list(int client_socket);
