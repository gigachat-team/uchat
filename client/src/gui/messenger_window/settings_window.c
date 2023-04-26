#include "gui.h"

void init_login_entry() {
    hide_widget(Builder, "login_alredy_exist");
    set_entry_text(Builder, "settings_login_entry", ThisUser->login);
}

void on_apply_settings() {
    char *new_login = get_entry_text(Builder, "settings_login_entry");
    t_state_code state = rq_change_login(ServerAddress, ThisUser->id, new_login);

    if (state == SUCH_LOGIN_ALREADY_EXISTS) {
        show_widget(Builder, "login_alredy_exist");
    }

    if (state == LOGIN_SUCCESSFULLY_CHANGED) {
        hide_widget(Builder, "login_alredy_exist");
        ThisUser->login = new_login;
    }
}

void on_open_settings_window_clicked() {
    open_window(Builder, "settings_window");
    init_login_entry();
}

void on_close_settings_window_clicked() {
    close_window(Builder, "settings_window");
}
