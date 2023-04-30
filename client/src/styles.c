#include "styles.h"

void load_css(char *css_file_path) {
    GtkCssProvider *provider = gtk_css_provider_new();

    gtk_style_context_add_provider_for_screen(
        gdk_screen_get_default(),
        GTK_STYLE_PROVIDER(provider),
        GTK_STYLE_PROVIDER_PRIORITY_USER
    );

    if (!css_file_path) {
        gtk_css_provider_load_from_path(provider, PATH_TO_LIGHT_STYLE, NULL);
        return;
    }

    gtk_css_provider_load_from_path(provider, css_file_path, NULL);
}

void load_theme() {
    char style_type_str[2];
    read_from_file(STYLE_TYPE_SETTING_PATH, 2, style_type_str);
    t_style_type style_type = atoi(style_type_str);

    switch (style_type) {
    case DARK_STYLE_THEME:
        load_dark_theme(); break;
    case LIGHT_STYLE_THEME:
        load_light_theme(); break;
    }
}

void save_theme(t_style_type style_type) {
    char *style_type_str;
    asprintf(&style_type_str, "%u", style_type);
    write_to_file(STYLE_TYPE_SETTING_PATH, style_type_str);
    free(style_type_str);
}

void load_light_theme() {
    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    t_string css_str = read_three_files(PATH_TO_LIGHT_STYLE_SETTINGS, PATH_TO_COMMON_STYLE, PATH_TO_LIGHT_STYLE);
    gtk_css_provider_load_from_data(provider, css_str.val, css_str.len, NULL);
    string_destroy(&css_str);
}

void load_dark_theme() {
    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    t_string css_str = read_three_files(PATH_TO_DARK_STYLE_SETTINGS, PATH_TO_COMMON_STYLE, PATH_TO_DARK_STYLE);
    gtk_css_provider_load_from_data(provider, css_str.val, css_str.len, NULL);
    string_destroy(&css_str);
}

void apply_style_to_widget(GtkWidget *widget, const char *class_name) {
    if (!class_name || !widget) return;

    GtkStyleContext *context = gtk_widget_get_style_context(widget);

    gtk_style_context_add_class(context, class_name);
}

void get_widget_by_id_and_apply_style(GtkBuilder *builder, const char *markup_id, const char *class_name) {
    if (!markup_id || !class_name || !builder) return;

    GtkWidget *newlogin = GTK_WIDGET(gtk_builder_get_object(builder, markup_id));
    apply_style_to_widget(newlogin, class_name);
}

void set_cursor_image(GtkWidget *widget, const gchar *cursor_path) {
    if (!widget || !cursor_path) return;

    GdkCursor *cursor = NULL;
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file(cursor_path, NULL);

    if (!pixbuf) return;

    cursor = gdk_cursor_new_from_pixbuf(gdk_display_get_default(), pixbuf, 10, 36);
    g_object_unref(pixbuf);

    if (!cursor) return;

    GdkWindow *window = gtk_widget_get_window(widget);

    if (window != NULL) {
        gdk_window_set_cursor(window, cursor);
    }

    g_object_unref(cursor);
}

void apply_styles_for_messenger_window(GtkBuilder *gtk_builder) {
    if (!gtk_builder) return;

    GtkWidget *messenger_window = GTK_WIDGET(gtk_builder_get_object(gtk_builder, MESSENGER_WINDOW_ID));

    set_cursor_image(messenger_window, DEFAULT_CURSOR_IMAGE_PATH);

    get_widget_by_id_and_apply_style(gtk_builder, CANVAS_ID, CSS_CLASS_CANVAS);
    get_widget_by_id_and_apply_style(gtk_builder, MAIN_AREA_ID, CSS_CLASS_MAIN_AREA);
    get_widget_by_id_and_apply_style(gtk_builder, NEW_MESSAGE_ENTRY_ID, CSS_CLASS_ENTRY);
    get_widget_by_id_and_apply_style(gtk_builder, CHAT_NAME_LABEL_ID, CSS_CLASS_CHAT_NAME);
    get_widget_by_id_and_apply_style(gtk_builder, SEARCH_ENTRY_ID, CSS_CLASS_SEARCH_ENTRY);

    get_widget_by_id_and_apply_style(gtk_builder, NEW_MESSAGE_ENTRY_ID, CSS_CLASS_MESSAGE_FIELD);
    get_widget_by_id_and_apply_style(gtk_builder, CREATE_ROOM_PARENT_ID, CSS_CLASS_CREATE_ROOM_PARENT);
    get_widget_by_id_and_apply_style(gtk_builder, UPPER_CANVAS_WINDOW_ID, CSS_CLASS_UPPER_CANVAS_WINDOW);
    get_widget_by_id_and_apply_style(gtk_builder, SEARCH_ENTRY_PARENT_ID, CSS_CLASS_SEARCH_ENTRY_PARENT);
    get_widget_by_id_and_apply_style(gtk_builder, NEW_MESSAGE_ENTRY_PARENT_ID, CSS_CLASS_NEW_MESSAGE_ENTRY_PARENT);
}

