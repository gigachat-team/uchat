#include "client_main.h"

GtkBuilder *Builder = NULL;

int main(int argc, char **argv) {
    if (argc != 3) {
        printf(USAGE_MESSAGE);
        return EXIT_FAILURE;
    }

    gtk_init(&argc, &argv);
    load_theme();
    t_gui_data gui_data = create_gui_data(argv[1], atoi(argv[2]));
    Builder = gui_data.builder;
    gtk_builder_connect_signals(gui_data.builder, &gui_data);

    apply_styles_to_authentication_window(gui_data.builder);

    gtk_main();

    g_object_unref(gui_data.builder);

    return EXIT_SUCCESS;
}

void exit_app() {
    gtk_main_quit();
}
