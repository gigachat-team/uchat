#include "client_main.h"

GtkBuilder *Builder = NULL;

int main(int argc, char **argv) {
    if (argc != 3) {
        printf(USAGE_MESSAGE);
        return EXIT_FAILURE;
    }

    gtk_init(&argc, &argv);
    load_theme();

    Builder = create_gtk_builder();

    t_gui_data gui_data = create_gui_data(argv[1], atoi(argv[2]));
    gtk_builder_connect_signals(Builder, &gui_data);

    apply_styles_to_authentication_window(Builder);

    gtk_main();

    g_object_unref(Builder);

    return EXIT_SUCCESS;
}

void exit_app() {
    gtk_main_quit();
}
