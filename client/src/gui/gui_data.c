#include "gui.h"

t_gui_data create_gui_data(char *ip, in_port_t port) {
    t_gui_data gui_data = {
        .builder = create_gtk_builder(),
        .server_address = {ip, port},
        .user_id = 0
    };
    return gui_data;
}
