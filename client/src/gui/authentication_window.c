#include "../../client.h"

static void open_messenger_window(GtkBuilder *gtk_builder, t_address *server_address, id_t user_id) {
    close_window(gtk_builder, AUTHENTICATION_WINDOW_ID);
    open_window(gtk_builder, MESSENGER_WINDOW_ID);
    gui_render_chats_list(gtk_builder, server_address, user_id);
}

void gui_login(GtkBuilder *gtk_builder, t_address *server_address, id_t *user_id) {
    GtkWidget *error_message = get_widget(gtk_builder, ERROR_MESSAGE_LOGIN_LABEL_ID);

    apply_style_to_widget(error_message, "error-message");

    char *login = get_entry_text(gtk_builder, LOGIN_ENTRY_ID);
    char *password = get_entry_text(gtk_builder, PASSWORD_ENTRY_ID);

    switch (rq_authenticate_user(*server_address, login, password, LOGIN_MODE, user_id)) {
    case SUCCESSFUL_LOGIN:
        open_messenger_window(gtk_builder, server_address, *user_id);
    break; case SUCH_LOGIN_DOES_NOT_EXIST:
        set_label_text(error_message, "Such login does not exist.");
    break; case WRONG_PASSWORD:
        set_label_text(error_message, "Wrong password.");
    break; case CONNECTION_REFUSED:
        set_label_text(error_message, "Failed to connect to the server.");
    break; default:
        break;
    }
}

void gui_register(GtkBuilder *gtk_builder, t_address *server_address, id_t *user_id) {
    GtkWidget *error_message = get_widget(gtk_builder, ERROR_MESSAGE_REGISTRATION_LABEL_ID);

    apply_style_to_widget(error_message, "error-message");

    char *new_login = get_entry_text(gtk_builder, NEW_LOGIN_ENTRY_ID);
    char *new_password = get_entry_text(gtk_builder, NEW_PASSWORD_ENTRY_ID);
    char *new_password_again = get_entry_text(gtk_builder, NEW_PASSWORD_AGAIN_ENTRY_ID);

    if (strlen(new_login) < MIN_LOGIN_LENGTH) {
        set_label_text(error_message, "Login must be longer.");
        return;
    }
    if (strlen(new_password) < MIN_PASSWORD_LENGTH) {
        set_label_text(error_message, "Password must be longer.");
        return;
    }
    if (strcmp(new_password, new_password_again) != 0) {
        set_label_text(error_message, "Password mismatch.");
        return;
    }

    switch (rq_authenticate_user(*server_address, new_login, new_password, REGISTER_MODE, user_id)) {
    case SUCCESSFUL_REGISTRATION:
        open_messenger_window(gtk_builder, server_address, *user_id);
    break; case SUCH_LOGIN_ALREADY_EXISTS:
        set_label_text(error_message, "Such login already exists.");
    break; case CONNECTION_REFUSED:
        set_label_text(error_message, "Failed to connect to the server.");
    break; default:
        break;
    }
}
