#include "gui.h"

static void gui_login() {
    GtkWidget *error_message = get_widget(Builder, ERROR_MESSAGE_LOGIN_LABEL_ID);

    apply_style_to_widget(error_message, CSS_CLASS_ERROR_MESSAGE);

    char *login = get_entry_text(Builder, LOGIN_ENTRY_ID);
    char *password = get_entry_text(Builder, PASSWORD_ENTRY_ID);

    switch (rq_authenticate_user(ServerAddress, login, password, LOGIN_MODE, &ThisUserId)) {
    case SUCCESSFUL_LOGIN:
        open_messenger_window();
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

static void gui_register() {
    GtkWidget *error_message = get_widget(Builder, ERROR_MESSAGE_REGISTRATION_LABEL_ID);
    apply_style_to_widget(error_message, CSS_CLASS_ERROR_MESSAGE);

    char *new_login = get_entry_text(Builder, NEW_LOGIN_ENTRY_ID);
    char *new_password = get_entry_text(Builder, NEW_PASSWORD_ENTRY_ID);
    char *new_password_again = get_entry_text(Builder, NEW_PASSWORD_AGAIN_ENTRY_ID);

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

    switch (rq_authenticate_user(ServerAddress, new_login, new_password, REGISTER_MODE, &ThisUserId)) {
    case SUCCESSFUL_REGISTRATION:
        open_messenger_window();
    break; case SUCH_LOGIN_ALREADY_EXISTS:
        set_label_text(error_message, "Such login already exists.");
    break; case CONNECTION_REFUSED:
        set_label_text(error_message, "Failed to connect to the server.");
    break; default:
        break;
    }
}

void on_register_button_clicked(GtkButton *b) {
    gui_register();
    (void)b;
}

void on_login_button_clicked(GtkButton *b) {
    gui_login();
    (void)b;
}
