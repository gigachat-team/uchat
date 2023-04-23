#include "gui.h"

gboolean chat_list_updater(gpointer user_data) {
    t_gui_data *gui_data = (t_gui_data *)user_data;

    gui_render_chats_list(gui_data->builder, &gui_data->server_address, gui_data->user_id);
    return TRUE;
}

void open_messenger_window(GtkBuilder *gtk_builder, t_gui_data *data) {
    close_window(gtk_builder, AUTHENTICATION_WINDOW_ID);
    open_window(gtk_builder, MESSENGER_WINDOW_ID);
    GtkWidget *messenger_window = GTK_WIDGET(gtk_builder_get_object(gtk_builder, MESSENGER_WINDOW_ID));

    set_cursor_image(messenger_window, DEFAULT_CURSOR_IMAGE_PATH);

    get_widget_by_id_and_apply_style(gtk_builder, CONNECTING_BOX_ID, CSS_CLASS_CONNECTION_BOX);
    get_widget_by_id_and_apply_style(gtk_builder, CONNECTING_LABEL_ID, CSS_CLASS_CONNECTION_LABEL);

    get_widget_by_id_and_apply_style(gtk_builder, CREATE_ROOM_ID, CSS_CLASS_NEW_CHAT_BUTTON);
    get_widget_by_id_and_apply_style(gtk_builder, CHAT_LISTS_WINDOW_ID, CSS_CLASS_CHATS_LIST_CONTAINER);
    get_widget_by_id_and_apply_style(gtk_builder, CREATE_ROOM_ID, CSS_CLASS_CREATE_ROOM);
    get_widget_by_id_and_apply_style(gtk_builder, NEW_MESSAGE_ENTRY_ID, CSS_CLASS_MESSAGE_FIELD);
    get_widget_by_id_and_apply_style(gtk_builder, CHAT_NAME_LABEL_ID, CSS_CLASS_CHAT_NAME);
    get_widget_by_id_and_apply_style(gtk_builder, CANVAS_ID, CSS_CLASS_CANVAS);

    get_widget_by_id_and_apply_style(gtk_builder, UPPER_CANVAS_WINDOW_ID, CSS_CLASS_UPPER_CANVAS_WINDOW);
    get_widget_by_id_and_apply_style(gtk_builder, CREATE_ROOM_PARENT_ID, CSS_CLASS_CREATE_ROOM_PARENT);
    
    gui_render_chats_list(data->builder, &data->server_address, data->user_id);

    g_timeout_add(UPDATE_INTERVAL, chat_list_updater, data);
}
