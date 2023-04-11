#include "../../client.h"

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

void gui_login(GtkBuilder *gtk_builder, t_address *server_address, id_t user_id) {
    GtkWidget *enter_login = GTK_WIDGET(gtk_builder_get_object(gtk_builder, "wlogin"));
    GtkWidget *enter_password = GTK_WIDGET(gtk_builder_get_object(gtk_builder, "wpassword"));
    GtkWidget *error_message = GTK_WIDGET(gtk_builder_get_object(gtk_builder, "error_message_login"));

    apply_style_to_widget(error_message, "error-message");

    t_authentication_data authentication_data = get_authentication_data(enter_login, enter_password);

    if (!validation_authentication_data(authentication_data, error_message)) {
        return;
    }

    switch (rq_authenticate_user(*server_address, authentication_data, LOGIN_MODE, &user_id)) {
    case SUCCESSFUL_LOGIN:
        open_messenger_window(gtk_builder, server_address, user_id);
    break; case SUCH_LOGIN_DOES_NOT_EXIST:
        gtk_label_set_text(GTK_LABEL(error_message), "Such login does not exist.");
    break; case WRONG_PASSWORD:
        gtk_label_set_text(GTK_LABEL(error_message), "Wrong password.");
    break; case CONNECTION_REFUSED:
        gtk_label_set_text(GTK_LABEL(error_message), "Failed to connect to the server.");
    break; default:
        break;
    }

    if (authentication_data.login != NULL && authentication_data.password != NULL) {
        free_authentication_data(authentication_data);
    }
}

void gui_register(GtkBuilder *gtk_builder, t_address *server_address, id_t *user_id) {
    GtkWidget *new_login = GTK_WIDGET(gtk_builder_get_object(gtk_builder, NEW_LOGIN_FIELD_ID));
    GtkWidget *new_password = GTK_WIDGET(gtk_builder_get_object(gtk_builder, NEW_PASSWORD_FIELD_ID));
    GtkWidget *new_password_again = GTK_WIDGET(gtk_builder_get_object(gtk_builder, NEW_PASSWORD_AGAIN_FIELD_ID));
    GtkWidget *error_message = GTK_WIDGET(gtk_builder_get_object(gtk_builder, ERROR_MESSAGE_REGISTRATION_LABEL_ID));

    apply_style_to_widget(error_message, "error-message");

    t_authentication_data authentication_data = get_authentication_data(new_login, new_password);
    char *password_repeat = (char *)gtk_entry_get_text(GTK_ENTRY(new_password_again));

    if (!validation_authentication_data(authentication_data, error_message)) {
        return;
    }

    if (strcmp(authentication_data.password, password_repeat) != 0) {
        gtk_label_set_text(GTK_LABEL(error_message), "Password mismatch.");
        return;
    }

    switch (rq_authenticate_user(*server_address, authentication_data, REGISTER_MODE, user_id)) {
    case SUCCESSFUL_REGISTRATION:
        open_messenger_window(gtk_builder, server_address, *user_id);
    break; case SUCH_LOGIN_ALREADY_EXISTS:
        write_label_text(gtk_builder, ERROR_MESSAGE_REGISTRATION_LABEL_ID, "Such login already exists.");
    break; case CONNECTION_REFUSED:
        gtk_label_set_text(GTK_LABEL(error_message), "Failed to connect to the server.");
    break; default:
        break;
    }

    free_authentication_data(authentication_data);
}
