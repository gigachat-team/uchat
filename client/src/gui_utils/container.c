#include "gui_utils.h"

void clear_container(GtkBuilder *builder, char *contener_name) {
    GList *list = gtk_container_get_children(GTK_CONTAINER(gtk_builder_get_object(builder, contener_name)));

    while (list != NULL) {
        gtk_widget_destroy(list->data);
        list = list->next;
    }

    g_list_free(list);
}
