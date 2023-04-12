#include "../../client.h"

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

void apply_style_to_widget(GtkWidget *widget, const char *class) {
    if (!class || !widget) return;

    GtkStyleContext *context = gtk_widget_get_style_context(widget);

    gtk_style_context_add_class(context, class);
}

void get_widget_by_id_and_apply_style(t_gui_data gui_data, const char *markup_id, const char *class) {
    if (!markup_id || !class || !gui_data.builder) return;

    GtkWidget *newlogin = GTK_WIDGET(gtk_builder_get_object(gui_data.builder, markup_id));
    apply_style_to_widget(newlogin, class);
}
