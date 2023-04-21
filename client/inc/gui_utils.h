#pragma once

#include <gtk/gtk.h>
#include <stdbool.h>

#define GLADE_FILE_PATH "resources/markup.glade"

// Destroy all widgets in container whith in builder
void clear_container(GtkBuilder *builder, char *contener_name);

char *get_entry_text(GtkBuilder *builder, char *entry_name);

GtkBuilder *create_gtk_builder();

// x, y is new size image
GtkWidget *get_image_from_path(char *path, gint x, gint y);

void set_label_text(GtkWidget *gtk_widget, char *text);
void write_label_text(GtkBuilder *builder, char *label_name, char *text);

// Scroll GrkSclolledWindow to botton position
void scroll_to_bottom(GtkBuilder *builder, char *name_scrolled_field);

GtkWidget *get_widget(GtkBuilder *gtk_builder, char *name);
// Add widget in box contener whith in builder
void add_to_box_start(GtkBuilder *builder, GtkWidget *new_element, gchar *box_name, gint padding);
void show_widget(GtkBuilder *builder, char *widget_name);
void hide_widget(GtkBuilder *builder, char *widget_name);

void open_window(GtkBuilder *builder, char *window_name);
void close_window(GtkBuilder *builder, char *window_name);
