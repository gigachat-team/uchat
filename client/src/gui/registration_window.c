#include "../../client.h"

static t_gui_data gui_data_init(char **argv) {
    GError *err = NULL;
    GtkBuilder *builder = gtk_builder_new();
    if (0 == gtk_builder_add_from_file(builder, "./client/src/gui/TestGUI.glade", &err))
        fprintf(stderr, "Error adding build from file. Error: %s\n", err->message);

    t_gui_data gui_data = {
        .builder = builder,
        .server_address = {argv[1], atoi(argv[2])},
        .user_id = 0
    };

    return gui_data;
}

static bool validation_authentication_data(t_authentication_data authentication_data, GtkWidget *error_message) {
    if (strlen(authentication_data.login) <= MIN_LOGIN_LENGTH) {
        gtk_label_set_text(GTK_LABEL(error_message), "Login must be longer.");
        return false;
    }

    if (strlen(authentication_data.password) <= MIN_PASSWORD_LENGTH) {
        gtk_label_set_text(GTK_LABEL(error_message), "Password must be longer.");
        return false;
    }

    return true;
}

// Buttons-events-----------------------------------
void login(GtkButton *bconfirm, gpointer user_data) {
    t_gui_data *data = (t_gui_data *)user_data;

    GtkBuilder *builder = data->builder;
    GtkWidget *enter_login = GTK_WIDGET(gtk_builder_get_object(builder, "wlogin"));
    GtkWidget *enter_password = GTK_WIDGET(gtk_builder_get_object(builder, "wpassword"));
    GtkWidget *error_message = GTK_WIDGET(gtk_builder_get_object(builder, "error_message_login"));

    t_authentication_data authentication_data = get_authentication_data(enter_login, enter_password);

    if (!validation_authentication_data(authentication_data, error_message)) {
        return;
    }

    switch (rq_authenticate_user(data->server_address, authentication_data, LOGIN_MODE, &data->user_id)) {
        case SUCCESSFUL_LOGIN:
            open_messenger_window(*data);
        break; case SUCH_LOGIN_DOES_NOT_EXIST:
            gtk_label_set_text(GTK_LABEL(error_message), "Such login does not exist.");
        break; case WRONG_PASSWORD:
            gtk_label_set_text(GTK_LABEL(error_message), "Wrong password.");
        break; case CONNECTION_REFUSED:
            gtk_label_set_text(GTK_LABEL(error_message), "Failed to connect to the server.");
        break; default:
            break;
    }

    free_authentication_data(authentication_data);

    (void)bconfirm;
}

void regist(GtkButton *bconfirm, gpointer user_data) {
    t_gui_data *data = (t_gui_data *)user_data;

    GtkBuilder *builder = data->builder;
    GtkWidget *enter_newlogin = GTK_WIDGET(gtk_builder_get_object(builder, "wnewlogin"));
    GtkWidget *enter_newpassword = GTK_WIDGET(gtk_builder_get_object(builder, "wnewpassword"));
    GtkWidget *enter_newpassword_repeat = GTK_WIDGET(gtk_builder_get_object(builder, "wnewpassword_r"));
    GtkWidget *error_message = GTK_WIDGET(gtk_builder_get_object(builder, "error_message_register"));

    t_authentication_data authentication_data = get_authentication_data(enter_newlogin, enter_newpassword);
    char *password_repeat = (char *)gtk_entry_get_text(GTK_ENTRY(enter_newpassword_repeat));

    if (!validation_authentication_data(authentication_data, error_message)) {
        return;
    }

    if (strcmp(authentication_data.password, password_repeat) != 0) {
        gtk_label_set_text(GTK_LABEL(error_message), "Password mismatch.");
        return;
    }

    switch (rq_authenticate_user(data->server_address, authentication_data, REGISTER_MODE, &data->user_id)) {
        case SUCCESSFUL_REGISTRATION:
            open_messenger_window(*data);
        break; case SUCH_LOGIN_ALREADY_EXISTS:
            write_label_text(data->builder, "error_message_register", "Such login already exists.");
        break; case CONNECTION_REFUSED:
            gtk_label_set_text(GTK_LABEL(error_message), "Failed to connect to the server.");
        break; default:
            break;
    }

    free_authentication_data(authentication_data);

    (void)bconfirm;
}
//-------------------------------------------------

void gui_init(int argc, char **argv) {
    gtk_init(&argc, &argv);

    t_gui_data data = gui_data_init(argv);
    gtk_builder_connect_signals(data.builder, &data);

    // open_messenger_window(data);

    open_window(data.builder, "Authorization");


    gtk_main();
    g_object_unref(data.builder);
}
