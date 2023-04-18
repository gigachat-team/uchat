#pragma once

#include "utils.h"
#include "list.h"

typedef struct s_user_message {
    id_t message_id;
    id_t sender_id;
    char *sender_login;
    char *data;
    char *creation_date;
    uint8_t changes_count;
} t_user_message;

void free_user_message_ptr(void *message_ptr);
void free_user_messages(t_user_message *messages, size_t length);
void free_user_messages_list(list_t *messages_list);
