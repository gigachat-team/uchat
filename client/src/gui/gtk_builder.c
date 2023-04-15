#include "gtk_builder.h"

GtkBuilder *create_gtk_builder() {
    GError *err = NULL;
    GtkBuilder *builder = gtk_builder_new();

    if (gtk_builder_add_from_file(builder, GLADE_FILE_PATH, &err) == 0) {
        fprintf(stderr, "Error adding build from file. Error: %s\n", err->message);
        exit(EXIT_FAILURE);
    }

    return builder;
}
