#pragma once

#include "user_message.h"
#include "utils.h"

typedef struct s_message_update {
    t_user_message message;
    bool remove;
} t_message_update;

t_message_update create_empty_message_update();
t_message_update *create_empty_message_update_ptr();
void send_message_updates_list(int client_socket, t_list_with_size *message_updates_list);
void free_message_updates_list(t_list **message_updates_list);
