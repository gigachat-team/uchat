#include "client_main.h"

int main(int argc, char **argv) {
    if (argc != 3) {
        printf(USAGE_MESSAGE);
        return EXIT_FAILURE;
    }

    gtk_init(&argc, &argv);
    load_css(CSS_DARK_FILE_PATH);
    t_gui_data gui_data = create_gui_data(argv[1], atoi(argv[2]));
    gtk_builder_connect_signals(gui_data.builder, &gui_data);

    GtkWidget *auth_window = GTK_WIDGET(gtk_builder_get_object(gui_data.builder, AUTHENTICATION_WINDOW_ID));
    open_window(gui_data.builder, AUTHENTICATION_WINDOW_ID);
    set_cursor_image(auth_window, DEFAULT_CURSOR_IMAGE_PATH);

    apply_style_to_widget(auth_window, CSS_CLASS_AUTHENTICATION_WINDOW);

    gtk_main();

    g_object_unref(gui_data.builder);

    return EXIT_SUCCESS;
}

void exit_app() {
    gtk_main_quit();
}
