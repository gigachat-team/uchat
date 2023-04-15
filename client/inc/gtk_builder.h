#pragma once

#include <gtk/gtk.h>

#define GLADE_FILE_PATH "resources/markup.glade"

GtkBuilder *create_gtk_builder();
