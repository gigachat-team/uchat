#include "client_main.h"

GtkBuilder *Builder = NULL;
t_address *ServerAddress = NULL;
id_t ThisUserId = 0;

int main(int argc, char **argv) {
    if (argc != 3) {
        printf(USAGE_MESSAGE);
        return EXIT_FAILURE;
    }

    t_address server_address = {argv[1], atoi(argv[2])};

    gtk_init(&argc, &argv);
    load_theme();

    Builder = create_gtk_builder();
    ServerAddress = &server_address;

    gtk_builder_connect_signals(Builder, NULL);

    apply_styles_to_authentication_window(Builder);

    gtk_main();

    g_object_unref(Builder);

    return EXIT_SUCCESS;
}

void exit_app() {
    gtk_main_quit();
}
