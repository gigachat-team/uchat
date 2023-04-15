#pragma once

#include "utils.h"
#include "gtk_builder.h"

typedef struct s_gui_data {
    GtkBuilder *builder;
    t_address server_address;
    uint user_id;
} t_gui_data;

t_gui_data create_gui_data(char *ip, in_port_t port);
