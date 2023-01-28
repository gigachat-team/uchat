#include "../utils.h"

void free_chat_data(t_chat_data chat_data) {
    free(chat_data.name);
    mx_free_str_arr(&chat_data.member_logins);
}

