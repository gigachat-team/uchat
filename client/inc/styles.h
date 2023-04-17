#pragma once

#include "gui_utils.h"

#define DEFAULT_CSS_FILE_PATH "resources/style.css"
#define DEFAULT_CURSOR_IMAGE_PATH "resources/img/write_icon.png"

#define CSS_CLASS_WHITE "white"
#define CSS_CLASS_ENTRY_DEFAULT "entry-default"
#define CSS_CLASS_ERROR_MESSAGE "error-message"
#define CSS_CLASS_NEW_CHAT_BUTTON "new-chat-button"

/**
 * @brief loads css to gtk. Should be called after gtk_init function
 * @param css_file_path path to a css file that will be included.
 * If variable is NULL, it'll use DEFAULT_CSS_FILE_PATH
*/
void load_css(char *css_file_path);

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
