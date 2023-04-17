#include "styles.h"

void load_css(char *css_file_path) {
    GtkCssProvider *provider = gtk_css_provider_new();

    gtk_style_context_add_provider_for_screen(
        gdk_screen_get_default(),
        GTK_STYLE_PROVIDER(provider),
        GTK_STYLE_PROVIDER_PRIORITY_USER
    );

    if (!css_file_path) {
        gtk_css_provider_load_from_path(provider, DEFAULT_CSS_FILE_PATH, NULL);
        return;
    }

    gtk_css_provider_load_from_path(provider, css_file_path, NULL);
}

void apply_style_to_widget(GtkWidget *widget, const char *class_name) {
    if (!class_name || !widget) return;

    GtkStyleContext *context = gtk_widget_get_style_context(widget);

    gtk_style_context_add_class(context, class_name);
}

void get_widget_by_id_and_apply_style(GtkBuilder *builder, const char *markup_id, const char *class_name) {
    if (!markup_id || !class_name || !builder) return;

    GtkWidget *newlogin = GTK_WIDGET(gtk_builder_get_object(builder, markup_id));
    apply_style_to_widget(newlogin, class_name);
}

void set_cursor_image(GtkWidget *widget, const gchar *cursor_path) {
    if (!widget || !cursor_path) return;

    GdkCursor *cursor = NULL;
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file(cursor_path, NULL);

    if (!pixbuf) return;

    cursor = gdk_cursor_new_from_pixbuf(gdk_display_get_default(), pixbuf, 10, 30);
    g_object_unref(pixbuf);

    if (!cursor) return;

    GdkWindow *window = gtk_widget_get_window(widget);

    if (window != NULL) {
        gdk_window_set_cursor(window, cursor);
    }

    g_object_unref(cursor);
}
