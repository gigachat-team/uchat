#pragma once

#include "list.h"
#include "types.h"

typedef struct {
    id_t message_id;
    id_t sender_id;
    char *sender_login;
    char *data;
    uint32_t creation_date;
    uint8_t changes_count;
    id_t reply_message_id;
} t_message;

t_message create_message();
t_message *create_message_ptr();
void free_message(t_message *message);
void free_message_ptr(void *message);
void free_messages_array(t_message *messages, size_t length);
void free_messages_list(list_t *messages_list);
