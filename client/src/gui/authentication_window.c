#include "client_main.h"

static void open_messenger_window(GtkBuilder *gtk_builder, t_address *server_address, id_t user_id) {
    close_window(gtk_builder, AUTHENTICATION_WINDOW_ID);
    open_window(gtk_builder, MESSENGER_WINDOW_ID);
    GtkWidget *messenger_window = GTK_WIDGET(gtk_builder_get_object(gtk_builder, MESSENGER_WINDOW_ID));
    set_cursor_image(messenger_window, DEFAULT_CURSOR_IMAGE_PATH);
    get_widget_by_id_and_apply_style(gtk_builder, CREATE_ROOM_ID, CSS_CLASS_NEW_CHAT_BUTTON);
    gui_render_chats_list(gtk_builder, server_address, user_id);
}

static void gui_login(GtkBuilder *gtk_builder, t_address *server_address, id_t *user_id) {
    GtkWidget *error_message = get_widget(gtk_builder, ERROR_MESSAGE_LOGIN_LABEL_ID);

    apply_style_to_widget(error_message, CSS_CLASS_ERROR_MESSAGE);

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

static void gui_register(GtkBuilder *gtk_builder, t_address *server_address, id_t *user_id) {
    GtkWidget *error_message = get_widget(gtk_builder, ERROR_MESSAGE_REGISTRATION_LABEL_ID);
    apply_style_to_widget(error_message, CSS_CLASS_ERROR_MESSAGE);

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

void on_register_button_clicked(GtkButton *b, gpointer user_data) {
    t_gui_data *gui_data = (t_gui_data *)user_data;
    gui_register(gui_data->builder, &gui_data->server_address, &gui_data->user_id);
    (void)b;
}

void on_login_button_clicked(GtkButton *b, gpointer user_data) {
    t_gui_data *gui_data = (t_gui_data *)user_data;
    gui_login(gui_data->builder, &gui_data->server_address, &gui_data->user_id);
    (void)b;
}
