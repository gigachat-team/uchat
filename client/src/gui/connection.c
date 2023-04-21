#include "gui.h"

bool show_error_if_no_connection(GtkBuilder *builder) {
    bool successfull_connection = false;

    if (errno == ECONNREFUSED || errno == ECONNABORTED || errno == EBADF) {
        show_widget(builder, CONNECTION_BOX_ID);
        errno = 0;
    } else {
        hide_widget(builder, CONNECTION_BOX_ID);
        successfull_connection = true;
    }

    return successfull_connection;
}
