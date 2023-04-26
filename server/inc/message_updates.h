#pragma once

#include <stdbool.h>
#include "user_message.h"

typedef struct s_message_update {
    t_user_message message;
    bool remove;
} t_message_update;

t_message_update create_empty_message_update();
t_message_update *create_empty_message_update_ptr();
void free_message_updates_list(list_t *message_updates_list);
