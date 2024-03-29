#include "gui_utils.h"

GtkWidget *get_widget(GtkBuilder *gtk_builder, char *name) {
    return GTK_WIDGET(gtk_builder_get_object(gtk_builder, name));
}

void add_to_box_start(GtkBuilder *builder, GtkWidget *new_element, gchar *box_name, gint padding) {
    GtkWidget *box = GTK_WIDGET(gtk_builder_get_object(builder, box_name));

    gtk_box_pack_start(GTK_BOX(box), new_element, false, false, padding);
    gtk_widget_show(new_element);
}

void show_widget(GtkBuilder *builder, char *widget_name) {
    GtkWidget *widget = get_widget(builder, widget_name);
    gtk_widget_show(widget);
}

void hide_widget(GtkBuilder *builder, char *widget_name) {
    GtkWidget *widget = get_widget(builder, widget_name);
    gtk_widget_hide(widget);
}

bool toggle_widget_visibility(bool visible, GtkBuilder *builder, char *widget_name) {
    visible ? show_widget(builder, widget_name) : hide_widget(builder, widget_name);
    return visible;
}
