#include "client_main.h"

GtkBuilder *Builder = NULL;
t_address *ServerAddress = NULL;
id_t ThisUserId = 0;
list_t *LoadedMessagesList = NULL;
t_chat *SelectedChat = NULL;

int main(int argc, char **argv) {
    if (argc != 3) {
        printf(USAGE_MESSAGE);
        return EXIT_FAILURE;
    }


    gtk_init(&argc, &argv);
    load_theme();

    t_address server_address = {argv[1], atoi(argv[2])};
    t_chat selected_chat = {.id = 0, .name = NULL, .owner_id = 0};

    Builder = create_gtk_builder();
    ServerAddress = &server_address;
    LoadedMessagesList = list_new();
    SelectedChat = &selected_chat;

    gtk_builder_connect_signals(Builder, NULL);

    apply_styles_to_authentication_window(Builder);

    gtk_main();

    g_object_unref(Builder);
    free_user_messages_list(LoadedMessagesList);

    return EXIT_SUCCESS;
}

void exit_app() {
    gtk_main_quit();
}
