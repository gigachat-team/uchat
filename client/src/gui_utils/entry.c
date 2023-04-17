#include "gui_utils.h"

char *get_entry_text(GtkBuilder *builder, char *entry_name) {
    GtkWidget *entry = GTK_WIDGET(gtk_builder_get_object(builder, entry_name));
    return (char *)gtk_entry_get_text(GTK_ENTRY(entry));
}
