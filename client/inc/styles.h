#pragma once

#include "gui.h"
#include "file.h"
#include "gui_utils.h"

#define PATH_TO_LIGHT_STYLE "resources/styles/light.css"
#define PATH_TO_DARK_STYLE "resources/styles/dark.css"
#define DEFAULT_CURSOR_IMAGE_PATH "resources/img/cursor.png"

#define STYLE_TYPE_SETTING_PATH "resources/settings/style_type.txt"

#define CSS_CLASS_ENTRY "entry"
#define CSS_CLASS_CANVAS "canvas"
#define CSS_CLASS_CHAT_NAME "chat-name"
#define CSS_CLASS_MAIN_AREA "main-area"
#define CSS_CLASS_CREATE_ROOM "create-room"
#define CSS_CLASS_SEARCH_ENTRY "search-entry"
#define CSS_CLASS_ENTRY_DEFAULT "entry-default"
#define CSS_CLASS_MESSAGE_FIELD "message-field"
#define CSS_CLASS_ERROR_MESSAGE "error-message"
#define CSS_CLASS_NEW_CHAT_BUTTON "new-chat-button"
#define CSS_CLASS_WINDOW_TOP_LABEL "window-top-label"
#define CSS_CLASS_TIME_TEXT_SETTINGS "time-text"
#define CSS_CLASS_TIME_NAME_SETTINGS "name-text"
#define CSS_CLASS_CREATE_ROOM_PARENT "create-room-parent"
#define CSS_CLASS_SEARCH_ENTRY_PARENT "search-entry-parent"
#define CSS_CLASS_UPPER_CANVAS_WINDOW "upper-canvas-window"
#define CSS_CLASS_CHATS_LIST_CONTAINER "chats-list-containter"
#define CSS_CLASS_NEW_MESSAGE_ENTRY_PARENT "new-message-entry-parent"

typedef enum {
    DARK_STYLE_THEME,
    LIGHT_STYLE_THEME
} t_style_type;

/**
 * @brief loads css to gtk. Should be called after gtk_init function
 * @param css_file_path path to a css file that will be included.
 * If variable is NULL, it'll use PATH_TO_LIGHT_STYLE
*/
void load_css(char *css_file_path);

void load_theme();
void save_theme(t_style_type style_type);

/**
 * @brief loads default light theme
*/
void load_light_theme();

/**
 * @brief loads default dark theme
*/
void load_dark_theme();

/**
 * @brief applies a style from a loaded css file to a widget.
 * If one of the pointers in NULL, then the function does nothing
 * @param widget in which a new style will be loaded
 * @param class_name css class-name for a style
*/
void apply_style_to_widget(GtkWidget *widget, const char *class_name);

/**
 * @brief applies style to a gtk widget by id in a .glade file.
 * If one of the pointers in NULL, then the function does nothing
 * @param gui_data contains the builder pointer from which the function
 * gets a widget.
 * @param markup_id is an id from .glade file
 * @param class_name css class-name for a style
*/
void get_widget_by_id_and_apply_style(GtkBuilder *builder, const char *markup_id, const char *class_name);

/**
 * @brief sets a cursor image from CURSOR_PATH in a window from WIDGET
 * If the WIDGET doesn't have a window, the function does nothing. The
 * same thing if the pointers are NULL
 * @param widget a pointer to a widget that contains a GtkWindow pointer
 * @param cursor_path a file path to the cursor image.
*/
void set_cursor_image(GtkWidget *widget, const gchar *cursor_path);

/**
 * @brief sets all the styles for the messenger window and the cursor
 * image. If no builder is provied, the function does nothing
 * @param gtk_builder builder to apply styles
*/
void apply_styles_for_messenger_window(GtkBuilder *gtk_builder);

/**
 * @brief sets all the styles for the create chat window and the cursor
 * image. If no builder is provied, the function does nothing
 * @param gtk_builder builder to apply styles
*/
void apply_styles_to_create_chat_window(GtkBuilder *gtk_builder);

/**
 * @brief sets all the styles for the chat settings window and the cursor
 * image. If no builder is provied, the function does nothing
 * @param gtk_builder builder to apply styles
*/
void apply_styles_to_chat_settings_window(GtkBuilder *gtk_builder);

/**
 * @brief sets all the styles for the authentication window and the cursor
 * image. If no builder is provied, the function does nothing
 * @param gtk_builder builder to apply styles
*/
void apply_styles_to_authentication_window(GtkBuilder *gtk_builder);

/**
 * @brief sets all the styles for the settings window and the cursor
 * image. If no builder is provied, the function does nothing
 * @param gtk_builder builder to apply styles
*/
void apply_styles_to_settings_window(GtkBuilder *gtk_builder);
