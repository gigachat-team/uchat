#pragma once

#include "gui_data.h"

#define DEFAULT_CSS_FILE_PATH "resources/style.css"

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
 * @param class css class-name for a style
*/
void apply_style_to_widget(GtkWidget *widget, const char *class);

/**
 * @brief applies style to a gtk widget by id in a .glade file.
 * If one of the pointers in NULL, then the function does nothing
 * @param gui_data contains the builder pointer from which the function
 * gets a widget.
 * @param markup_id is an id from .glade file
 * @param class css class-name for a style
*/
void get_widget_by_id_and_apply_style(t_gui_data gui_data, const char *markup_id, const char *class);
