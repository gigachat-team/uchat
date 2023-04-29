#pragma once

#include "list.h"
#include "types.h"
#include <gtk/gtk.h>

typedef struct {
    id_t message_id;
    id_t sender_id;
    char *sender_login;
    char *data;
    time_t creation_date;
    uint8_t changes_count;
    id_t reply_message_id;
    GtkWidget *container_box;
    GtkWidget *content_label;
    GtkWidget *is_edited_label;
    GtkWidget *replied_message_content_label;
    GtkWidget *replied_message_login_label;
} t_message;

typedef struct s_messages_array {
    t_message *arr;
    size_t size;
} t_messages_array;

t_message create_message();
t_message *create_message_ptr();
void free_message(t_message *message);
void free_messages_list(list_t *messages_list);
int compare_messages_IDs(void *a, void *b);
