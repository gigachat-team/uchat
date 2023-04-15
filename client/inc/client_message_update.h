#pragma once

#include "client_user_message.h"

typedef struct s_message_update {
    t_user_message message;
    bool remove;
} t_message_update;