void apply_styles_to_create_chat_window(GtkBuilder *gtk_builder) {
    if (!gtk_builder) return;

    GtkWidget *crate_chat_window = get_widget(gtk_builder, CREATE_CHAT_WINDOW_ID);
    set_cursor_image(crate_chat_window, DEFAULT_CURSOR_IMAGE_PATH);

    get_widget_by_id_and_apply_style(gtk_builder, CREATE_CHAT_TOP_LABEL_ID, CSS_CLASS_WINDOW_TOP_LABEL);
    get_widget_by_id_and_apply_style(gtk_builder, NEW_CHAT_NAME_ENTRY_ID, CSS_CLASS_ENTRY);
}

void apply_styles_to_chat_settings_window(GtkBuilder *gtk_builder) {
    if (!gtk_builder) return;

    GtkWidget *chat_settings_window = GTK_WIDGET(gtk_builder_get_object(gtk_builder, CHAT_SETTINGS_WINDOW_ID));
    set_cursor_image(chat_settings_window, DEFAULT_CURSOR_IMAGE_PATH);

    get_widget_by_id_and_apply_style(gtk_builder, CHAT_SETTINGS_TOP_LABEL_ID, CSS_CLASS_WINDOW_TOP_LABEL);
    get_widget_by_id_and_apply_style(gtk_builder, ENTRY_ADD_MEMBER_ID, CSS_CLASS_ENTRY);
}

void apply_styles_to_authentication_window(GtkBuilder *gtk_builder) {
    if (!gtk_builder) return;

    GtkWidget *authentication_window = GTK_WIDGET(gtk_builder_get_object(gtk_builder, AUTHENTICATION_WINDOW_ID));
    open_window(gtk_builder, AUTHENTICATION_WINDOW_ID);
    set_cursor_image(authentication_window, DEFAULT_CURSOR_IMAGE_PATH);
    get_widget_by_id_and_apply_style(gtk_builder, AUTHENTICATION_LABEL_ID, CSS_CLASS_WINDOW_TOP_LABEL);

    get_widget_by_id_and_apply_style(gtk_builder, LOGIN_ENTRY_ID,              CSS_CLASS_ENTRY);
    get_widget_by_id_and_apply_style(gtk_builder, PASSWORD_ENTRY_ID,           CSS_CLASS_ENTRY);
    get_widget_by_id_and_apply_style(gtk_builder, NEW_LOGIN_ENTRY_ID,          CSS_CLASS_ENTRY);
    get_widget_by_id_and_apply_style(gtk_builder, NEW_PASSWORD_ENTRY_ID,       CSS_CLASS_ENTRY);
    get_widget_by_id_and_apply_style(gtk_builder, NEW_PASSWORD_AGAIN_ENTRY_ID, CSS_CLASS_ENTRY);
}

void apply_styles_to_settings_window(GtkBuilder *gtk_builder) {
    if (!gtk_builder) return;

    GtkWidget *settings_window = GTK_WIDGET(gtk_builder_get_object(gtk_builder, SETTINGS_WINDOW_ID));
    open_window(gtk_builder, SETTINGS_WINDOW_ID);
    set_cursor_image(settings_window, DEFAULT_CURSOR_IMAGE_PATH);
    get_widget_by_id_and_apply_style(gtk_builder, SETTINGS_LOGIN_ENTRY_ID, CSS_CLASS_ENTRY);
}

void on_toggle_theme_button_clicked(GtkButton *b) {
    char style_type_str[2];
    read_from_file(STYLE_TYPE_SETTING_PATH, 2, style_type_str);
    t_style_type style_type = atoi(style_type_str);

    switch (style_type) {
    case DARK_STYLE_THEME:
        load_light_theme();
        save_theme(LIGHT_STYLE_THEME); break;
    case LIGHT_STYLE_THEME:
        load_dark_theme();
        save_theme(DARK_STYLE_THEME); break;
    }

    (void)b;
}
