#pragma once

#include "utils.h"
#include "list.h"
#include <gtk/gtk.h>

typedef struct s_user_message {
    id_t message_id;
    id_t sender_id;
    char *sender_login;
    char *data;
    struct tm creation_date;
    GtkWidget *widget;
} t_user_message;

typedef struct s_user_messages_array {
    t_user_message *arr;
    size_t size;
} t_user_messages_array;

t_user_messages_array allocate_user_messages_array(size_t size);
void free_user_message(t_user_message message);
void free_user_messages(t_user_message *messages, size_t length);
void free_user_messages_list(t_list_with_size *messages_list);
