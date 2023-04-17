#include "gui.h"

void open_messenger_window(GtkBuilder *gtk_builder, t_address *server_address, id_t user_id) {
    close_window(gtk_builder, AUTHENTICATION_WINDOW_ID);
    open_window(gtk_builder, MESSENGER_WINDOW_ID);
    GtkWidget *messenger_window = GTK_WIDGET(gtk_builder_get_object(gtk_builder, MESSENGER_WINDOW_ID));
    set_cursor_image(messenger_window, DEFAULT_CURSOR_IMAGE_PATH);
    get_widget_by_id_and_apply_style(gtk_builder, CREATE_ROOM_ID, CSS_CLASS_NEW_CHAT_BUTTON);
    gui_render_chats_list(gtk_builder, server_address, user_id);
}
