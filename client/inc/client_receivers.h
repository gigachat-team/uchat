#pragma once

#include "client_user_message.h"
#include "client_message_update.h"

t_list_with_size receive_messages_list(int client_socket);
t_list_with_size receive_message_updates_list(int client_socket);
