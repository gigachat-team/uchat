#include "gui_utils.h"

GtkWidget *get_image_from_path(char *path, gint x, gint y) {
    GtkWidget *image = gtk_image_new();

    // Load the image from file using GdkPixbuf
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file(path, NULL);

    // Scale the image to a new size
    GdkPixbuf *scaled_pixbuf = gdk_pixbuf_scale_simple(pixbuf, x, y, GDK_INTERP_BILINEAR);

    // Set the scaled image to the GtkImage widget
    gtk_image_set_from_pixbuf(GTK_IMAGE(image), scaled_pixbuf);

    return image;
}
