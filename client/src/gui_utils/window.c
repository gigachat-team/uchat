#include "gui_utils.h"

void open_window(GtkBuilder *builder, char *window_name) {
    GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(builder, window_name));

    gtk_widget_show_all(window);
}

void close_window(GtkBuilder *builder, char *window_name) {
    GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(builder, window_name));

    gtk_widget_hide(window);
}
