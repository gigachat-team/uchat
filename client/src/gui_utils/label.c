#include "gui_utils.h"

void set_label_text(GtkWidget *gtk_widget, char *text) {
    gtk_label_set_text(GTK_LABEL(gtk_widget), text);
}

void write_label_text(GtkBuilder *builder, char *label_name, char *text) {
    GtkWidget *label = GTK_WIDGET(gtk_builder_get_object(builder, label_name));
    gtk_label_set_text(GTK_LABEL(label), text);
}
