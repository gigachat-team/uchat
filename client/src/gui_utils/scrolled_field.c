#include "gui_utils.h"

void scroll_to_bottom(GtkBuilder *builder, char *name_scrolled_field) {
    GtkWidget *scrolled_window = GTK_WIDGET(gtk_builder_get_object(builder, name_scrolled_field));
    GtkAdjustment *adjustment = gtk_scrolled_window_get_vadjustment(GTK_SCROLLED_WINDOW(scrolled_window));
    gtk_adjustment_set_value(adjustment, gtk_adjustment_get_upper(adjustment) - gtk_adjustment_get_page_size(adjustment));
}
