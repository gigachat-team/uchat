#pragma once

#include "list.h"
#include "types.h"
#include <malloc.h>
#include <sys/types.h>

typedef struct s_chat {
    id_t id;
    char *name;
    id_t owner_id;
} t_chat;

void free_chat(t_chat *chat);
void free_chats(t_chat *chats, size_t length);
void free_chats_list(list_t *chats_list);
