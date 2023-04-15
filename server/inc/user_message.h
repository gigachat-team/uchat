#pragma once

#include "../../utils/utils.h"

typedef struct s_user_message {
    id_t message_id;
    id_t sender_id;
    char *sender_login;
    char *data;
    char *creation_date;
} t_user_message;

void free_user_message(t_user_message *message);
void free_user_messages(t_user_message *messages, size_t length);
void free_user_messages_list(t_list **messages_list);
void free_message_updates_list(t_list **message_updates_list);
