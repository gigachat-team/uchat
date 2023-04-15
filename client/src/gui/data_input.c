#include "client_main.h"

t_new_chat_member_data get_new_chat_member_data(id_t chat_id) {
    printf("Enter new member login: ");
    char member_login[MAX_LOGIN_LENGTH];
    scanf("%s", member_login);

    t_new_chat_member_data new_chat_member_data = { chat_id, strdup(member_login) };
    return new_chat_member_data;
}

int console_input_int(char *message) {
    printf("%s", message);
    int number;
    scanf("%d", &number);
    return number;
}
