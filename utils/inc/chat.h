#pragma once

#define _GNU_SOURCE
#include <malloc.h>
#include <sys/types.h>

typedef struct s_chat {
    id_t id;
    char *name;
} t_chat;

void free_chat(t_chat chat);
void free_chats(t_chat *chats, size_t length);
