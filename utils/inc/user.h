#pragma once

#define _GNU_SOURCE
#include "list.h"

typedef struct s_user {
    id_t id;
    char *login;
} t_user;

void free_user(t_user user);
void free_users(t_user *users, size_t users_count);
void free_users_list(list_t *users_list);
