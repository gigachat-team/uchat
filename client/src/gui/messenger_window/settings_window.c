#include "gui.h"

void on_open_settings_window() {
    open_window(Builder, "settings_window");
}

void on_close_settings_window() {
    close_window(Builder, "settings_window");
}
